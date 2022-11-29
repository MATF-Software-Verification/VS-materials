#!/bin/bash

# measure_time.sh

##############################################################################
# Copyright (c) 2018, Ana Spasic
# This program and the accompanying materials are made
# according with curriculum of the master course Software Verification, 
# tought on Faculty of Mathematics, University of Belgrade, Serbia. 
# 
# Script run klee on various files named exN-[1|2|v].c
# and write klee statistics in report named after search method.
# N represents number  of symbolic variables in program.
# 1 and 2 have division by 0 on different paths, and v version do not have that error.
#
# Usage: 
# ./ measure_time [dfs|bfs|random-path|random-state] [yes|no] [file_number_limit] [1|2|v]
#
# dfs|bfs|random-path|random-state - to select search heuristic
#     If it's called without argument it will user default Klee search heuristics. 
# yes|no  -  for demanding generation of paths for each test.
# file_number_limit  -  option to stop testing after files with file_number_limit variables 
# 1|2|v  - version of programs to be executed 
#
# Created under the licence Creative Commons CC BY-NC-ND 4.0
# (Attribution-NonCommercial-NoDerivatives 4.0 International License)
# http://creativecommons.org/licenses/by-nc-nd/4.0/
#############################################################################


KLEE=klee
STAT=klee-stats
SEARCH=""
LIMIT=0
VERSION=""
KLEE_FLAGS="-exit-on-error -optimize"

if [ $# -eq 0 ] ; then
  echo -e "No arguments supplied.\tUse default."
  echo "Usage: measure_time [search method] [paths(yes|no)] [file_no_limit] [1|2|v]"
fi

if  [ $# -lt 2 ]; then
	echo "Usage: measure_time [search method] [paths(yes|no)] [file_no_limit] [1|2|v]"
  exit 
else 
	SEARCH=$1
	if [ $SEARCH != "dfs" ]  && [ $SEARCH != "bfs" ] && [ $SEARCH != "random-path" ] && [ $SEARCH != "random-state" ]  ; then
		echo 'Script can be called for : dfs, bfs, random-path, random-state'
		exit
	else 
			KLEE_FLAGS=$KLEE_FLAGS" --search="$SEARCH
	fi
	if [ $2 == "yes" ] ; then
		KLEE_FLAGS=$KLEE_FLAGS" --write-paths"
	fi
	if [ $# -gt 2 ] ; then
	  LIMIT=$3 
	fi
  if [ $# -gt 3 ] ; then
	  VERSION=$4 
	fi
fi 

#~ for file in ./*.c; do
	 #~ content=$(cat "$file") # no cat abuse this time
	 #~ echo "#include <klee/klee.h>\n\nint $content" >"$file"
#~ done

# generate report file name
if [ "$SEARCH" = "" ]; then
  REPORT=report_default
else
  REPORT=report_$SEARCH
fi  

if [ "$VERSION" = '' ] ; then
  REPORT=$REPORT.txt
else  
  REPORT=$REPORT"_""$VERSION".txt  
fi
  
# delete report if exists
if [ -e $REPORT ]; then
	rm $REPORT
fi
		
# execute and write report		
for file in *.bc; do
  name=${file##ex}
  name=${name%%.*}
  number=${name%%-*}
  version=${name##*-}
    
  if [ $LIMIT -gt 0 ] && [ $number -gt $LIMIT ]; then
    break
  fi
  
  if ! [ "$VERSION" = "" ]  &&  ! [ "$version"  = "$VERSION" ] ; then
    continue;
  fi 
  
   
	echo -e "\n$file\n"
	echo -e "\n\n$file\n" >> $REPORT
	"$KLEE"  $KLEE_FLAGS "$file" 
	"$STAT" klee-last >> $REPORT
done
