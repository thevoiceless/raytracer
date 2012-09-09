#pragma once

#ifdef MAINFILE
    #define EXTERN
#else
    #define EXTERN extern
#endif

// Global variables
EXTERN Vector viewpt;
EXTERN Vector screenLowerLeftCorner;
EXTERN Vector screenHorizVector;
EXTERN Vector screenVertVector;
EXTERN Vector lightSource;
EXTERN double light_intensity;
EXTERN double ambient_light_intensity, resolution_x, resolution_y;
EXTERN int number_of_primitives;