// hw2.pde
// William Horn
// Created: Sep 12, 2017
// Hierarchical Objects


float randomDirection() {
    return (round(random(1)) == 0) ? 1 : -1;
}


class Branch {
    float radius;
    float length;
    float angle, windSpeed, maxDeviationAngle, angleDeviation;
    float depth;

    ArrayList<Branch> branches; // All the child branches

    // ***************** Constructor ******************

    Branch(float r, float l, float a, float d) {
        radius = r;
        length = l;
        angle = a;
        depth = d;

        windSpeed = calcWindSpeed();
        maxDeviationAngle = calcMaxAngle();
        angleDeviation = random(-maxDeviationAngle, maxDeviationAngle);

        branches = new ArrayList<Branch>();

        // Make all the child branches
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

    // **************** Animation Function ******************

    void update() {
        float prevAngleDev = angleDeviation;

        // Apply the animation force
        applyWindSpeed();

        // Check to see if the wind force should change direction
        boolean changedDir = false;
        if(angleDeviation > maxDeviationAngle || angleDeviation < -maxDeviationAngle) { 
            windSpeed *= -1;
            changedDir = true;
        }

        // Apply the force again if it has
        if (changedDir) {
            applyWindSpeed();
        }

        // If the branch is in the middle, then give it a new maxDeviationAngle and windSpeed
        if (hasPastCenter(prevAngleDev)) {
            calcMaxAngle(); 
            windSpeed = calcWindSpeed();
        }

        // Update all the child branches if not a leaf
        if (depth <= maxDepth) {
            for (Branch b : branches) {
                b.update();
            }
        }
    }

    // ****************** Drawing Funciton **********************

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

        // Move to the tip of the branch
        translate(0, length);

        // Draw its branches
        if(depth <= maxDepth) {
            for (Branch b : branches) {
                b.show();
            }
        }

        popMatrix();
    }

    // ************ Calculation Functions **************

    float calcMaxAngle() {
        float maxAng = (PI / 22) * pow((depth - 1), 1.15) * 0.15;
        return random(0.75 * maxAng, 1.5 * maxAng) * windSpeedScale; 
    }


    float calcWindSpeed() {
        return (0.0005 * pow((depth - 1), 1.15) + (random(-5, 5)/100000)) * randomDirection();
    }


    float getTotalAngle() {
        return angle + angleDeviation;
    }


    boolean hasPastCenter(float prevAngle) {
        return (prevAngle > 0 && angleDeviation < 0) ||
            (prevAngle < 0 && angleDeviation > 0);
    }


    void applyWindSpeed() {
        angleDeviation += (windSpeed + random(-(0.1 * windSpeed), 0.1 * windSpeed)) * windSpeedScale;
    }
}


class Tree {
    float startX, startY;

    Branch root;

    Tree(float x, float y) {
        startX = x;
        startY = y;
        root = new Branch(10, 300, PI, 2);
    }

    void show() {
        pushMatrix();
        translate(startX, startY);

        root.show();

        popMatrix();
    }

    void update() {
        root.update();
    }
}


class WindLine {
   float x, y;
   float len;
   float vel;
   
   WindLine() {
       setPos();
       len = 6.0;
       vel = 8.0;
   }
   
   void show() {
      pushMatrix();
      
      translate(x, y);
      
      strokeWeight(1);
      stroke(255, 255, 255, getAlpha());
      
      line(0, 0, getLen(), 0);
      
      popMatrix();
   }
   
   void update() {
      x += getVel(); 
      
      if (x > width + 2 * getLen()) {
        setPos();
      }
   }
     
   void setPos() {
       x = -(2 * getLen() + random(width));
       y = random(height);
   }
  
   float getLen() {
       return (windSpeedScale > 0.5) ? len * windSpeedScale : 0;
   }
   
   float getAlpha() {
     return 200 * (windSpeedScale / maxWindSpeedScale);
   }
   
   float getVel() {
      return windSpeedScale * vel;
   }
}

// ************* Globals *************
float padding;
int maxDepth;
float branchLengthDecay;
float branchWidthDecay;

float windSpeedScale;
float maxWindSpeedScale;

int numWindLines;
ArrayList<WindLine> lines;

Tree tree;
// ***********************************


void setup() {
    size(1700, 850);
    background(0);

    maxDepth = 5;
    branchLengthDecay = 0.57;
    branchWidthDecay = 0.60;

    padding = 10;

    windSpeedScale = 1.0;
    maxWindSpeedScale = 8;    
    
    lines = new ArrayList<WindLine>();
    
    numWindLines = 14;
    for(int i = 0; i < numWindLines; ++i) {
      lines.add(new WindLine());   
    }
    
    tree = new Tree(width / 2, height - padding);
}


// Change the amount of wind with '+' and '-' keys
void keyPressed() {
    if (key == '+') {
        windSpeedScale += 0.1;
        windSpeedScale = min(windSpeedScale, maxWindSpeedScale);
    }
    if (key == '-') {
        windSpeedScale -= 0.1;
        windSpeedScale = max(0.1, windSpeedScale);
    }
}

void update() {
  tree.update();
  
  for(WindLine wl : lines) {
     wl.update(); 
  }
}

void draw() {
    // Animation 
    update();
    
    // Draw
    background(0);
    strokeWeight(1);
    stroke(255);
    noFill();
   
    for(WindLine wl : lines) {
     wl.show(); 
    }
    tree.show();
}
