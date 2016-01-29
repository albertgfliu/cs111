#!/bin/bash

#put test cases here
touch a b c d

#test file flag options
echo "./simpsh --creat a"
./simpsh --creat a
if [ $? -eq 0 ]; then
	echo "Test 1 had errors "
else
	echo "Test 1 success"
fi

echo "./simpsh --creat --rdonly a"
./simpsh --creat --rdonly a
if [ $? -ne 0 ]; then
	echo "Test 2 had errors "
else
	echo "Test 2 success"
fi

echo "./simpsh --excl --creat --rdonly a"
./simpsh --excl --creat --rdonly a
if [ $? -eq 0 ]; then
	echo "Test 3 had errors "
else
	echo "Test 3 success"
fi

#test file open options
echo "./simpsh --verbose --rdonly a --wronly b --wronly c"
./simpsh --verbose --rdonly a --wronly b --wronly c
if [ $? -ne 0 ]; then
	echo "Test 4 had errors "
else
	echo "Test 4 success"
fi

echo "./simpsh --verbose --rdonly a --wronly b --rdonly c"
./simpsh --verbose --rdonly a --wronly b --rdonly c
if [ $? -ne 0 ]; then
	echo "Test 5 had errors "
else
	echo "Test 5 success"
fi

#test --command option
echo "./simpsh --verbose --rdonly a --wronly b --rdonly c --command 0 1 2 cat a -"
./simpsh --verbose --rdonly a --wronly b --rdonly c --command 0 1 2 cat a -
if [ $? -ne 0 ]; then
	echo "Test 6 had errors "
else
	echo "Test 6 success"
fi


