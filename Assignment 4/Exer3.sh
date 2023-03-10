#! /bin/bash

listOfItems=$(find *.jpg)
for imageName in $listOfItems
do
  mv $imageName $(date +"%d-%m-%Y")-$imageName
done