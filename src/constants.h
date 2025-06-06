
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 1200
// #define WINDOW_HEIGHT 600
// Have 16:9 aspect ratio
#define DEFAULT_X_MIN -(32.0f / 9)
#define DEFAULT_X_MAX (32.0f / 9)
#define DEFAULT_Y_MIN -2.0f
#define DEFAULT_Y_MAX 2.0f

#define WINDOW_HEIGHT ((int)(((DEFAULT_Y_MAX - DEFAULT_Y_MIN) / (DEFAULT_X_MAX - DEFAULT_X_MIN)) * WINDOW_WIDTH))

#define MAX_STEPS 100
#define SAMPLE_GRID_WIDTH 2 // makes a grid 2 high and 2 wide for sampling each pixel

#define IMAGE_WIDTH 3840
#define IMAGE_SAMPLE_GRID_WIDTH 4