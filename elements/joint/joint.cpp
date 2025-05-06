#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include "joint.h"

#define PI 3.14159265

/**
 * @brief Constructs a Joint object with the given parameters.
 * 
 * Initializes the joint's internal state with coordinates, radius, and color.
 * The pointer `state` is set to refer to the extended state specific to the Joint.
 * 
 * @param coordinates The (x, y) position of the joint.
 * @param radius The radius of the circular joint.
 * @param color The RGB color of the joint.
 */
Joint::Joint(Coordinates coordinates, int radius, Color color){
  state = &jointState;
  jointState.coordinates = coordinates;
  jointState.radius = radius;
  jointState.color = color;
}

/**
 * @brief Renders the joint as a circle using OpenGL.
 * 
 * Uses the radius and number of segments from the joint's internal state
 * to approximate and draw a circle. If the joint is active, it is drawn filled;
 * otherwise, it is drawn in wireframe mode.
 */
void Joint::draw(){
  glColor3f(jointState.color[0], jointState.color[1], jointState.color[2]);

  if (jointState.isActive){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
  }else{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  }

  int segments = jointState.segments;
  int radius = jointState.radius;

  glBegin(GL_POLYGON);
    for (int current_segment = 0; current_segment < segments; current_segment++) {
      float theta = 2.0f * PI * (float)current_segment / (float)segments;
      float x = radius * cosf(theta);
      float y = radius * sinf(theta);
      glVertex2f(x + jointState.coordinates[0], y + jointState.coordinates[1]);
    }
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
}
