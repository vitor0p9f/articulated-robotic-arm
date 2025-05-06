#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <vector>

#include "../abstract_classes/drawable.h"
#include "../elements/gripper/gripper.h"
#include "../elements/base/base.h"
#include "../elements/forearm/forearm.h"
#include "../elements/upper_arm/upper_arm.h"
#include "../elements/joint/joint.h"

/**
 * @brief Enumeration of parts that can be set as active for manipulation.
 */
enum ActivePart {
  BASE,
  BASE_FOREARM_JOINT,
  FOREARM_UPPER_ARM_JOINT,
  UPPER_ARM_GRIPPER_JOINT
};

/**
 * @brief The Window class manages the OpenGL rendering window and handles user interaction.
 * 
 * This class encapsulates the scene including robotic parts like the base, forearm,
 * upper arm, joints, and gripper. It handles keyboard input to manipulate parts
 * and manages rendering through GLUT callbacks.
 */
class Window {
  private:
    static int width;                         ///< Width of the window.
    int height;                               ///< Height of the window.
    int x_position;                           ///< Initial x-position of the window.
    int y_position;                           ///< Initial y-position of the window.
    static int baseTX;                        ///< Base horizontal translation value.
    static float base_forearm_joint_RA;       ///< Rotation angle of base-forearm joint.
    static float forearm_upper_arm_joint_RA;  ///< Rotation angle of forearm-upper arm joint.
    static float upper_arm_gripper_joint_RA;  ///< Rotation angle of upper arm-gripper joint.
    static const float MAX_ANGLE;             ///< Maximum rotation angle.
    static const float MIN_ANGLE;             ///< Minimum rotation angle.
    static const int BASE_LIMIT;              ///< Limit for base translation.
    static const int MOVE_STEP;               ///< Step size for translation.
    static const float ROTATE_STEP;           ///< Step size for rotation.
    static ActivePart active;                 ///< Currently selected active part.
    static Gripper gripper;                   ///< Gripper object.
    static Base base;                         ///< Base object.
    static ForeArm forearm;                   ///< Forearm object.
    static UpperArm upper_arm;                ///< Upper arm object.
    static Joint base_forearm_joint;          ///< Joint between base and forearm.
    static Joint forearm_upper_arm_joint;     ///< Joint between forearm and upper arm.
    static Joint upper_arm_gripper_joint;     ///< Joint between upper arm and gripper.

  public:
    /**
     * @brief Constructs a Window object and initializes the OpenGL environment.
     * 
     * @param argc Argument count from main.
     * @param argv Argument vector from main.
     */
    Window(int argc, char** argv);

    /**
     * @brief Display callback for rendering the scene.
     */
    static void display();

    /**
     * @brief Handles ASCII keyboard inputs for interaction.
     * 
     * @param key The key that was pressed.
     * @param x The x-position of the mouse.
     * @param y The y-position of the mouse.
     */
    static void keyboard(unsigned char key, int x, int y);

    /**
     * @brief Handles special keyboard inputs (arrow keys, etc.).
     * 
     * @param key The special key that was pressed.
     * @param x The x-position of the mouse.
     * @param y The y-position of the mouse.
     */
    static void specialKeyboard(int key, int x, int y);

    /**
     * @brief Starts the main event loop for rendering and input handling.
     */
    void run();
};

#endif
