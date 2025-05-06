#include "forearm.h"
#include <GL/freeglut_std.h>

/**
 * @brief Constructs a ForeArm object and initializes its state.
 * 
 * Sets the position, size, and color of the forearm element.
 * Also links the internal state pointer to the extended state.
 * 
 * @param coordinates The (x, y) position.
 * @param width The width of the forearm.
 * @param height The height of the forearm.
 * @param color The RGB color of the forearm.
 */
ForeArm::ForeArm(Coordinates coordinates, int width, int height, Color color){
  state = &foreArmState;
  foreArmState.coordinates = coordinates;
  foreArmState.width = width;
  foreArmState.height = height;
  foreArmState.color = color;
}

/**
 * @brief Renders the forearm element as a filled or outlined rectangle.
 * 
 * Uses OpenGL to draw a quad based on the current state (position, size, color).
 * Fills or outlines the shape depending on whether it is active.
 */
void ForeArm::draw(){
  glColor3f(foreArmState.color[0], foreArmState.color[1], foreArmState.color[2]);

  int x = foreArmState.coordinates[0];
  int y = foreArmState.coordinates[1];
  int width = foreArmState.width;
  int height = foreArmState.height;

  if (foreArmState.isActive){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
  } else {
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
