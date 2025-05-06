#ifndef BASE_H
  #define BASE_H

  #include "../../abstract_classes/drawable.h"

  /**
   * @brief Represents the base component in the graphical structure.
   * 
   * The Base class is a concrete implementation of the Drawable abstract class.
   * It defines its own internal state and provides a draw method for rendering.
   */
  class Base : public Drawable {
    private:
      /**
       * @brief Extended internal state for the Base class.
       *
       * Currently inherits from Drawable::State without additional fields,
       * but this allows future customization.
       */
      struct ExtendedState : public State {
      } baseState;
    
    public:
      /**
       * @brief Constructs a Base object with position, size, and color.
       * 
       * @param coordinates The (x, y) position of the base.
       * @param width The width of the base.
       * @param height The height of the base.
       * @param color The RGB color of the base.
       */
      Base(Coordinates coordinates, int width, int height, Color color);

      /**
       * @brief Draws the base component on the screen.
       *
       * Overrides the pure virtual draw method from Drawable.
       */
      void draw() override;
  };

#endif
