#!/bin/bash
result=`python file.py "hi"`
if [ "$result" == "Salaam" ]; then
  echo "script return correct response"
fi

