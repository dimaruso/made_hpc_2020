#!/bin/bash

# organize FOR loop printing the elements of array
my_array=(apple, banan, "fruit backet", orange)
for val in ${my_array[@]}; do
    echo "$val"
done
