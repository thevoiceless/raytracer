# CSCI441 Project 1 - Raytracer

## Compilation and Usage
To compile, simply run "make". This will create a single "raytrace" executable.
There are two ways to run the raytracer:

1.  Run "./raytrace" with no command-line arguments; This will automatically look for an input file named "input.txt" in the current directory.

2.  Run "./raytrace input_file_name" where "input_file_name" is the full (including the file extension) name of a file in the current directory to use as input.

## Input File Format
The input ﬁle will specify the view, window size, light source and the primitives (triangles and spheres), in the following order:

1. The desired resolution of the output image (two integers, m and n if the output is to be m × n)
2. The coordinates of the viewpoint e (three ﬂoats)
3. The screen data: l (lower left corner), h and v (vectors running along the horizontal and vertical edges)
4. The light source (b, the coordinates and I, the intensity)
5. The ambient light intensity
6. Number of primitives
7. List of primitives (spheres and triangles)

The list of primitives consists of a number of primitive records. A primitive record starts with a letter, S for a sphere and T for a triangle.  
For a sphere, the next line contains the coordinates of the center and the radius (4 ﬂoats). The follwoing line contains the material description (8 ﬂoats): kdr, kdg, kdb, kar, kag, kab, ks and nspec. The ﬁrst three are the diﬀuse reﬂection coeﬃcients for red green and blue components, then come the ambient reﬂection coeﬃcients and the specular coeﬃcient and exponent. There are no separate RGB components for the specular coeﬃcient; the same value is used for all of them (i.e. ksr = ksg = ksb = ks).  
For a triangle, the next three lines contain the coordinates of each of the three vertices (9 ﬂoats). The fourth line contains the material properties in the same format as for spheres.
The input ﬁles are designed so that the intensity of a pixel should never exceed 1 (except possibly for a tiny amount due to numerical error).

Thus, the starting portion of the ﬁle will look like this:

m n  
ex ey ez  
lx ly lz  
hx hy hz  
vx vy vz  
bx by bz I  
Ia  
N

Then come the primitives. For a sphere:

S  
cx cy cz r  
kdr kdg kdb kar kag kab ks nspec

And for a triangle:

T  
a1x a1y a1z  
a2x a2y a2z  
a3x a3y a3z  
kdr kdg kdb kar kag kab ks nspec

## Output

If an input file is passed as a command-line argument, a PPM file with a matching name is created. If no input file is specified, the resulting file is just named "output.ppm".

## Notes
This raytracer is extremely slow. Seriously. Everything is done with the CPU, and the code itself is very inefficient (but works). I might go back at some point and clean it up (like passing all objects by reference), or I might not. 