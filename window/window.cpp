/**
 * @file window.cpp
 * @brief Implementation of the Window class that manages the robotic arm interface using OpenGL and FreeGLUT.
 *
 * This file sets up the OpenGL context, handles user input, and performs transformations
 * and rendering of an articulated robotic arm composed of base, forearm, upper arm, joints, and gripper.
 */

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>

#include "window.h"

// Static constant definitions
const float Window::MAX_ANGLE = 60.0f;
const float Window::MIN_ANGLE = -60.0f;
const int Window::BASE_LIMIT = 400;
const int Window::MOVE_STEP = 1;
const float Window::ROTATE_STEP = 1.0f;

// Static variables for transformations and components
int Window::baseTX = 0;
float Window::base_forearm_joint_RA = 0.0f;
float Window::forearm_upper_arm_joint_RA = 0.0f;
float Window::upper_arm_gripper_joint_RA = 0.0f;

// Static component instances
Gripper Window::gripper = Gripper(Coordinates{42,110}, Coordinates{58,110}, 8, 10, Color{0.0f,1.0f,0.0f});
Joint Window::upper_arm_gripper_joint = Joint(Coordinates{50,110}, 4, Color{0.0f,1.0f,0.0f});
UpperArm Window::upper_arm = UpperArm(Coordinates{48,82}, 5, 20, Color{0.0f,1.0f,0.0f});
Joint Window::forearm_upper_arm_joint = Joint(Coordinates{50,74}, 4, Color{0.0f,1.0f,0.0f});
ForeArm Window::forearm = ForeArm(Coordinates{48,36}, 5, 30, Color{0.0f,1.0f,0.0f});
Joint Window::base_forearm_joint = Joint(Coordinates{50,28}, 4, Color{0.0f,1.0f,0.0f});
Base Window::base = Base(Coordinates{35,10}, 30, 10, Color{0.0f,1.0f,0.0f});

ActivePart Window::active = BASE;
int Window::width = 400;

/**
 * @brief Constructs and initializes the OpenGL window.
 * 
 * Initializes the FreeGLUT context, projection settings, keyboard input,
 * and display callback for rendering the robotic arm.
 */
Window::Window(int argc, char** argv){
  height = 400;
  x_position = 100;
  y_position = 100;

  base.activate();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(x_position, y_position);
  glutCreateWindow("Articulated Robotic Arm");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  gluOrtho2D(0, width/3.0, 0, height/3.0);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);
  glutDisplayFunc(display);
}

/**
 * @brief Renders the entire robotic arm and background elements.
 * 
 * Applies translation and rotation matrices hierarchically to render
 * each articulated component in the correct spatial relationship.
 */
void Window::display(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glPushMatrix();

  // Draw the ground line
  glColor3f(1.0f,1.0f,1.0f);
  glLineWidth(4);
  glBegin(GL_LINES);
    glVertex2f(0, 10);
    glVertex2f(width/3.0, 10);
  glEnd();
  glLineWidth(1);

  // Draw and transform each part
  glTranslatef(baseTX, 0.0f, 0.0f);
  base.draw();

  glPushMatrix();
  glTranslatef(base_forearm_joint.getCoordinates()[0], base_forearm_joint.getCoordinates()[1], 0.0f);
  glRotatef(base_forearm_joint_RA, 0.0f, 0.0f, 1.0f);
  glTranslatef(-base_forearm_joint.getCoordinates()[0], -base_forearm_joint.getCoordinates()[1], 0.0f);
  base_forearm_joint.draw();
  forearm.draw();

  glPushMatrix();
  glTranslatef(forearm_upper_arm_joint.getCoordinates()[0], forearm_upper_arm_joint.getCoordinates()[1], 0.0f);
  glRotatef(forearm_upper_arm_joint_RA, 0.0f, 0.0f, 1.0f);
  glTranslatef(-forearm_upper_arm_joint.getCoordinates()[0], -forearm_upper_arm_joint.getCoordinates()[1], 0.0f);
  forearm_upper_arm_joint.draw();
  upper_arm.draw();

  glPushMatrix();
  glTranslatef(upper_arm_gripper_joint.getCoordinates()[0], upper_arm_gripper_joint.getCoordinates()[1], 0.0f);
  glRotatef(upper_arm_gripper_joint_RA, 0.0f, 0.0f, 1.0f);
  glTranslatef(-upper_arm_gripper_joint.getCoordinates()[0], -upper_arm_gripper_joint.getCoordinates()[1], 0.0f);
  upper_arm_gripper_joint.draw();
  gripper.draw();

  glPopMatrix(); // gripper
  glPopMatrix(); // upper arm
  glPopMatrix(); // forearm
  glPopMatrix(); // base
  
  glFlush();
}

