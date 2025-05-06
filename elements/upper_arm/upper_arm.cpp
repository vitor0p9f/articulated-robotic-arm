#include "upper_arm.h"

/**
 * @brief Constructs an UpperArm instance and initializes its internal state.
 * 
 * @param coordinates The top-left (x, y) position of the upper arm.
 * @param width The width of the upper arm.
 * @param height The height of the upper arm.
 * @param color The RGB color of the upper arm.
 */
UpperArm::UpperArm(Coordinates coordinates, int width, int height, Color color){
  state = &upperArmState;
  upperArmState.coordinates = coordinates;
  upperArmState.width = width;
  upperArmState.height = height;
  upperArmState.color = color;
}

/**
 * @brief Renders the upper arm as a quadrilateral using OpenGL.
 * 
 * The rendering mode depends on whether the component is active.
 * When active, it is filled; otherwise, it is rendered in wireframe mode.
 */
void UpperArm::draw(){
  glColor3f(upperArmState.color[0], upperArmState.color[1], upperArmState.color[2]);

  int x = upperArmState.coordinates[0];
  int y = upperArmState.coordinates[1];
  int width = upperArmState.width;
  int height = upperArmState.height;

  if (upperArmState.isActive){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
  }else{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  }

  glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2f(width + x, y);
    glVertex2f(width + x, height + y);
    glVertex2f(x, height + y);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
