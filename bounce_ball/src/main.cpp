#include <iostream>
#include <cmath>
using namespace std;

// Define constants
const double PI = 3.141592653589793;
const double DEG_TO_RAD = PI / 180.0;
const double RAD_TO_DEG = 180.0 / PI;
const double ROOM_SIZE = 20.0; // The length of the room's side
const double SPEED = 1.0; // The speed of the ball
const double THETA_0 = 41.9872; // The initial angle of the ball in degrees
const int N = 25; // The number of hits to the walls

// Define a struct to store the position and angle of the ball
struct Ball {
    double x; // The x-coordinate of the ball
    double y; // The y-coordinate of the ball
    double theta; // The angle of the ball in degrees
};

// Define a function to calculate the distance between two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Define a function to calculate the time it takes for the ball to hit a wall
double timeToHitWall(Ball b) {
    // Calculate the x and y components of the velocity vector
    double vx = SPEED * cos(b.theta * DEG_TO_RAD);
    double vy = SPEED * sin(b.theta * DEG_TO_RAD);

    // Calculate the time it takes for the ball to hit each wall
    double t_left = (b.x + ROOM_SIZE / 2) / -vx;
    double t_right = (ROOM_SIZE / 2 - b.x) / vx;
    double t_bottom = (b.y + ROOM_SIZE / 2) / -vy;
    double t_top = (ROOM_SIZE / 2 - b.y) / vy;

    // Return the minimum positive time among them
    double t_min = INFINITY;
    if (t_left > 1e-3 && t_left < t_min) t_min = t_left;
    if (t_right > 1e-3 && t_right < t_min) t_min = t_right;
    if (t_bottom > 1e-3 && t_bottom < t_min) t_min = t_bottom;
    if (t_top > 1e-3 && t_top < t_min) t_min = t_top;
    return t_min;
}

// Define a function to update the position and angle of the ball after hitting a wall
void updateBall(Ball &b) {
    // Calculate the time it takes for the ball to hit a wall
    double t = timeToHitWall(b);

    // Calculate the new position of the ball after hitting a wall
    b.x += SPEED * cos(b.theta * DEG_TO_RAD) * t;
    b.y += SPEED * sin(b.theta * DEG_TO_RAD) * t;

    // Calculate the new angle of the ball after hitting a wall
    if (abs(b.x + ROOM_SIZE / 2) < 1e-6 || abs(b.x - ROOM_SIZE / 2) < 1e-6) {
        // The ball hit a vertical wall, so reflect its angle over the y-axis
        b.theta = 180 - b.theta;
    } else {
        // The ball hit a horizontal wall, so reflect its angle over the x-axis
        b.theta = -b.theta;
    }

    // Normalize the angle to be between 0 and 360 degrees
    while (b.theta < 0) b.theta += 360;
    while (b.theta >= 360) b.theta -= 360;
}

// Define a function to print the details of the ball before and after hitting a wall
void printBall(Ball b_before, Ball b_after, int hit) {

    // Modify this line to remove unnecessary spaces and labels in the output
    cout << hit << " " << b_before.x << " " << b_before.y << " " << b_before.theta << " "
         << b_after.x << " " << b_after.y << " " << b_after.theta << endl;
}

// Define the main function
int main() {
    // Initialize the ball at the center of the room with the initial angle
    Ball b;
    b.x = 0.0;
    b.y = 0.0;
    b.theta = THETA_0;

    // Initialize a variable to store the total distance traveled by the ball
    double total_distance = 0.0;

    // Initialize a variable to store the number of hits to the walls
    int hit = 0;

    // Loop until the ball hits N times to the walls
    while (hit < N) {
        // Store the position and angle of the ball before hitting a wall
        Ball b_before = b;

        // Update the position and angle of the ball after hitting a wall
        updateBall(b);

        // Store the position and angle of the ball after hitting a wall
        Ball b_after = b;

        // Print the details of the ball before and after hitting a wall
        printBall(b_before, b_after, hit + 1);

        // Calculate the distance traveled by the ball in this hit
        double d = distance(b_before.x, b_before.y, b_after.x, b_after.y);

        // Add the distance to the total distance
        total_distance += d;

        // Increment the number of hits
        hit++;
    }

    // Print the total distance traveled by the ball after N hits
    cout << "Total distance: " << total_distance << endl;

    return 0;
}

