#ifndef MANDELBROT_H
#define MANDELBROT_H

/**
 * Returns the number of iterations (0..MAX_STEPS) needed for
 * z_{n+1} = z_n^2 + (re + i·im) to escape (|z| ≥ 2).
 * If it never escapes within MAX_STEPS, returns MAX_STEPS.
 */
int verify_in_mandelbrot(float re, float im);

#endif /* MANDELBROT_H */
