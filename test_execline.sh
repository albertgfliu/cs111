#!/usr/local/cs/execline-2.1.4.5/bin/execlineb

# (sort a | tr A-Z a-z >c ) 2> d
pipeline {
	sort a
}
redirfd -w 1 c tr a-z A-Z

