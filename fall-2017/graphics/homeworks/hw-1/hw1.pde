// Graphics.pde
// William Horn
// AUG 30, 2017

// First time with processing
int width;
int height;
int center_w;
int center_h;
int startingLimit;
int drag;
int padding; 


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

    void show() {
        // overriden in the derived class 
        ellipse(pos.x, pos.y, 20, 30); 
    }
}

class Ameoba extends Entity {
    float size;

    Ameoba() {
        super();
        size = random(20, 50);
        starting_noise = random(1000);
    }


    void show() {   
        strokeWeight(1);
        stroke(255);
        noFill();

        beginShape(TRIANGLE_FAN);
        
        step = 0.5;
        noise_index = starting_noise;
        vertex(pos.x, pos.y);

        Vec2 first;
        for(int d = 0; d < 2*PI; d += 2*PI/20) {
            float x =  cos(d) * size + pos.x;
            float y =  sin(d) * size + pos.y;
            
            Vec2 p = new Vec2(x, y);
            Vec2 n = new Vec2(x, y);

            n.mult((noise(noise_index) - 0.5) * 0.1);
            noise_index += step;

            p.addVec(n);
            
            if(d == 0) 
                first = new Vec2(p.x, p.y);
            
            vertex(p.x, p.y);
        }
        vertex(first.x, first.y);
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
        strokeWeight(8);
        stroke(255);
        beginShape(POINTS);
        
        for(float d = 0; d < 2*PI; d = (d + 2*PI/8)) {
            float xloc = size * d * cos(d) + pos.x; 
            float yloc = size * d * sin(d) + pos.y;
            vertex(xloc, yloc);
        }
        endShape();
    }
}


class WaveyStrip extends Entity {
    float size;

    WaveyStrip() {
        super();
        size = random(4, 12);
    }


    void show() {    
        strokeWeight(1);
        stroke(255);
        beginShape(TRIANGLE_STRIP);
        vertex(30, 75);
        vertex(40, 20);
        vertex(50, 75);
        vertex(60, 20);
        vertex(70, 75);
        vertex(80, 20);
        vertex(90, 75);
        endShape();
    }
}


Entity randomEntity() {
    int select = round(random(0,2));

    if (select == 0) { 
        return new Spiral();
    }
    else if (select == 1) {
        return new Ameoba();
    }
    else if (select == 2) {
        return new WaveyStrip();
    }
}


void setup()
{
    width = 1000;
    height = 1000;
    center_w = width / 2;
    center_h = height / 2;
    startingLimit = 20;
    drag = 0.99;
    padding = 10; 

    int numEntities = 10;
    entites = new ArrayList<Entity>();
    for(int i = 0; i < numEntities; ++i) {
        entites.add(randomEntity());
    } 

    size(width, height);
}



void update() {
    for( Entity entity : entites) {
        entity.update();
    }
}


void draw(){  
    update();

    background(0);

    for( Entity entity : entites) {
        entity.show();
    }
}
