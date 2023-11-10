#!/bin/bash

# generateCodeCoverageReport.sh

##############################################################################
# Copyright (c) 2018, Ana Spasic
# This program and the accompanying materials are made
# according with curriculum of the master course Software Verification,
# tought on Faculty of Mathematics, University of Belgrade, Serbia.
#
# Script run test and generate code coverage report using lcov for QTproject
# that is already build and linked with gcov option for gcc or g++
# -g -Wall -fprofile-arcs -ftest-coverage -O0
# and linked with lgcov
#
# Or simply compiled with option --coverage and -O0 to disable optimization,
# for example:
# g++ -o menu.out --coverage -O0 menu.cpp
#
# Created under the licence Creative Commons CC BY-NC-ND 4.0
# (Attribution-NonCommercial-NoDerivatives 4.0 International License)
# http://creativecommons.org/licenses/by-nc-nd/4.0/
#############################################################################

if [ $# -lt 2 ]; then
  echo "usage: ${0}  <dir_with_coverage files> <executable> [<target-dir>]"
  exit 0
else
  if  [ $# -eq 2 ]; then
    # not said otherwise, target_dir is source directory
    TARGET_DIR="${1}"
  else
    TARGET_DIR="${3}"

    if [ ! -d "$TARGET_DIR" ]; then
      echo "$TARGET_DIR doesn't exists. WIll be created."
      mkdir $TARGET_DIR
    fi

    if [[ $TARGET_DIR == */ ]]; then
      #remove / at the ending
      TARGET_DIR=${TARGET_DIR:0:${#TARGET_DIR}-1}
    fi
  fi  
fi

TEST=${2}
SOURCE_DIR="${1}"

BROWSER=firefox

if [ ! -d "$SOURCE_DIR" ]; then
  echo "$SOURCE_DIR doesn't exists. Exiting."
  exit 1
fi

if [[ $SOURCE_DIR == */ ]]; then
  #remove / at the ending
    SOURCE_DIR=${SOURCE_DIR:0:${#SOURCE_DIR}-1}
fi

# check if there are gcno files in source_dir

if [ ! -e ${SOURCE_DIR}/*.gcno ]; then
    if [ ! -e ${SOURCE_DIR}/Makefile ]; then
      echo -e "\e[31mThere are no .gcno files to create coverage. Check your compilation parameters and compile program again."
      exit 0
    else
      CURRENT_DIR=${PWD}
      echo  "\e[35mThere are no .gcno files to create coverage. Building project again."
      cd ${SOURCE_DIR}
      make -B
      cd ${CURRENT_DIR}
     
      # Do we have it now?
      if [ ! -e ${SOURCE_DIR}/*.gcno ]; then
        echo -e "\e[31mThere are no .gcno files to create coverage. Check your compilation parameters and compile program again."
        exit 0
      fi
    fi
fi


# clear source_dir from gcda files from previous runs
lcov -z -d $SOURCE_DIR

# create initial coverage report filled with zeroes
lcov -c -i -d $SOURCE_DIR -o $TARGET_DIR/coverage-init.info

echo""
echo "Run tests"
# run tests
./$SOURCE_DIR/$TEST

echo ""
echo "Create coverage:"
echo ""
# create coverage report for the test
lcov --rc branch_coverage=1  -c -d $SOURCE_DIR -o $TARGET_DIR/coverage-test.info

#combine with previous coverage-init
lcov -a $TARGET_DIR/coverage-init.info -a $TARGET_DIR/coverage-test.info --rc branch_coverage=1 -o $TARGET_DIR/coverage.info

# remove system files from coverage, because we do not try to cover them
lcov --rc branch_coverage=1 -r $TARGET_DIR/coverage.info '/usr/*' '*.moc' -o $TARGET_DIR/coverage-filtered.info

echo ""
echo "Generate HTML for coverage:"
echo ""
#create html report from filtered coverage
genhtml --rc branch_coverage=1 -legend -o $TARGET_DIR/Reports $TARGET_DIR/coverage-filtered.info

#view report in brower
$BROWSER $TARGET_DIR/Reports/index.html &
