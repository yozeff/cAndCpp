//Joseph Harrison 2019
//approximating pi
#include <iostream>
#include <math.h>

using namespace std;

//struct stores 2D position vectors
typedef struct Vector2 {
    float x;
    float y;
} vector2_t ;

void randomise_vector(vector2_t * rptr)
{
    //generate components between -0.5 and 0.5
    rptr -> x = static_cast<float>(rand() / static_cast<float>(RAND_MAX)) - 0.5;
    rptr -> y = static_cast<float>(rand() / static_cast<float>(RAND_MAX)) - 0.5;
}

//check if point lies in circle: r = 0.5, o = (0, 0)
bool in_circle(vector2_t * rptr)
{
    if (hypot(rptr -> x, rptr -> y) <= 0.5) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char ** argv)
{
    int iterations;
    cout << "iterations (int): ";
    cin >> iterations;
    //declare position vector
    vector2_t r;
    //number of points in circle
    float successes = 0;
    //seed random number generator
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < iterations; i++) {
        
        randomise_vector(&r);
        //increase number of successes if in circle
        if (in_circle(&r)) {
            successes++;
        }
    }
    //approximate value according to pi = 4p
    float pi = 4 * successes / iterations;
    cout << "approximate pi = " << pi << endl;
    return 0;
}
