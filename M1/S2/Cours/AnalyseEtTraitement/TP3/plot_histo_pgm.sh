#!/bin/bash

# Check if input file is provided
if [ -z "$1" ]; then
  echo "Error: No input file specified."
  echo "Usage: $0 <input_file> [output_file]"
  exit 1
fi

# Assign input and output file names
INPUT_FILE="$1"
OUTPUT_FILE="${2:-pgm_histogram.png}"  # Default to 'pgm_histogram.png' if no output file is provided

# Check if the input file exists
if [ ! -f "$INPUT_FILE" ]; then
  echo "Error: Input file '$INPUT_FILE' not found."
  exit 1
fi

# Generate the histogram using Gnuplot
gnuplot <<EOF
# Set the terminal to PNG with size
set terminal pngcairo size 800,600 enhanced font 'Arial,12'

# Output the plot to the file
set output "$OUTPUT_FILE"

# Add labels and title
set title "PGM Image Histogram"
set xlabel "Valeur"
set ylabel "Ocurrences"

# Set grid
set grid

# Plot the histogram
plot "$INPUT_FILE" using 1:2 with lines lc rgb "black" title "Histogram"

# Close the output
unset output
EOF

# Check if the output file was created
if [ -f "$OUTPUT_FILE" ]; then
  echo "PGM histogram saved as '$OUTPUT_FILE'."
else
  echo "Error: Failed to save the histogram."
  exit 1
fi
