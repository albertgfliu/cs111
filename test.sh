#!/bin/bash

#put test cases here
./simpsh --rdonly a
./simpsh --wronly b
./simpsh --command
./simpsh --verbose

echo $?
