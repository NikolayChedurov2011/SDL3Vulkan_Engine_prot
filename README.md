# SDL3Vulkan_Engine_prot
"Engine prototype". Playground to learn and implement tech stack, patterns etc. 

**At the moment, there is no intention to build this project separately.**

## Installation and build:

```
git clone -b develop https://github.com/NikolayChedurov2011/SDL3Vulkan_Engine_prot.git --recurse-submodules
```

## How to use:

To start, implement own Game class inherited from Game_Base and include the Game_Base.h. This allow to use the game loop that controlled by tick based on the target FPS.
Your main function can be looks like this:

```
#include "Game.h"

int main(int argc, char* argv[]) {

  Game game;

  if (game.initialize()) {
    game.run();
  }
}
```

The **initialize()** function can accept with the thee parametres - window width, window height, is full screen, to set up the default window view.

For own initializations override the **postInitialize()** function that should return true of false, depends on initialization success.
Override the **update()** to update your data and **render()** to render what need.
