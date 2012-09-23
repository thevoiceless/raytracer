# CSCI441 Project 1 - Raytracer
## Compilation and Usage
To compile, simply run "make". This will create a single "raytrace" executable.
There are two ways to run the raytracer:
	1. Run "./raytrace" with no command-line arguments; This will automatically look for an input file named "input.txt" in the current directory.
	2. Run "./raytrace input_file_name" where "input_file_name" is the full (including the file extension) name of a file in the current directory to use as input.
## Notes
This raytracer is extremely slow. Seriously. Everything is done with the CPU, and the code itself is very inefficient (but works). I might go back at some point and clean it up (like passing all objects by reference), or I might not. 