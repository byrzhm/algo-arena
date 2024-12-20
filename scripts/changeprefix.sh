#! /bin/bash

# Check if the directory, old prefix, and new prefix are provided as arguments
if [ $# -ne 3 ]; then
    echo "Usage: $0 <directory> <old_prefix> <new_prefix>"
    exit 1
fi

# Assign arguments to variables
directory=$1
old_prefix=$2
new_prefix=$3

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

        # Check if the file name starts with the old prefix
        if [[ "$basename" == "$old_prefix"* ]]; then
            # Remove the old prefix and add the new prefix
            new_name="$new_prefix${basename#"$old_prefix"}"
            # Rename the file
            mv "$file" "$directory/$new_name"
        fi
    fi
done

echo "Prefix changed from '$old_prefix' to '$new_prefix' in $directory."
