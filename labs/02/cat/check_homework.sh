#!/bin/bash

STUDENT_ID=$1

MODE=$2

echo "Converting to Unix .."
dos2unix patches/* > /dev/null 2>&1

echo "Testing Student: $STUDENT_ID ... " 
echo 

# Clean white spaces in patches
# find patches/ -depth -name "* *" -execdir rename 's/ /_/g' "{}" \;

PATCH=$(find patches/ -iname *$STUDENT_ID*.eml)
echo $PATCH


if [ -z "$MODE" ]
then
    git apply --check $PATCH
else
    git am $PATCH
fi

if [ $? -eq 0 ]
then
    echo "Patch Successfully applied"
    echo $STUDENT_ID >> patches_applied
else
    echo "Could not apply patch"
    echo $STUDENT_ID >> patches_not_applied
fi

make

if [ $? -eq 0 ]
then
    echo "Build :) "
    echo $STUDENT_ID >> patches_build
else
    echo "Could not build"
    echo $STUDENT_ID >> patches_not_build
fi

./homework_cat file.txt

if [ $? -eq 0 ]
then
    echo "cat Works !!"
else
    echo "cat does not work"
fi

./cat_sys_call file.txt

if [ $? -eq 0 ]
then
    echo "cat (syscall) Works !!"
else
    echo "cat (syscall) does not work"
fi

