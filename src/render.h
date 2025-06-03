#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"
extern Complex C;

extern float offsets_x[SAMPLE_GRID_WIDTH];
extern float offsets_y[SAMPLE_GRID_WIDTH];

void render_fractal(void);
void initialise_offsets(void);
void render_fractal_image(int, int);

#endif