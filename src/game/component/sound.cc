// Header File
#include "game/component/sound.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Using
// (none)

namespace game {
namespace component {

bool Sound::TryListen(int noise_level) {
    if (noise_level > sound_sensitivity_)
        return true;
    return false;
}

} // namespace component
} // namespace game