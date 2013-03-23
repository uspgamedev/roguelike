#ifndef ROGUELIKE_COMPONENT_SOUND_H_
#define ROGUELIKE_COMPONENT_SOUND_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace component {

class Sound : public ComponentBase {
  typedef ComponentBase super;
  public:
    Sound(game::base::GameObject* owner) : super(owner) {}
    ~Sound() {}

    bool TryListen(int noise_level);

  private:
    int sound_sensitivity_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_SOUND_H_