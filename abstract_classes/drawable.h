#ifndef DRAWABLE_H
  #define DRAWABLE_H

  #include <array>
  #include <GL/freeglut.h>

  /**
   * @brief Type alias for 2D coordinates (x, y).
   */
  typedef std::array<int, 2> Coordinates;

  /**
   * @brief Type alias for RGB color.
   */
  typedef std::array<float, 3> Color;

  /**
   * @brief Abstract base class for drawable objects.
   *
   * Provides a common interface and state (position, size, color, activation)
   * that can be shared among derived graphical elements.
   */
  class Drawable {
    protected:
      /**
       * @brief Internal structure representing the state of a drawable object.
       */
      struct State {
        Coordinates coordinates;  ///< Object position (x, y)
        int width;                ///< Object width
        int height;               ///< Object height
        Color color;              ///< Object color (RGB)
        bool isActive = false;    ///< Whether the object is active (filled)
      };

      State* state = nullptr;  ///< Pointer to the actual state managed by the subclass

    public:
      /**
       * @brief Draw the object.
       *
       * This function must be implemented by subclasses.
       */
      virtual void draw() = 0;

      /**
       * @brief Set the position of the object.
       * @param coordinates The (x, y) position.
       */
      void setCoordinates(Coordinates coordinates){
        state->coordinates = coordinates;
      }

      /**
       * @brief Get the position of the object.
       * @return Reference to the (x, y) position.
       */
      const Coordinates& getCoordinates(){
        return state->coordinates;
      }

      /**
       * @brief Set the width of the object.
       * @param width The new width value.
       */
      void setWidth(int width){
        state->width = width;
      }

      /**
       * @brief Get the width of the object.
       * @return The width value.
       */
      int getWidth(){
        return state->width;
      }

      /**
       * @brief Set the height of the object.
       * @param height The new height value.
       */
      void setHeight(int height){
        state->height = height;
      }

      /**
       * @brief Get the height of the object.
       * @return The height value.
       */
      int getHeight(){
        return state->height;
      }

      /**
       * @brief Set the color of the object.
       * @param color RGB color as an array of floats.
       */
      void setColor(Color color){
        state->color = color;
      }

      /**
       * @brief Get the color of the object.
       * @return Reference to the RGB color.
       */
      const Color& getColor(){
        return state->color;
      }

      /**
       * @brief Mark the object as active (filled).
       */
      void activate(){
        state->isActive = true;
      }

      /**
       * @brief Check if the object is active.
       * @return True if active, false otherwise.
       */
      bool isActive(){
        return state->isActive;
      }

      /**
       * @brief Deactivate the object (rendered as wireframe).
       */
      void deactivate(){
        state->isActive = false;
      }
  };

#endif
