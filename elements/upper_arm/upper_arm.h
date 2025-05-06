#ifndef UPPER_ARM_H
  #define UPPER_ARM_H

  #include "../../abstract_classes/drawable.h"

/**
 * @brief Represents the upper arm component in a drawable structure.
 * 
 * Inherits from the Drawable abstract class and implements a rectangular
 * shape representing the upper arm of a robotic or graphical structure.
 */
  class UpperArm : public Drawable {
    private:
      /**
       * @brief Internal state specific to the UpperArm.
       * 
       * Extends the base State structure for potential future enhancements.
       */
      struct ExtendedState : public State {
      } upperArmState;
    
    public:
      /**
       * @brief Constructs an UpperArm object with given properties.
       * 
       * @param coordinates The (x, y) position of the upper arm.
       * @param width The width of the upper arm.
       * @param height The height of the upper arm.
       * @param color The RGB color of the upper arm.
       */
      UpperArm(Coordinates coordinates, int width, int height, Color color);

      /**
       * @brief Draws the upper arm on screen.
       * 
       * Implements the draw method defined by the Drawable interface.
       */
      void draw() override;
  };
#endif
