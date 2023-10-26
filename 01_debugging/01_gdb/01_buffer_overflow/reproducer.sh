#!/bin/bash

rm sample.out

# Build the sample
make

inputs=(
    "foo"
    "notfoo"
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwww"
)

for input in "${inputs[@]}"; do
    echo "testing input: $input"
    echo "------------------"
    echo "$input" | SECRET=foo ./sample
    echo "------------------"
    echo "$input" | DEBUG="" SECRET=foo ./sample
    echo "------------------"
done
