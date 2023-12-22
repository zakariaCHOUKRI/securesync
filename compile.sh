#!/bin/bash

# Set the compiler
COMPILER=g++

# Set the include directory
INCLUDE_DIR=./include

# Set the source directory
SRC_DIR=./src

# Set the output directory
OUTPUT_DIR=./

# Set the executable name
EXECUTABLE=myProgram

# Find all .cpp files in the source directory
CPP_FILES=$(find $SRC_DIR -name "*.cpp")

# Initialize an empty string for object files
OBJ_FILES=""

# Compile each .cpp file
for FILE in $CPP_FILES; do
    OBJ_FILE="${FILE%.cpp}.o"
    # echo "$OBJ_FILE"
    $COMPILER -I$INCLUDE_DIR -c $FILE -o $OBJ_FILE
    OBJ_FILES="$OBJ_FILES $OBJ_FILE"
done

# Link object files into a single executable
$COMPILER -o $OUTPUT_DIR/$EXECUTABLE $OBJ_FILES

# Remove object files after linking
rm $OBJ_FILES

# Print completion message
echo "Compilation finished. Executable created: $OUTPUT_DIR/$EXECUTABLE"
