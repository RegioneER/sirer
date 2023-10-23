#!/bin/bash

mvn clean install -PAll -P${1}-paas -DwarName=${1}-paas

cd prototypes/AxmrDoc && mvn clean install -Dconfiguration=paas -DwarName=${1} -P${2} -P${1}-paas && cp target/${1}.war ../../docker/.