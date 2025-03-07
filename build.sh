#!/usr/bin/env bash

cd $(dirname $0)

BUILD_DIR='./build'
SRC_DIR='./examples'

mkdir -p "$BUILD_DIR"

for source_file in $SRC_DIR/*.c; do
    program_name="$(echo $source_file | grep -Po '[^/]*(?=\.c$)')"
    echo "Build example '$program_name'"
    gcc -Wall -Wextra -Wconversion -Wshadow -Wundef -Wunused \
        -I. \
        -lcurl \
        -std=gnu23 \
        "$source_file" -o "$BUILD_DIR/$program_name"
done

echo Done
