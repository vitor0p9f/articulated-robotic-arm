#include "window/window.h"
#include <cstdio>

/**
 * @brief Entry point for the articulated robotic arm simulation.
 *
 * Initializes the OpenGL context and the simulation window,
 * prints control instructions to stderr, and starts the main
 * application loop that handles rendering and user interaction.
 *
 * @param argc Argument count from the command line.
 * @param argv Argument vector from the command line.
 * @return int Exit status (0 on success).
 */
int main(int argc, char** argv) {
  // Controls
  std::fprintf(stderr,
      "backspace - Toggle between parts, activating them.\n"\
      "'←' and '→' - Move or rotate the active element\n"\
      "'↑' and '↓' - Open or close gripper, if it's active\n"
  );
  
  Window window(argc, argv);

  window.run();

  return 0;
}
