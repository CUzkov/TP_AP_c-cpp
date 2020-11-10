#!/bin/bash
str=$(ls -la | grep $1)
if [[ -z "$str" ]]
then
    echo 1
else
    echo 0
fi
