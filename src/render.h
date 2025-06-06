#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"
extern Complex C;

// extern float offsets_x[SAMPLE_GRID_WIDTH];
// extern float offsets_y[SAMPLE_GRID_WIDTH];
extern float y_max;
extern float y_min;
extern float x_max;
extern float x_min;

void render_fractal(void);
void initialise_offsets(void);
void render_save_fractal(char *, int, int);

#endif