
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 1200
// #define WINDOW_HEIGHT 600

#define X_MIN -3.0f
#define X_MAX 3.0f
#define Y_MIN -2.0f
#define Y_MAX 2.0f

#define WINDOW_HEIGHT ((int)(((Y_MAX - Y_MIN) / (X_MAX - X_MIN)) * WINDOW_WIDTH))

#define MAX_STEPS 100
#define SAMPLE_GRID_WIDTH 2 // makes a grid 2 high and 2 wide for sampling each pixel

#define IMAGE_WIDTH 3840
#define IMAGE_SAMPLE_GRID_WIDTH 2