/**
 * @brief Handles standard keyboard input.
 * 
 * Space key toggles between active parts (base, joints, etc.).
 * Each part is visually highlighted and enabled for interaction.
 * 
 * @param key Pressed key.
 * @param x Mouse x-coordinate.
 * @param y Mouse y-coordinate.
 */
void Window::keyboard(unsigned char key, int x, int y){
  switch (key) {
    case ' ': {
      active = static_cast<ActivePart>((active + 1) % 4);

      // Deactivate all parts
      gripper.deactivate();
      upper_arm_gripper_joint.deactivate();
      upper_arm.deactivate();
      forearm_upper_arm_joint.deactivate();
      forearm.deactivate();
      base_forearm_joint.deactivate();
      base.deactivate();

      glutPostRedisplay();

      // Activate current part
      switch (active) {
        case BASE:
          base.activate();
          break;
        case BASE_FOREARM_JOINT:
          base_forearm_joint.activate();
          forearm.activate();
          break;
        case FOREARM_UPPER_ARM_JOINT:
          forearm_upper_arm_joint.activate();
          upper_arm.activate();
          break;
        case UPPER_ARM_GRIPPER_JOINT:
          upper_arm_gripper_joint.activate();
          gripper.activate();
          break;
      }

      glutPostRedisplay();
      break;
    }
  }
}

/**
 * @brief Handles special keyboard input (arrow keys).
 * 
 * LEFT/RIGHT rotate or translate components depending on the selected active part.
 * UP/DOWN control the gripper angle when it's the active part.
 * 
 * @param key Special key (GLUT_KEY_*).
 * @param x Mouse x-coordinate.
 * @param y Mouse y-coordinate.
 */
void Window::specialKeyboard(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT: {
      float delta = (key == GLUT_KEY_RIGHT) ? -ROTATE_STEP : ROTATE_STEP;

      switch (active) {
        case BASE: {
          Coordinates coordinates = base.getCoordinates();
          int base_x = coordinates[0] + baseTX;
          int right_limit = width / 3.0 - base.getWidth();
          int left_limit = 0;

          if (key == GLUT_KEY_RIGHT && base_x + MOVE_STEP < right_limit) {
            baseTX += MOVE_STEP;
          } else if (key == GLUT_KEY_LEFT && base_x - MOVE_STEP > left_limit) {
            baseTX -= MOVE_STEP;
          }
          break;
        }

        case BASE_FOREARM_JOINT:
          base_forearm_joint_RA = std::clamp(base_forearm_joint_RA + delta, MIN_ANGLE, MAX_ANGLE);
          break;

        case FOREARM_UPPER_ARM_JOINT:
          forearm_upper_arm_joint_RA = std::clamp(forearm_upper_arm_joint_RA + delta, MIN_ANGLE, MAX_ANGLE);
          break;

        case UPPER_ARM_GRIPPER_JOINT:
          upper_arm_gripper_joint_RA = std::clamp(upper_arm_gripper_joint_RA + delta, MIN_ANGLE, MAX_ANGLE);
          break;
      }

      break;
    }

    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN: {
      if (active == UPPER_ARM_GRIPPER_JOINT) {
        float delta = (key == GLUT_KEY_UP) ? -ROTATE_STEP : ROTATE_STEP;
        float new_angle = std::clamp(gripper.getAngle() + delta, MIN_ANGLE, 0.0f);
        gripper.setAngle(new_angle);
      }

      break;
    }
  }

  glutPostRedisplay();
}

/**
 * @brief Starts the GLUT main loop.
 */
void Window::run(){
  glutMainLoop();
}
