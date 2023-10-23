#!/bin/bash
userService='Ianus'
export JAVA_HOME=/usr/lib/jvm/adoptopenjdk-8-hotspot-amd64
[ ! -z "$2" ] && userService=$2

chmod oug+x mvnw
./mvnw install -PAll -P${1}-paas -DwarName=${1}-paas 
cd prototypes/AxmrDoc && ../../mvnw clean install -Dconfiguration=paas -DwarName=${1}-paas -P${1}-paas -P$userService && cd ../.. 
rm -rf dist
mkdir -p dist && cp prototypes/AxmrDoc/target/${1}-paas.war dist/.
cp docker/* dist/.
sed -i 's/__WARNAME__/'${1}'/g' dist/Dockerfile
sed -i 's/__AMBIENTE__/'${3}'/g' dist/Dockerfile
sed -i 's!__FTL_REPO__!'${4}'!g' dist/Dockerfile