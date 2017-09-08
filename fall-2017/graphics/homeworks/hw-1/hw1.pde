// Graphics.pde
// William Horn
// AUG 30, 2017

// First time with processing
int width = 500;
int height = 500;
int center_w = width / 2;
int center_h = height / 2;
int startingLimit = 20;
int drag = 0.99;
int padding = 10; 


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
    PVector pos, vel;

    Entity() {
        pos = new Vec2(random(padding, width),
                          random(padding, height));
        this.vel = new Vec2(random(-startingLimit, startingLimit), 
                          random(-startingLimit, startingLimit));
    }

    void applyForce(PVector force) {
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
        return pos.x > width || pos.x < 0 || pos.y > height || pos.y < 0;
    }

    void wrapEntity() {
        if(pos.x < 0) pos.x = width;
        if(pos.x > width) pos.x = 0;

        if(pos.y < 0) pos.y = height;
        if(pos.y > height) pos.y = 0;
    }

    void show() {
        // overriden in the derived class 
        ellipse(pos.x, pos.y, 20, 30); 
    }
}

class Ameoba extends Entity {
    float size;

    Ameoba() {
        super();
        size = random(10, 15);
    }


    void show() {    
        strokeWeight(2);
        beginShape(TRIANGLE_STRIP);
        vertex(pos.x + 30 +  size, pos.y + 75 + size);
        vertex(pos.x + 40 + size, pos.y + 20 + size);
        vertex(pos.x + 50 + size, pos.y + 75 + size);
        vertex(pos.x + 60 + size, pos.y + 20 + size);
        vertex(pos.x + 70 + size, pos.y + 75 + size);
        endShape();
    }
}


class Spiral extends Entity {
    float size;

    Spiral() {
        super();
        size = random(4, 12);
    }


    void show() {    
        strokeWeight(10);
        beginShape(POINTS);
        for(float d = 0; d < 2*PI; d = (d + 2*PI/8)) {
            float xloc = size * d * cos(d) + pos.x; 
            float yloc = size * d * sin(d) + pos.y;
            vertex(xloc, yloc);
        }
        endShape();
    }
}

Spiral s = new Spiral();
Ameoba a = new Ameoba();

ArrayList<Entity> entites = new ArrayList<Entity>();

entites.add(a);
entites.add(s);


void setup()
{
    size(width, height);
    background(125);
    fill(255);
}


void update() {
    for( Entity entity : entites) {
        entity.update();
    }
}


void draw(){  
    update();

    background(204);

    for( Entity entity : entites) {
        entity.show();
    }
}
