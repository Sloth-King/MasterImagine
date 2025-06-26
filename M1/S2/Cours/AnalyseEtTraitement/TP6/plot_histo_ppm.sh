#!/bin/bash

# Check if an input file was provided as an argument
if [ -z "$1" ]; then
  echo "Error: No input file specified."
  echo "Usage: $0 <input_file> [output_file]"
  exit 1
fi

# Define the input file and output file names
INPUT_FILE="$1"
OUTPUT_FILE="${2:-ppm_histogram.png}"

# Check if the input file exists
if [ ! -f "$INPUT_FILE" ]; then
  echo "Error: Input file '$INPUT_FILE' not found."
  exit 1
fi

# Generate the histogram using Gnuplot
gnuplot <<EOF
# Calculate the range of the data
stats "$INPUT_FILE" using 1:2 nooutput name "R"
stats "$INPUT_FILE" using 1:3 nooutput name "G"
stats "$INPUT_FILE" using 1:4 nooutput name "B"

# Set the terminal to PNG with size
set terminal pngcairo size 800,600 enhanced font 'Arial,12'

# Output the plot to the file
set output "$OUTPUT_FILE"

# Add labels and title
set title "PPM Image Histogram"
set xlabel "Valeur"
set ylabel "Occurrences"

# Set grid
set grid

# Dynamically set the x and y ranges based on the data
set xrange [0:255]
set yrange [0:*]

# Plot the histogram
plot "$INPUT_FILE" using 1:4 with lines lc rgb "blue" title "Bleu", \
     '' using 1:2 with lines lc rgb "red" title "Rouge", \
     '' using 1:3 with lines lc rgb "green" title "Vert"

# Close the output
unset output
EOF

# Check if the output file was created
if [ -f "$OUTPUT_FILE" ]; then
  echo "PPM histogram saved as '$OUTPUT_FILE'."
else
  echo "Error: Failed to save the histogram."
  exit 1
fi
