int canvas_width = 500;
int canvas_height = 400;
int canvas_center_x=250;
int canvas_center_y=200;

//facial expression value
boolean smiling;


// setup
// Processing setup function
void setup()
{
    size(canvas_width, canvas_height);
    strokeWeight(6.);
    smiling = true;
    frameRate(2);
}


// draw
// Processing drawing function
void draw()
{
    int r, g, b;  // For color components

    r = int(random(256));
    g = int(random(256));
    b = int(random(256));
    stroke(r, g, b);

    r = int(random(256));
    g = int(random(256));
    b = int(random(256));
    fill(r, g, b);

    background(255);
    if (!smiling){
      stroke(255, 0, 0);
      fill(0, 0, 0);
      drawQuads(75, 75, canvas_center_x-(canvas_center_x/2), canvas_center_y-(canvas_center_y/2));
      drawQuads(75, 75, canvas_center_x+(canvas_center_x/2), canvas_center_y-(canvas_center_y/2));
      drawLine(canvas_center_x-(canvas_center_x/1.5), canvas_center_x+(canvas_center_x/1.5), canvas_center_y, canvas_center_y);
    }
    if (smiling){
      stroke(0,255,255);
      fill(255);
      drawQuads(50, 50, canvas_center_x-(canvas_center_x/2), canvas_center_y-(canvas_center_y/2));
      drawQuads(50, 50, canvas_center_x+(canvas_center_x/2), canvas_center_y-(canvas_center_y/2));
      drawLine(canvas_center_x-(canvas_center_x/2), canvas_center_x+(canvas_center_x/2), canvas_center_y, canvas_center_y);
    }
    // Try changing the primitive in the above line
}

void drawQuads(int width, int height, int origin_x, int origin_y){
  beginShape(QUADS);
  vertex(abs(width-origin_x), abs(height-origin_y));
  vertex(abs(width-origin_x), abs(height+origin_y));
  vertex(abs(width+origin_x), abs(height+origin_y));
  vertex(abs(width+origin_x), abs(height-origin_y));
  endShape();
}

void drawLine(x1, x2, y1, y2){
  beginShape(LINES);
  vertex(x1,y1);
  vertex(x2,y2);
  endShape();
}
// keyPressed
// Processing keypress handler
void keyPressed()
{
    switch (key)
    {
    case ' ':
        smiling = !smiling;
        break;
    }
}
