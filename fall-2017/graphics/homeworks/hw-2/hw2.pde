// hw2.pde
// William Horn
// Created: Sep 12, 2017
// Hierarchical Objects

float padding;
int maxDepth = 5;
float branchLengthDecay = 0.57;
float branchWidthDecay = 0.60;

float randomDirection() {
    float dir = round(random(1));

    if (dir == 0) {
        return 1;
    }
    else {
        return -1;
    }
}


class Branch {
    float radius;
    float length;
    float angle, windForce, maxAngle, angleDeviation;
    float depth;

    ArrayList<Branch> branches;

    Branch(float r, float l, float a, float d) {
        radius = r;
        length = l;
        angle = a;
        depth = d;
        windForce = calcWindForce();
        maxAngle = calcMaxAngle();
        angleDeviation = random(-maxAngle, maxAngle);

        branches = new ArrayList<Branch>();

        if (depth <= maxDepth) {
            for(int i = 0; i < depth; ++i) {
                Branch newBranch = new Branch(
                        branchWidthDecay * r,
                        branchLengthDecay * l,
                        ((PI * i) / depth) - (PI / 4), 
                        d + 1);

                branches.add(newBranch);
            }

        }
    }

    float calcMaxAngle() {
        float maxAng = (PI / 22) * pow((depth - 1), 1.15) * 0.15;
        return random(0.75 * maxAng, 1.5 * maxAng);
    }


    float calcWindForce() {
        return 0.0005 * pow((depth - 1), 1.15) + random(-0.00005, 0.00005) * randomDirection();
    }

    float getTotalAngle() {
        return angle + angleDeviation;
    }

    boolean hasPastCenter(float prevAngle) {
        return (prevAngle > 0 && angleDeviation < 0) ||
            (prevAngle < 0 && angleDeviation > 0);
    }

    void applyWindForce() {
        angleDeviation += windForce + random(-(0.1 * windForce), 0.1 * windForce);
    }

    void update() {
        // check if the branch is in the middle
        float prevAngleDev = angleDeviation;

        applyWindForce();

        boolean changedDir = false;
        if(angleDeviation > maxAngle) { 
            windForce *= -1;
            changedDir = true;
        }
        else if (angleDeviation < -maxAngle) {
            windForce *= -1;
            changedDir = true;  
        }

        if (changedDir) {
            applyWindForce();

        }

        if (hasPastCenter(prevAngleDev)) {
            calcMaxAngle(); 
            windForce = calcWindForce();
        }


        if (depth <= maxDepth) {
            for (Branch b : branches) {
                b.update();
            }
        }
    }


    void show() {
        pushMatrix();
        rotate(getTotalAngle());
        fill(255);

        beginShape(QUADS);
        vertex(+radius, -radius);
        vertex(+radius, length+radius);
        vertex(-radius, length+radius);
        vertex(-radius, -radius);
        endShape(CLOSE);

        //beginShape(POINTS);
        //vertex(0 , 0);
        //vertex(0, length);
        //endShape();

        translate(0, length);
        if(depth <= maxDepth) {
            for (Branch b : branches) {
                b.show();
            }
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
        root = new Branch(10, 300, PI, 2);
    }

    void show() {
        pushMatrix();
        translate(startX, startY - bottomPadding);
        root.show();
        popMatrix();
    }

    void update() {
        root.update();
    }
}

Tree tree;

void setup() {
    size(1700, 850);
    background(0);

    padding = 10;

    tree = new Tree(width / 2, height, padding);
}


void draw() {
    background(0);
    strokeWeight(1);
    stroke(255);
    noFill();

    tree.update();

    tree.show();

}
