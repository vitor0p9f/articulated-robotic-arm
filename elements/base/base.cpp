#include "base.h"
#include <GL/gl.h>

/**
 * @brief Constructs a Base object and initializes its state.
 * 
 * Sets the position, size, and color of the base element.
 * Also links the internal state pointer to the extended state.
 * 
 * @param coordinates The (x, y) position.
 * @param width The width of the base.
 * @param height The height of the base.
 * @param color The RGB color of the base.
 */
Base::Base(Coordinates coordinates, int width, int height, Color color){
  state = &baseState;
  baseState.coordinates = coordinates;
  baseState.width = width;
  baseState.height = height;
  baseState.color = color;
}

/**
 * @brief Renders the base element as a filled or outlined rectangle.
 * 
 * Uses OpenGL to draw a quad based on the current state (position, size, color).
 * Fills or outlines the shape depending on whether it is active.
 */
void Base::draw(){
  glColor3f(baseState.color[0], baseState.color[1], baseState.color[2]);

  int x = baseState.coordinates[0];
  int y = baseState.coordinates[1];
  int width = baseState.width;
  int height = baseState.height;

  if (baseState.isActive){
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
