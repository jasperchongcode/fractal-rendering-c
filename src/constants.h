
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 900
// #define WINDOW_HEIGHT 600

#define X_MIN -2.0f
#define X_MAX 2.0f
#define Y_MIN -2.0f
#define Y_MAX 2.0f

#define WINDOW_HEIGHT ((int)(((Y_MAX - Y_MIN) / (X_MAX - X_MIN)) * WINDOW_WIDTH))

#define MAX_STEPS 200