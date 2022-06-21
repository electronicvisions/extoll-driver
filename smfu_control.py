#!/usr/bin/python

from __future__ import print_function

import os
import ast
import sys
import mmap
import struct
import math
from datetime import datetime

def main(argv=sys.argv):
	commands = [
		{"name": "load_test",
		 "desc": "Loads memory of given size (in 8 byte chunks) and prints some basic performance stats (not comparable to native c benchmarks)",
		 "func": load_test,
		 "args": [
		 	["count", "Number of 8 byte chunks to load"] ] },

		{"name": "store_test",
		 "desc": "Stores deterministic values (in 8 byte chunks) in global memory and prints some basic performance stats (not comparable to native c benchmarks)",
		 "func": store_test,
		 "args": [
		 	["count", "Number of 8 byte chunks to store"] ] },

		{"name": "get_intervals",
		 "desc": "Pretty prints intervals configured on this machine",
		 "func": get_intervals,
		 "args": [] },

		{"name": "set_intervals",
		 "desc": "Stacks the intervals passed onto each other and configures them on this machine",
		 "func": set_intervals,
		 "args": [
		 	["intervals", "Interval list in <node>:<size>, example: 1:1G,2:512M"] ] },

		{"name": "disable_caching",
		 "desc": "Disables caching for global memory on this machine by disabling the corresponding MTRR",
		 "func": disable_caching,
		 "args": [] },

		{"name": "enable_caching",
		 "desc": "Enables caching for global memory on this machine by configuring an MTRR for it",
		 "func": enable_caching,
		 "args": [
		 	["size", "Size of region that is to be cached"] ] },

		{"name": "save_mem",
		 "desc": "Stores a memory dump of the global memory on disk",
		 "func": save_mem,
		 "args": [
		 	["size", "Size of memory chunk that is to be stored"],
		 	["offset", "Offset where the memory chunk starts (not the mmap offset!)"],
			["filename", "File in which the dump should be saved"] ] },

		{"name": "load_mem",
		 "desc": "Loads a memory dump from disk and writes to the global memory",
		 "func": load_mem,
		 "args": [
		 	["size", "Size of memory chuck that is to be loaded"],
			["offset", "Offset where the memory chunk starts (not the mmap offset!)"],
			["filename", "File where the data should be loaded from"] ] },

		{"name": "hexdump",
		 "desc": "Show a hexdump of a part of the global memory",
		 "func": hexdump,
		 "args": [
		 	["size", "Size of memory chunk to dump to screen"],
			["offset", "Offset of memory chunk (not the mmap offset!)"] ] }
	]

	if (len(argv) < 2):
		print("Usage: %s <command> <arguments>" % argv[0])
		print_commands(commands)
		return -1
	
	found = False
	for cmd in commands:
		if ( cmd["name"] == argv[1] ):
			found = True
			if ( (len(argv) - 2) < len(cmd["args"]) ):
				print("Not enough arguments for function. Expected %d, got %d" % (len(cmd["args"]),  len(argv)-2))
				return -1
			if ( (len(argv) - 2) > len(cmd["args"]) ):
				print("Too many arguments for function. Expected %d, got %d" % (len(cmd["args"]),  len(argv)-2))
				return -1
			args = {}
			i = 2
			for arg in cmd["args"]:
				args[arg[0]] = argv[i]
				i += 1
			cmd["func"](args)

	if ( not found ):
		print("Unknown command: %s" % argv[1])
		print_commands(commands)
		return -1


# *****************************************************************************
# A C C E S S I B L E   F U N C T I O N S
# *****************************************************************************

def load_test(args):
	count = parse_size(args["count"])
	with smfu_map(count*8) as mm:
		print("Loading %d bytes as %d unsigned long ints..." % (count*8, count), end="")
		buf = ["\x00\x00\x00\x00\x00\x00\x00\x00"] * count
		start = datetime.now()
		for i in xrange(count):
			buf[i] = mm.read(8)
		end = datetime.now()
		print("done")
		print("last read values:")
		for i in xrange(min(count, 10)):
			print("  0x%016LX" % struct.unpack("L", buf[i]))
		diff_secs = total_seconds(end - start)
		latency_per_read = diff_secs / (count)
		bandwidth = count*8 / diff_secs
		print("Total time: %s, Latency per load: %s, Load Bandwidth: %s/s" %
			(format_duration(diff_secs), format_duration(latency_per_read), format_size(bandwidth)))

