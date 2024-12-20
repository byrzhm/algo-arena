#! /bin/bash

# Check if the directory and prefix are provided as arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory> <prefix>"
    exit 1
fi

# Assign arguments to variables
directory=$1
prefix=$2

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Error: Directory $directory does not exist."
    exit 1
fi

# Iterate over all files in the directory
for file in "$directory"/*; do
    # Skip directories
    if [ -f "$file" ]; then
        # Extract the base name of the file
        basename=$(basename "$file")
        # Rename the file with the prefix
        mv "$file" "$directory/$prefix$basename"
    fi
done

echo "Prefix added to all files in $directory."
