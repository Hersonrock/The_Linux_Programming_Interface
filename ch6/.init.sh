#!/usr/bin/env bash

projectName=$1
mkdir ./$1
mkdir ./$1/bin
mkdir ./$1/include
mkdir ./$1/src
cp ./.makefile ./$1/makefile
touch ./$1/readme
echo "----README----" > ./$1/readme
