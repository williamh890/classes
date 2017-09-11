// Graphics.pde
// William Horn
// AUG 30, 2017

// First time with processing
int width;
int height;
int startingLimit;
int drag;
int padding; 

// showOutline -> default beginShape 
// 
// 
// class      | EXAMPLE
// -----------------------------
// Ameoba     | TRIANGLE_FAN 
// BlockGroup | QUADS
// Boing      | QUAD_STRIPS
// Triangles  | TRIANGLES
// Spiral     | POINTS
// SpazeLine  | LINES
// WaveyStrip | TRIANGLE_STRIP 
//
//
// NOTE: Some of the updating of the internal state of the shapes are
//       are modified in the show function. In a perfect world, this 
//       would be moved out into the update function, possibly in an
//       update function




class Vec2 {
    float x, y;
    
    Vec2(float initX, float initY) {
        x = initX;
        y = initY;
    }

    void mult(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    void addVec(Vec2 toAdd) {
        x += toAdd.x;
        y += toAdd.y;
   } 
}


class Entity {
    Vec2 pos, vel;
    float size; 

    Entity() {
        pos = new Vec2(random(padding, width),
                       random(padding, height));
        vel = new Vec2(random(-startingLimit, startingLimit), 
                       random(-startingLimit, startingLimit));
        size = 5; 
    }


    int getBound() {
        return 5 * size;
    }


    void applyForce(Vec2 force) {
        // Apply a force to the object
        vel.addVec(force);
    }

    void update() {
        // Slow down the object by the drag in the world
        vel.x *= drag;
        vel.y *= drag;

        pos.addVec(vel);

        // If the entity goes out of bounds just wrap it across the screen
        if(outOfBounds()) {
            wrapEntity();
        }

    }
    
    bool outOfBounds() {
        return pos.x  > width +  (getBound()) || 
               pos.x  <         -(getBound()) ||
               pos.y  > height + (getBound()) || 
               pos.y  <         -(getBound());
    }

    void wrapEntity() {
        if(pos.x < -getBound()) pos.x = width + getBound();
        if(pos.x > width + getBound()) pos.x = -getBound();

        if(pos.y < -getBound()) pos.y = height + getBound();
        if(pos.y > height + getBound()) pos.y = -getBound();
    }

    // overriden in the derived class 
    void show() {
        ellipse(pos.x, pos.y, 20, 30); 
    }
}


class Ameoba extends Entity {
    float startingNoise;

    Ameoba() {
        super();
        size = random(20, 50);
        startingNoise = random(10000000);
    }


    void show() {   
        strokeWeight(1);
        stroke(255);
        noFill();

        beginShape(TRIANGLE_FAN);
        
        step = 0.5;
        noiseIndex = startingNoise;
        vertex(pos.x, pos.y);

        Vec2 first;
        for(int d = 0; d < 2*PI; d += 2*PI/20) {
            float x =  cos(d) * size + pos.x;
            float y =  sin(d) * size + pos.y;
            
            Vec2 p = new Vec2(x, y);
            Vec2 n = new Vec2(x, y);

            n.mult((noise(noiseIndex) - 0.5) * 0.1);
            noiseIndex += step;

            p.addVec(n);
            
            if(d == 0) 
                first = new Vec2(p.x, p.y);
            
            vertex(p.x, p.y);
        }
        vertex(first.x, first.y);
        endShape();
        startingNoise += 0.001;
    }
}


class BlockGroup extends Entity {
    float rotationAngle, startingAngle, rotationSpeed;
    float blockLength, blockWidth;
    int numBlocks;
    int numVertices;

    BlockGroup() {
        super();
        startingAngle = 0;
        blockLength = random(50, 100);
        blockWidth = random(50, 100);
        numBlocks = 5;
        rotationAngle = random(0, TAU);
        rotationSpeed = random(0.01, 0.1);
    }


    void show() {
        pushMatrix();
        translate(pos.x, pos.y);
        rotate(rotationAngle);
        rotationAngle += rotationSpeed;

        beginShape(QUADS);
        noFill();
        strokeWeight(1);
        stroke(255);

        boolean evenSide = true;
        for(float w = 0; w < blockWidth; w += blockWidth/numBlocks) {
            if (evenSide){
                vertex(w, blockLength);
                vertex(w, 0);
            } 
            else {
                vertex(w, 0);
                vertex(w, blockLength);
            }
            evenSide = !evenSide;
        }

        endShape();
        popMatrix();
    }
}


class Boing extends Entity {
    float startingAngle;
    float lengthMin, lengthMax;
    float currLength;
    float growth;
    float numBlocks;

    Boing() {
        super();
        size = random(10, 20);
        startingAngle = 0;
        lengthMin = random(40, 60);
        currLength = lengthMin;

        lengthMax = random(currLength, currLength + 100);
        growth = random(0.5, 1)
        numBlocks = 8;
        blockWidth = random(10, 40);
    }


