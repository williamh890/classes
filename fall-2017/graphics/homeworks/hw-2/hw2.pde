// hw2.pde
// William Horn
// Created: Sep 12, 2017
// Hierarchical Objects

float padding;
int maxDepth = 4;

class Branch {
    float radius;
    float length;
    float angle;
    float depth;

    Branch left, right;

    Branch(float r, float l, float a, float d) {
        radius = r;
        length = l;
        angle = a;
        depth = d;
        
        if (depth <= maxDepth) {
             left = new Branch(0.8 * r, 0.9 * l, PI / 4, d + 1);
             right = new Branch(0.8 * r, 0.9 * l, -PI / 4, d + 1);
        }
    }

    void show() {
        pushMatrix();
        rotate(angle);
        beginShape(QUADS);
        vertex(+radius, -radius);
        vertex(+radius, length+radius);
        vertex(-radius, length+radius);
        vertex(-radius, -radius);
        endShape(CLOSE);

        beginShape(POINTS);
        vertex(0 , 0);
        vertex(0, length);
        endShape();
        
        translate(0, length);
        if(depth <= maxDepth) {
            left.show();
            right.show();
        }
        
        popMatrix();
    }

}


class Tree {
    float startX, startY;
    float bottomPadding;

    Branch root;

    Tree(float x, float y, float p) {
        startX = x;
        startY = y;
        bottomPadding = p;
        root = new Branch(10, 100, PI, 1);
    }

    void show() {
        pushMatrix();
        translate(startX, startY - bottomPadding);
        root.show();
        popMatrix();
    }
}

Tree tree;

void setup() {
    size(1700, 850);
    background(100);

    padding = 15;

    tree = new Tree(width / 2, height, padding);
}


void draw() {
    strokeWeight(1);
    stroke(255);
    noFill();
    
    tree.show();
    
}