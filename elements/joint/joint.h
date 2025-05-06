#ifndef JOINT_H
  #define JOINT_H

  #include "../../abstract_classes/drawable.h"

  /**
   * @brief A class representing a joint in a 2D space.
   * 
   * The Joint class inherits from the Drawable abstract class and is responsible
   * for rendering a circular joint with a specified radius. The joint can be drawn
   * with a given color and positioned at specified coordinates.
   * 
   * It stores the radius of the joint and can be drawn as a filled circle or outlined shape.
   * 
   * @see Drawable
   */
  class Joint : public Drawable {
    private:
      /**
       * @brief Represents the extended state of the joint.
       * 
       * The extended state includes the radius of the joint and the number of segments
       * used to approximate the circle shape. The `segments` value is set to 100 by default.
       */
      struct ExtendedState : public State {
        int radius;  ///< Radius of the joint.
        int segments = 100;  ///< Number of segments used to approximate the circle.
      } jointState;

    public:
      /**
       * @brief Constructs a Joint object with given coordinates, radius, and color.
       * 
       * Initializes the joint's position, radius, and color.
       * 
       * @param coordinates The (x, y) position of the joint.
       * @param ray The radius of the joint.
       * @param color The RGB color of the joint.
       */
      Joint(Coordinates coordinates, int ray, Color color);

      /**
       * @brief Draws the joint using OpenGL.
       * 
       * Overrides the pure virtual draw method from Drawable. The joint is rendered as a circle
       * with the given radius and color. The number of segments defines the approximation of the circle.
       * 
       * @see Drawable::draw()
       */
      void draw() override;
  };

#endif
