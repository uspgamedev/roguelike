#ifndef ROGUELIKE_BASE_LEVELMANAGER_H_
#define ROGUELIKE_BASE_LEVELMANAGER_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace base {

class LevelManager {

  public:
    LevelManager();
    ~LevelManager();

    void GenerateFromFile();
    void GenerateCaveLevel();

};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_LEVELMANAGER_H_