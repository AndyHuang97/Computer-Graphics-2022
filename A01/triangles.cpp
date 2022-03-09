/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

auto rectangle = [=] (float left_x, float right_x,  float top_y, float bottom_y, float r, float g, float b) {
	float x = left_x;
	float y = top_y;
	float firstSideLength = right_x - left_x;
	float secondSideLength = bottom_y - top_y;
	Triangle(x,y, x+firstSideLength,y, x,y+secondSideLength, r, g, b);
	Triangle(x,y+secondSideLength, x+firstSideLength,y+secondSideLength, x+firstSideLength,y, r, g, b);
};

// roof
const float left_roof_x = -0.038;
const float right_roof_x = 0.73;
const float center_roof_x = 0.36;
const float bottom_roof_y = 0.17;
const float top_roof_y = -0.45;

Triangle(left_roof_x, bottom_roof_y, center_roof_x,top_roof_y, right_roof_x,bottom_roof_y,   1,0,0);

// body
const float left_body_x = 0.06;
const float right_body_x = 0.64;
const float top_body_y = bottom_roof_y;
const float bottom_body_y = 0.81;
rectangle(left_body_x, right_body_x, top_body_y, bottom_body_y, 0,0,1);

// door
const float left_door_x = 0.28;
const float right_door_x = 0.41;
const float top_door_y = 0.5;
const float bottom_door_y = 0.81;
rectangle(left_door_x, right_door_x, top_door_y, bottom_door_y, 1,1,0);

// windows
const float left_window1_x = 0.17;
const float top_window1_y = 0.28;
const float right_window1_x = 0.28;
const float bottom_window1_y = 0.43;
rectangle(left_window1_x, right_window1_x, top_window1_y, bottom_window1_y, 1,1,0);

const float left_window2_x = 0.44;
const float right_window2_x = 0.57;
const float top_window2_y = 0.25;
const float bottom_window2_y = 0.41;
rectangle(left_window2_x, right_window2_x, top_window2_y, bottom_window2_y, 1,1,0);


// terrain
const float left_terrain_x = -0.97;
const float top_terrain_y = 0.8;
const float right_terrain_x = 0.98;
const float bottom_terrain_y = 1;
rectangle(left_terrain_x, right_terrain_x, top_terrain_y, bottom_terrain_y, 0, 102.0/255, 0);


// auto circle = [=] ()
for(int i = 0; i < 32; i++) {
	Triangle( 0.68 + 0.05 * cos(6.28/32*(i-0.5)), -0.65 + 0.05 * sin(6.28/32*(i-0.5)),
			  0.68 + 0.10 * cos(6.28/32*i), -0.65 + 0.10 * sin(6.28/32*i),
			  0.68 + 0.05 * cos(6.28/32*(i+0.5)), -0.65 + 0.05 * sin(6.28/32*(i+0.5)),
			  1,102.0/255,0);
}
