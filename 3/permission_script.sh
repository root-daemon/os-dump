#!bin/bash
file_path="text.txt"

if [-x "$file_path"]; then
  echo "The file has execute permission"
else
  
