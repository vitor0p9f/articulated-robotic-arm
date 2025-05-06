#include "gripper.h"
#include <GL/gl.h>

/**
 * @brief Draws the left part of the gripper as a set of triangles.
 * 
 * The left part of the gripper is composed of a horizontal and a vertical section
 * formed by triangles. If the gripper is inactive, internal lines are drawn to cover
 * the internal structure.
 * 
 * @param x The x-coordinate of the left part's base.
 * @param y The y-coordinate of the left part's base.
 * @param width The width of the left part of the gripper.
 * @param height The height of the left part of the gripper.
 * @param active Flag indicating whether the gripper is active or not (for drawing style).
 */
void drawLeftPart(int x, int y, int width, int height, bool active) {
  glBegin(GL_TRIANGLES);
    // Horizontal part  

    // First triangle
    glVertex2i(x - width, y);
    glVertex2i(x - width, y + height/2);
    glVertex2i(x, y);

    // Second triangle
    glVertex2i(x - width, y + height/2);
    glVertex2i(x, y + height/2);
    glVertex2i(x, y);

    // Vertical part

    // Third triangle
    glVertex2i(x - width, y);
    glVertex2i(x - width/2, y);
    glVertex2i(x - width/2, y + height);

    // Fourth triangle
    glVertex2i(x - width, y);
    glVertex2i(x - width, y + height);
    glVertex2i(x - width/2, y + height);
  glEnd();

  if (!active){
    glColor3f(0.0f, 0.0f, 0.0f);

    // Covers internal lines
    glBegin(GL_LINES);
      glVertex2i(x, y);
      glVertex2i(x - width, y + height/2);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x - width/2, y + height/2);
      glVertex2i(x - width, y + height/2);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x - width, y);
      glVertex2i(x - width/2, y + height);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x - width/2, y);
      glVertex2i(x - width/2, y + height/2);
    glEnd();
  }
}

/**
 * @brief Draws the right part of the gripper as a set of triangles.
 * 
 * The right part of the gripper is composed of a horizontal and a vertical section
 * formed by triangles. If the gripper is inactive, internal lines are drawn to cover
 * the internal structure.
 * 
 * @param x The x-coordinate of the right part's base.
 * @param y The y-coordinate of the right part's base.
 * @param width The width of the right part of the gripper.
 * @param height The height of the right part of the gripper.
 * @param active Flag indicating whether the gripper is active or not (for drawing style).
 */
void drawRightPart(int x, int y, int width, int height, bool active) {
  glBegin(GL_TRIANGLES);
    // Horizontal part  

    // First triangle
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height/2);
    glVertex2i(x, y);

    // Second triangle
    glVertex2i(x + width, y + height/2);
    glVertex2i(x, y + height/2);
    glVertex2i(x, y);

    // Vertical part

    // Third triangle
    glVertex2i(x + width, y);
    glVertex2i(x + width/2, y);
    glVertex2i(x + width/2, y + height);

    // Fourth triangle
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x + width/2, y + height);
  glEnd();

  if (!active){
    glColor3f(0.0f, 0.0f, 0.0f);

    // Covers internal lines
    glBegin(GL_LINES);
      glVertex2i(x, y);
      glVertex2i(x + width, y + height/2);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x + width/2, y + height/2);
      glVertex2i(x + width, y + height/2);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x + width, y);
      glVertex2i(x + width/2, y + height);
    glEnd();

    glBegin(GL_LINES);
      glVertex2i(x + width/2, y);
      glVertex2i(x + width/2, y + height/2);
    glEnd();
  }
}

/**
 * @brief Constructs a Gripper object with given coordinates, size, and color.
 * 
 * Initializes the gripper's left and right parts' coordinates, width, height, and color.
 * 
 * @param left_part_coordinates The (x, y) position of the left part of the gripper.
 * @param right_part_coordinates The (x, y) position of the right part of the gripper.
 * @param width The width of the gripper.
 * @param height The height of the gripper.
 * @param color The RGB color of the gripper.
 */
Gripper::Gripper(Coordinates left_part_coordinates, Coordinates right_part_coordinates, int width, int height, Color color) {
  state = &gripperState;
  gripperState.left_part_coordinates = left_part_coordinates;
  gripperState.right_part_coordinates = right_part_coordinates;
  gripperState.width = width;
  gripperState.height = height;
  gripperState.color = color;
}

/**
 * @brief Sets the angle of rotation for the gripper.
 * 
 * @param angle The desired angle to rotate the gripper (in degrees).
 */
void Gripper::setAngle(float angle) {
  gripperState.angle = angle;
}

/**
 * @brief Gets the current angle of rotation of the gripper.
 * 
 * @return The current rotation angle of the gripper.
 */
float Gripper::getAngle() {
  return gripperState.angle;
}

/**
 * @brief Draws the gripper component, including left and right parts.
 * 
 * Overrides the pure virtual draw method from Drawable.
 * The left and right parts of the gripper are drawn based on their positions,
 * size, color, and angle of rotation. The drawing behavior is affected by the
 * `isActive` status, which determines whether the gripper is drawn filled or outlined.
 */
void Gripper::draw() {
  glColor3f(gripperState.color[0], gripperState.color[1], gripperState.color[2]);

  if (gripperState.isActive) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  int width = gripperState.width;
  int height = gripperState.height;
  float angle = gripperState.angle;

  int x_left = gripperState.left_part_coordinates[0];
  int y_left = gripperState.left_part_coordinates[1];

  glPushMatrix();

  // Change the origin of the coordinate system to the desired point
  glTranslatef(x_left, y_left, 0.0f);

  // Rotate around the desired point
  glRotatef(angle, 0.0f, 0.0f, 1.0f);

  // Change the origin back to the original coordinate
  glTranslatef(-x_left, -y_left, 0.0f);

  drawLeftPart(x_left, y_left, width, height, gripperState.isActive);

  glPopMatrix();

  glColor3f(gripperState.color[0], gripperState.color[1], gripperState.color[2]);

  int x_right = gripperState.right_part_coordinates[0];
  int y_right = gripperState.right_part_coordinates[1];

  glPushMatrix();

  // Change the origin of the coordinate system to the desired point
  glTranslatef(x_right, y_right, 0.0f);

  // Rotate around the desired point
  glRotatef(-angle, 0.0f, 0.0f, 1.0f);

  // Change the origin back to the original coordinate
  glTranslatef(-x_right, -y_right, 0.0f);

  drawRightPart(x_right, y_right, width, height, gripperState.isActive);

  glPopMatrix();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