def store_test(args):
	count = parse_size(args["count"])
	with smfu_map(count*8) as mm:
		print("Storing %d bytes as %d unsigned long ints..." % (count*8, count), end="")
		buf = []
		for i in xrange(count):
			buf += [struct.pack("L", 0xCAFEBABE00000000 + i)]
		start = datetime.now()
		for i in xrange(count):
			mm.write(buf[i])
		end = datetime.now()
		print("done")
		diff_secs = total_seconds(end - start)
		latency_per_read = diff_secs / count
		bandwidth = count*8 / diff_secs
		print("Total time: %s, Latency per Store: %s, Store Bandwidth: %s/s" %
			(format_duration(diff_secs), format_duration(latency_per_read), format_size(bandwidth)))

def set_intervals(args):
	intervals = parse_intervals(args["intervals"])
	# reset all intervals
	for i in xrange(16):
		set_interval(i, 0, 0, 0)
		write_reg("extoll_rf_smfu_rf_vpid_tStartAddr_raw",
				[i, 0])
	
	start = read_reg("extoll_rf_smfu_rf_oStartAddr_raw")[0]
	for interval in intervals:
		control = 0x301 | ( interval['node'] << 16 )
		end = start + interval['size'] - 1;
		set_interval(interval['node'], start, end, control)
		start = end + 1
	
	default_start = read_reg("extoll_rf_smfu_rf_tStartAddr_default_raw")[0]
	write_reg("extoll_rf_smfu_rf_vpid_tStartAddr_raw",
			[nodeid(), default_start])
	return 0

def get_intervals(args):
	starts = read_reg("extoll_rf_smfu_rf_interval_startaddr_raw")
	ends = read_reg("extoll_rf_smfu_rf_interval_endaddr_raw")
	controls = read_reg("extoll_rf_smfu_rf_interval_control_raw")
	vpid_addresses = read_reg("extoll_rf_smfu_rf_vpid_tStartAddr_raw")
	print("Interval    Node       Size          Start -            End     Vpid start")
	print("--------------------------------------------------------------------------")
	for i in xrange(16):
		start = starts[i]
		end = ends[i]
		node = controls[i] >> 16
		vpid_address = vpid_addresses[i]
		status = "invalid"
		if (controls[i] & 0x1 != 0):
			status = " valid "
		print("%02d[%s] %4s %10s %14s - %14s %14s" %
			(i, status, node, format_size(end-start), hex(start), hex(end), hex(vpid_address)))

def disable_caching(args):
	ostart = read_reg("extoll_rf_smfu_rf_oStartAddr_raw")[0]
	reg = get_mtrr_reg(ostart)
	if (reg != None):
		echo("/proc/mtrr", "disable=%d" % reg)
		if (get_mtrr_reg(ostart) == None):
			print("Caching disabled")
		else:
			print("Something went wrong, Caching still enabled");
			return -1
	else:
		print("Caching already disabled")
	return 0

def enable_caching(args):
	size = parse_size(args["size"])
	ostart = read_reg("extoll_rf_smfu_rf_oStartAddr_raw")[0]
	if (get_mtrr_reg(ostart) != None):
		print("Caching already enabled")
	else:
		try:
			echo("/proc/mtrr", "base=0x0%x size=0x0%x type=write-back" % (ostart, size) )
		except Exception as e:
			print(e.strerror)
		if (get_mtrr_reg(ostart) != None):
			print("Caching enabled")
		else:
			print("Something went wrong, caching still disabled")
			return -1
	return -1

