// Graphics.pde
// William Horn
// AUG 30, 2017

// First time with processing
int width = 500;
int height = 500;
int r = 100;

void setup()
{
    size(width, height);
    background(125);
    fill(255);
}

void draw(){  
    ellipse(width / 2, height / 2, r, r);
}
