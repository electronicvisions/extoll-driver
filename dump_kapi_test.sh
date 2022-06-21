#!/bin/bash

echo "This script dumps the output of test_kapi.ko to the console the script was invoked in."

tail -f /var/log/kern.log | grep --line-buffered KAPI_TEST &
