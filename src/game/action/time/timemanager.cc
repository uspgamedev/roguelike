
// Header File
#include "game/action/time/timemanager.h"

// External Dependencies
// (none)
#include <cstdio>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/component/controller.h"
#include "game/component/energy.h"

// Using
using game::base::GameController;
using game::base::GameObject;
using game::component::Energy;

namespace game {
namespace action {
namespace time {

bool obj_less::operator()(const GameObject* a, const GameObject* b) const {
    return a->energy_component()->Mean() < b->energy_component()->Mean();
}

void TimeManager::operator()(double) {
    if( actors_.empty() ) {
        GameController::reference()->Finish();
        return;
    }

    GameObject* next = actors_.top();
    actors_.pop();
    double time_spent = next->controller_component()->Act();
    if( !next->dead() ) actors_.push(next);
    // for each cara regen por time_spent.

}


} // namespace time
} // namespace action
} // namespace game
