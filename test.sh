#!/bin/bash

#put test cases here
./simpsh --rdonly a --wronly b --pipe --rdonly c
if [ $? -ne 0 ]; then
	echo "Test 1 failed (temporary)"
	exit
else
	echo "Test 1 success"
fi
