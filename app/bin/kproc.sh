#!/bin/sh
#..................
if [ $# -lt 1 ]
then
  echo "..........procedure_name"
  exit 1
fi

PROCESS=`ps -e|grep $1|grep -v grep|grep -v kproc.sh|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill the $1 process [ $i ]"
  kill  $i
done