    void show() {    
        noFill();
        strokeWeight(1);
        stroke(255);

        evenSide = true;
        pushMatrix();
        beginShape(QUAD_STRIP);

        translate(pos.x, pos.y);
        for(float w = 0; w < blockWidth; w += blockWidth/numBlocks) {
            vertex(w, currLength);
            vertex(w, 0);
        }
        endShape();
        popMatrix();

        currLength += growth;
        
        if (currLength <= lengthMin) {
            growth *= -1;
        }
        
        if (currLength >= lengthMax) {
            growth *= -1;
        }
    }
}

class Triangle extends Entity {
    float trianglesWidth, numVertices; 

    Triangle() {
        super();
        trianglesWidth = random(50, 100)
        size = random(50, 70);
        numVertices = 8;
    }

    void show() {    
        strokeWeight(8);
        stroke(255);
      
        pushMatrix();
        translate(pos.x, pos.y);
        beginShape(TRIANGLES);
        
        boolean evenVertex = true;
        for(int w = 0; w < trianglesWidth; w += trianglesWidth / numVertices) {
            if (evenVertex) {
                vertex(w, 0);
            }
            else {
                vertex(w, size);
            }
            evenVertex = !evenVertex;
        }

        endShape();
        popMatrix();
    }
}


class Spiral extends Entity {
    float startingAngle;
    Spiral() {
        super();
        size = random(10, 20);
        startingAngle = 0;
    }


    void show() {    
        strokeWeight(8);
        stroke(255);
        beginShape(POINTS);
        
        for(float d = startingAngle; d < 2*PI + startingAngle; d = (d + 2*PI/8)) {
            float xloc = size * (d - startingAngle) * cos(d) + pos.x; 
            float yloc = size * (d - startingAngle) * sin(d) + pos.y;
            vertex(xloc, yloc);
        }
        endShape();
        startingAngle += 0.1;
        if (startingAngle > TAU) {
            startingAngle = 0;
        }
    }
}


class SpazeLine extends Entity {
    float length;

    SpazeLine() {
        super();
        length = random(40, 50);
    }


    void show() {    
        strokeWeight(3);
        stroke(255);

        pushMatrix();
        translate(pos.x, pos.y);
        rotate(random(TAU));
        
        beginShape(LINES);
        
        vertex(0, 0);
        vertex(length, 0);

        endShape();
        popMatrix();
    }
}




class WaveyStrip extends Entity {
    float length;
    float startingAngle;
    int amplitude;

    WaveyStrip() {
        super();
        size = random(40, 60);
        length = random(40, 150);
        startingAngle = random(TAU);
        amplitude = 5;
    }


    void show() {    
        strokeWeight(1);
        stroke(255);
        beginShape(TRIANGLE_STRIP);
        
        numVertices = 10;
        angle = 0;
        deltaAngle = 2*TAU / numVertices;

        boolean isTopVertex = true;

        int v, a;
        for(v = 0, a = startingAngle; v < length; v += length/numVertices, a += 2*TAU/numVertices) {
            int x = pos.x + v;
            int y = pos.y + amplitude * cos(a); 

            if (!isTopVertex) {
                y -= size;
            }
            isTopVertex = !isTopVertex;

            vertex(x, y);
        }

        startingAngle += PI / numVertices * 0.5;
         
        endShape();
    }
}


Entity randomEntity() {
    int select = round(random(0,6));

    if (select == 0) { 
        return new Spiral();
    }
    else if (select == 1) {
        return new Ameoba();
    }
    else if (select == 2) {
        return new WaveyStrip();
    }
    else if (select == 3) {
        return new BlockGroup();
    }
    else if (select == 4) {
        return new Boing();
    }
    else if (select == 5) {
        return new Triangle();
    }
    else if (select == 6) {
        return new SpazeLine();
    }
}


// To demonstrate the standard beginShape()
void showOutline() {
    noFill();
    strokeWeight(1);
    beginShape();
    vertex(padding, padding);
    vertex(padding, height - padding);
    vertex(width - padding, height - padding);
    vertex(width - padding, padding);
    endShape(CLOSE);
}


void setup()
{
    width = 1700;
    height = 850;
    startingLimit = 7;
    drag = 0.9999;
    padding = 10; 

    size(width, height);
    int startingEntities = 3;
    entities = new ArrayList<Entity>();
    for(int i = 0; i < startingEntities; ++i) {
        entities.add(randomEntity());
    } 

}


void keyPressed() {
    if (key == '+') {
        entities.add(randomEntity());
    }
    else if (key == '-') {
        entities.remove(0);
    }
}

void update() {
    for( Entity entity : entities) {
        entity.update();
    }
}


void draw(){  
    update();

    background(0);
    showOutline();
    for( Entity entity : entities) {
        entity.show();
    }
}
