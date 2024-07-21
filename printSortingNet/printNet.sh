#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 lenght"
  exit 1
else
    lenght=$1
    make
    ./bin/printNet $lenght
    python3 visualPrint.py
fi