#!/bin/bash

# List only the names of subdirectories in the present working directory
for item in *; do
    if [ -d "$item" ]; then
        echo "$item"
    fi
done
