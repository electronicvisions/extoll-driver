/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2016 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2016)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _EXTOLL_RF_ACCESS_H_
#define _EXTOLL_RF_ACCESS_H_

struct extoll2_rf_context {
   int node;
   int addr;
   int write_mode;
   int read_mode;
   uint64_t timeout;
};

typedef struct extoll2_rf_context extoll2_rf_context_t;

/* first open a context to perform RRA in the kernel */
extoll2_rf_context_t* extoll2_rf_rra_open(void);
/* close when done */
int extoll2_rf_rra_close(extoll2_rf_context_t* context);
/* call seek to set node and address to be accessed */
void extoll2_rf_rra_seek(extoll2_rf_context_t* context, int node, int address);
/* read and write functions */
int extoll2_rf_rra_write(extoll2_rf_context_t* context, uint64_t value);
int extoll2_rf_rra_read(extoll2_rf_context_t* context, uint64_t* value);

/* set the timeout of a rma based rra read to <value> usec */
int extoll2_rf_rra_set_read_timeout(extoll2_rf_context_t* context, uint64_t value);

/*To set the access methods, access the write_mode and read_mode fields of extoll2_rf_context_t directly.
 *   Valid values are defined in extoll_rf_access_ioctl.h
 */


#endif
