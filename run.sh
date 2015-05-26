#!/bin/bash

if [[ $# -lt 3 ]] ;
then
  echo "Usage: ./run.sh <MSI,MESI,NoCoherent> <number_of_caches> <path_to_executable_bechmark>"
  exit 0
fi

echo "Running Simulator with $1 Protocol";
if [ $1 = "MSI" ]
then
	time pin -t obj-intel64/MultiCacheSimulator.so -protos obj-intel64/MSI_SMPCache.so -numcaches $2 -- $3 $4 $5 $6
elif [ $1 = "MESI" ]
then
	time pin -t obj-intel64/MultiCacheSimulator.so -protos obj-intel64/MESI_SMPCache.so -numcaches $2 -- $3 $4 $5 $6
elif [ $1 = "NoCoherent" ]
then
	time pin -t obj-intel64/MultiCacheSimulator.so -protos obj-intel64/NoCoherent_SMPCache.so -numcaches $2 -- $3 $4 $5 $6
else
  echo "Bad argument"
  echo "Usage: ./run.sh <MSI,MESI,NoCoherent> <number of caches> <path to	executable bechmark>"
fi
