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

#test --abort option
echo "./simpsh --abort --rdonly a"
./simpsh --abort --rdonly a
if [ $? -eq 0 ]; then
	echo "Test 7 had errors "
else
	echo "Test 7 success"
fi

#test --close option
echo "./simpsh --rdonly a --wronly b --close 1 --wronly c --command 0 1 2 cat"
./simpsh --rdonly a --wronly b --close 1 --wronly c --command 0 1 2 cat
if [ $? -eq 0 ]; then
	echo "Test 8 had errors "
else
	echo "Test 8 success"
fi

#test --catch option
echo "./simpsh --catch 11 --abort"
./simpsh --catch 11 --abort
if [ $? -ne 11 ]; then
	echo "Test 9 had errors "
else
	echo "Test 9 success"
fi


#test --ignore option
echo "./simpsh --ignore 11 --abort --creat --rdonly e"
./simpsh --ignore 11 --abort --creat --rdonly e
if [ $? -ne 0 ]; then
	echo "Test 10 had errors "
else
	echo "Test 10 success"
fi


