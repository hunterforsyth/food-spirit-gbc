#!/bin/bash

CUR_PWD=$(pwd)

rm -rf build
rm -rf ~/gbc-build
cp -R . ~/gbc-build

cd ~/gbc-build
./make.sh

cd "$CUR_PWD"

cp -R ~/gbc-build/build build
rm -rf ~/gbc-build
