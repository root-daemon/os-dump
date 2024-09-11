#!/bin/bash

# Check if a pattern is passed as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <pattern>"
    exit 1
fi

# Assign the first argument to the pattern variable
pattern="$1"

# Loop through all files in the present working directory
for file in *; do
    # Check if the item is a file
    if [ -f "$file" ]; then
        # Use grep to check if the pattern exists in the file
        if grep -q "$pattern" "$file"; then
            echo "Pattern found in $file"
        else
            echo "Pattern not found in $file"
        fi
    fi
done
