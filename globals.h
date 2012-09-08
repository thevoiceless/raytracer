#pragma once

#ifdef MAINFILE
    #define EXTERN
#else
    #define EXTERN extern
#endif

// Global variables
EXTERN double viewpoint[3];
EXTERN double screen_lower_left_corner[3];
EXTERN double screen_horizontal_vector[3];
EXTERN double screen_vertical_vector[3];
EXTERN double light_source[3];
EXTERN double light_intensity;
EXTERN double ambient_light_intensity, resolution_x, resolution_y;
EXTERN int number_of_primitives;