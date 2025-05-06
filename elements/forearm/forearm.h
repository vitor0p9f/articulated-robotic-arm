#ifndef FOREARM_H
  #define FOREARM_H

  #include "../../abstract_classes/drawable.h"

  /**
   * @brief Represents the forearm component in the graphical structure.
   * 
   * The ForeArm class is a concrete implementation of the Drawable abstract class.
   * It provides a method to draw the forearm with specific position, size, and color.
   */
  class ForeArm : public Drawable {
    private:
      /**
       * @brief Extended internal state for the ForeArm class.
       *
       * Inherits from Drawable::State, currently without additional fields,
       * but this structure can be extended in the future.
       */
      struct ExtendedState : public State {
      } foreArmState;
    
    public:
      /**
       * @brief Constructs a ForeArm object with position, size, and color.
       * 
       * @param coordinates The (x, y) position of the forearm.
       * @param width The width of the forearm.
       * @param height The height of the forearm.
       * @param color The RGB color of the forearm.
       */
      ForeArm(Coordinates coordinates, int width, int height, Color color);

      /**
       * @brief Draws the forearm component on the screen.
       *
       * Overrides the pure virtual draw method from Drawable.
       * The forearm is rendered based on its position, size, and color.
       */
      void draw() override;
  };

#endif
