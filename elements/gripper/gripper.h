#ifndef GRIPPER_H
  #define GRIPPER_H

  #include "../../abstract_classes/drawable.h"

  /**
   * @brief Represents the gripper component in the graphical structure.
   * 
   * The Gripper class is a concrete implementation of the Drawable abstract class.
   * It defines the state of the gripper, including the angle and the coordinates of
   * the left and right parts, and provides a draw method to render the gripper.
   */
  class Gripper : public Drawable {
    private:
      /**
       * @brief Extended internal state for the Gripper class.
       *
       * Inherits from Drawable::State and adds properties specific to the gripper,
       * such as angle and the coordinates of the left and right parts.
       */
      struct ExtendedState : public State {
        float angle;                           /**< The angle of rotation for the gripper. */
        Coordinates left_part_coordinates;     /**< Coordinates of the left part of the gripper. */
        Coordinates right_part_coordinates;    /**< Coordinates of the right part of the gripper. */
      } gripperState;

    public:
      /**
       * @brief Constructs a Gripper object with position, size, color, and part coordinates.
       * 
       * Initializes the gripper's left and right parts' coordinates, width, height, color, 
       * and angle of rotation.
       * 
       * @param left_part_coordinates The (x, y) position of the left part of the gripper.
       * @param right_part_coordinates The (x, y) position of the right part of the gripper.
       * @param width The width of the gripper.
       * @param height The height of the gripper.
       * @param color The RGB color of the gripper.
       */
      Gripper(Coordinates left_part_coordinates, Coordinates right_part_coordinates, int width, int height, Color color);

      /**
       * @brief Sets the angle of rotation for the gripper.
       * 
       * @param angle The desired angle to rotate the gripper (in degrees).
       */
      void setAngle(float angle);

      /**
       * @brief Gets the current angle of rotation of the gripper.
       * 
       * @return The current rotation angle of the gripper.
       */
      float getAngle();

      /**
       * @brief Draws the gripper component on the screen.
       * 
       * Overrides the pure virtual draw method from Drawable.
       * The gripper is rendered based on its position, size, color, and angle of rotation.
       */
      void draw() override;
  };

#endif
