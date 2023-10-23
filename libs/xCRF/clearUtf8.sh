#!/bin/sh
cp $1 $1.presed
sed -i 's///g' $1
mv *.presed presed/.