def save_mem(args):
	size = parse_size(args["size"])
	offset = parse_size(args["offset"])
	filename = args["filename"]
	buf_size = 1024*8
	with open(filename, "wb") as f:
		print("Dumping %lu bytes from global memory into file %s..." % (size, filename))
		with smfu_map(size, 0) as mm:
			mm.seek(offset)
			for i in xrange(size/buf_size):
				f.write(mm.read(buf_size))
			if (size / buf_size * buf_size < size):
				f.write(mm.read(size - size / buf_size * buf_size))
	print("Done")

def load_mem(args):
	size = parse_size(args["size"])
	offset = parse_size(args["offset"])
	filename = args["filename"]
	buf_size = 1024*8
	with open(filename, "rb") as f:
		print("Loading %lu bytes from file %s into global memory..." % (size, filename))
		with smfu_map(size, 0) as mm:
			mm.seek(offset)
			for i in xrange(size/buf_size):
				buf = f.read(buf_size)
				if (len(buf) < buf_size):
					print("File not big enough")
					return -1
				mm.write(buf)
			remainder = size - size / buf_size * buf_size
			if (remainder == 0):
				buf = f.read(remainder)
				if (len(buf) < remainder):
					print("File not big enough")
					return -1
				mm.write(buf)

def hexdump(args):
	size = parse_size(args["size"])
	offset = parse_size(args["offset"])
	with smfu_map(size, 0) as mm:
		mm.seek(offset)
		print(dump_as_hex(mm.read(size), 16))


# *****************************************************************************
# A U X I L I A R Y   F U N C T I O N S
# *****************************************************************************

# return extoll r2 sysfs
def sysfs():
	try:
		return os.environ["EXTOLL_R2_SYSFS"]
	except:
		raise Exception("Extoll Sysfs not set")

# arguments:
#   file: register file to read (without sysfs path)
# returns:
#   array with values (each output line results in one array element)
# 
# reading a scalar value: read_reg(file)[0]
def read_reg(file):
	f = open(sysfs()+"/"+file, "r")
	lines = f.readlines()
	results = []
	for line in lines:
		results += [ int(line, 16) ]
	f.close()
	return results

# arguments:
#   file: register file to write to (without sysfs path)
#   values: array with values to write
#   fake: print what would be written but doesn't write to file
# returns:
#   nothing
# 
# writing scalar values: write_reg(file, [value])
# writing array element (e.g. single interval): write_reg(file, [index, value])
def write_reg(file, values, fake=False):
	f = open(sysfs()+"/"+file, "w")
	str = ""
	for value in values:
		str += hex(value)+" "
	if (fake):
		print(file+" "+str)
	else:
		f.write(str)
	f.close()

# create memory map object with context guard
# supposed to use with "with":
#   with smfu_map(size, offset) as mm:
#     do stuff
#
# arguments:
#   size: size to map in bytes
#   smfu_offset: offset to be passed (if 1, directly map target memory)
# returns:
#   mmap object
class smfu_map():
	def __init__(self, size, offset=0):
		if (not os.path.exists("/dev/smfu2")):
			raise Exception("SMFU device file not found")
		self.f = open("/dev/smfu2", "wb+")
		self.mm = mmap.mmap(self.f.fileno(), size,
					prot=(mmap.PROT_READ | mmap.PROT_WRITE),
					flags=mmap.MAP_SHARED,
					offset=offset)
	def __enter__(self):
		return self.mm
	def __exit__(self, type, value, traceback):
		self.mm.close()
		self.f.close()

def print_commands(cmds):
	print("  Available commands:")
	for cmd in cmds:
		print(cmd["name"].rjust(25), end="")
		for  arg in cmd["args"]:
			print(" <"+arg[0]+">", end="")
		print()
		print(" "*26+cmd["desc"])
		for arg in cmd["args"]:
			print(" "*26+(arg[0]+": ").ljust(15)+arg[1])
		print()

# arguments:
#   file: file to write to
#   text: text to write into that file
# returns:
#   nothing
def echo(file, text, fake=False):
	f = open(file, "w")
	if (fake):
		print(file+": "+text)
	else:
		f.write(text+'\n')
	f.close()

def nodeid():
	return (read_reg("extoll_rf_info_rf_node_raw")[0]>>24) & 0xffff

