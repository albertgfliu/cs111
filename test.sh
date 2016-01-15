#!/bin/bash

#put test cases here
touch a b c d
echo "./simpsh --verbose --rdonly a --wronly b --wronly c"
./simpsh --verbose --rdonly a --wronly b --wronly c
if [ $? -ne 0 ]; then
	echo "Test 1 had errors "
else
	echo "Test 1 success"
fi

echo "./simpsh --verbose --rdonly a --wronly b --rdonly c"
./simpsh --verbose --rdonly a --wronly b --rdonly c
if [ $? -ne 0 ]; then
	echo "Test 2 had errors "
else
	echo "Test 2 success"
fi

echo "./simpsh --verbose --rdonly a --wronly b --rdonly c --command 0 1 2 cat a -"
./simpsh --verbose --rdonly a --wronly b --rdonly c --command 0 1 2 cat a -
if [ $? -ne 0 ]; then
	echo "Test 3 had errors "
else
	echo "Test 3 success"
fi
