#ifndef ROGUELIKE_BASE_LEVELMANAGER_H_
#define ROGUELIKE_BASE_LEVELMANAGER_H_

// Inheritance
// none

// External Dependencies
// none

// Internal Dependencies
#include "game/base/gamecontroller.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

class LevelManager {

  public:

    LevelManager();
    ~LevelManager();

    void GenerateFromFile();
    void GenerateCaveLevel();

  private:
    GameController* gc;

};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_LEVELMANAGER_H_