def set_interval(num, start, end, control):
	write_reg("extoll_rf_smfu_rf_interval_startaddr_raw", [num, start])
	write_reg("extoll_rf_smfu_rf_interval_endaddr_raw", [num, end])
	write_reg("extoll_rf_smfu_rf_interval_control_raw", [num, control])

def parse_size(str):
	def suffix(val, suf):
		if (suf == "B"):
			return int(val)
		elif (suf == "K"):
			return int(val * 1024)
		elif (suf == "M"):
			return int(val * 1024 * 1024)
		elif (suf == "G"):
			return int(val * 1024 * 1024 * 1024)
		elif (suf == "T"):
			return int(val * 1024 * 1024 * 1024 * 1024)
		elif (suf == "P"):
			return int(val * 1024 * 1024 * 1024 * 1024 * 1024)

	if (str[-1] in ( "B", "K", "M", "G", "T", "P")):
		return suffix(float(str[:-1]), str[-1])
	elif (str[-2:] in ( "KB", "MB", "GB", "TB", "PB")):
		return suffix(float(str[:-2]), str[-2])
	else:
		try:
			return int(ast.literal_eval(str))
		except:
			raise Exception("Not a valid size: %s" % str)

# contain total number of seconds contained in a duration passed as a timedelta
# not built-in before python version 2.7
def total_seconds(td):
	return (td.microseconds + (td.seconds + td.days * 24 * 3600) * 10**6) / 10.**6

def format_size(num):
	for x in ['B','KB','MB','GB','TB', 'PB']:
		if num < 1024.0:
			return "%s%s" % (round(num, 3), x)
		num /= 1024.0

def format_duration(duration):
	if (duration >= 1.):
		for x in [ ['s', 1., 60],
			   ['m', 60., 60],
			   ['h', 60*60., 24],
			   ['d', 60*60*24., 356] ]:
			tmp = duration/x[1]
			if ( tmp < x[2]):
				return "%s%s" % (round(tmp, 3), x[0])
	else:
		for x in [ ['ms', 1000, 1000],
			   ['us', 1000*1000, 1000],
			   ['ns', 1000*1000*1000, 1000] ]:
			tmp = duration*x[1]
			if ( tmp >= 1 and tmp < x[2] or x[2] == 'ns'):
				return "%s%s" % (round(tmp, 3), x[0])

def parse_intervals(str):
	result = []
	intervals = str.split(",")
	for interval in intervals:
		tmp = interval.split(":")
		if (len(tmp) != 2):
			raise Exception("Malformed interval list")
		try:
			tmp[0] = int(ast.literal_eval(tmp[0]))
		except:
			raise Exception("Malformed node id %s" % tmp[0])
		
		try:
			tmp[1] = parse_size(tmp[1])
		except:
			raise Exception("Malformed size: %s" %tmp[1])
		result += [ { 'node': tmp[0], 'size': tmp[1] } ]
	return result

def dump_as_hex(src, length=8):
	result = []
	digits = 4 if isinstance(src, unicode) else 2
	for i in xrange(0, len(src), length):
		s = src[i:i+length]
		hexa = b' '.join(["%0*X" % (digits, ord(x))  for x in s])
		for j in xrange(len(s)/4):
			hexa = hexa[:(j+1)*12+j] + " " + hexa[(j+1)*12+j:]
		text = b''.join([x if 0x20 <= ord(x) < 0x7F else b'.'  for x in s])
		result.append( b"%04X   %-*s   %s" % (i, length*(digits + 1), hexa, text) )
	return b'\n'.join(result)


# arguments:
#   addr: Address that is to search for in mtrr
# returns:
#   None if no mtrr starting at addr is found, index of mtrr starting at addr if such an entry is found
def get_mtrr_reg(addr):
	import re
	expr = "reg(\d+).*base=0x0*%x " % addr
	f = open("/proc/mtrr", "r")
	lines = f.readlines()
	f.close()
	for line in lines:
		match = re.match(expr, line)
		if (match != None):
			return int(match.group(1), 10)
	return None

if __name__ == "__main__":
	main()
