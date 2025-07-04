
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 1200

// Have 16:9 aspect ratio
#define DEFAULT_X_MIN -(32.0 / 9)
#define DEFAULT_X_MAX (32.0 / 9)
#define DEFAULT_Y_MIN -2.0
#define DEFAULT_Y_MAX 2.0

#define WINDOW_HEIGHT ((int)(((DEFAULT_Y_MAX - DEFAULT_Y_MIN) / (DEFAULT_X_MAX - DEFAULT_X_MIN)) * WINDOW_WIDTH))

#define DEFAULT_MAX_STEPS 100
#define SAMPLE_GRID_WIDTH 2 // makes a grid 2 high and 2 wide for sampling each pixel

#define IMAGE_WIDTH 3840
#define IMAGE_SAMPLE_GRID_WIDTH 4

#define ZOOM_FACTOR 1.05f
#define ZOOM_INCREASE_FACTOR 1.5f // Factor applied when using shift+zoom