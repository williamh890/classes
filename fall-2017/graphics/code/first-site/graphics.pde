// Graphics.pde
// William Horn
// AUG 30, 2017

// First time with processing
int height = 500;
int width = 400;

void setup() {
    size(500, 400);
    background(255);
    println("hellO!")
}

void draw() {
    int r = int(random(256));
    int g = int(random(256));
    int b = int(random(256));
    stroke(r, g, b);
    strokeWeight(6);
    line(10, 10, 490, 390);
}
