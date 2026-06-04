// Desing an structure for circle.
// Draw a circle on of * on the screen.
// Hint use a 2d buffer.
// Modularise into at least 4 functions.
#include <stdio.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 30

/* 1. Design a structure for the circle */
typedef struct {
    int center_x;
    int center_y;
    int radius;
} Circle;

/* Function Prototypes */
void init_buffer(char buffer[HEIGHT][WIDTH]);
int is_on_circle(int x, int y, Circle c);
void draw_circle(char buffer[HEIGHT][WIDTH], Circle c);
void print_buffer(char buffer[HEIGHT][WIDTH]);

int main() {
    char screen[HEIGHT][WIDTH];
    
    // Define our circle
    Circle my_circle = {
        .center_x = WIDTH / 2,
        .center_y = HEIGHT / 2,
        .radius = 12
    };

    // Execute the modularized rendering pipeline
    init_buffer(screen);
    draw_circle(screen, my_circle);
    print_buffer(screen);

    return 0;
}

/* FUNCTION 1: Initialize the buffer with blank spaces */
void init_buffer(char buffer[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer[y][x] = ' ';
        }
    }
}

/* FUNCTION 2: The Math - Check if a coordinate lies on the circle's edge */
int is_on_circle(int x, int y, Circle c) {
    // Calculate distance from center (dx, dy)
    float dx = (float)(x - c.center_x);
    
    // Multiply dy by 2.0 to correct the terminal character aspect ratio!
    // Without this, the circle becomes a vertical oval.
    float dy = (float)(y - c.center_y) * 2.0f; 
    
    // Calculate Pythagorean distance
    float distance = sqrt(dx * dx + dy * dy);
    
    // If the distance is close to the radius (give or take 1 unit of thickness),
    // it belongs to the circle's outline.
    if (distance >= c.radius - 1.0f && distance <= c.radius + 1.0f) {
        return 1; // True
    }
    return 0; // False
}

/* FUNCTION 3: Plot the circle into the 2D memory buffer */
void draw_circle(char buffer[HEIGHT][WIDTH], Circle c) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (is_on_circle(x, y, c)) {
                buffer[y][x] = '*';
            }
        }
    }
}

/* FUNCTION 4: Render the buffer to the standard output */
void print_buffer(char buffer[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(buffer[y][x]);
        }
        putchar('\n');
    }
}
