#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"
extern Complex C;

extern double y_max;
extern double y_min;
extern double x_max;
extern double x_min;

void render_fractal(void);
void initialise_offsets(void);
void render_save_fractal(char *, int, int);

#endif