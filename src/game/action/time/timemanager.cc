
// Header File
#include "game/action/time/timemanager.h"

// External Dependencies
#include <cassert>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/component/controller.h"
#include "game/component/energy.h"

// Using
using std::set;
using game::base::GameController;
using game::base::GameObject;
using game::component::Energy;

namespace game {
namespace action {
namespace time {

void TimeManager::operator()(double) {
    if( actors_.empty() ) {
        GameController::reference()->Finish();
        return;
    }

    GameObject* next = *(actors_.begin());
    TimeElapsed time_elapsed = next->controller_component()->Act();
    if(time_elapsed) {
        assert( static_cast<double>(time_elapsed) >= 0.0 ); // Remove this if you want to allow time_elapsed < 0.0
        time_has_passed(time_elapsed);
    }
}

void TimeManager::time_has_passed(const TimeElapsed& time) {
    ObjectQueue new_actors(actors_.key_comp());

    for(auto at = actors_.begin(); at != actors_.end() ; ++at) {
        (*at)->energy_component()->Regen(time);
        new_actors.insert(*at);
    }

    actors_.swap(new_actors);
    game::base::GameController::reference()->PassTime(time);
}

} // namespace time
} // namespace action
} // namespace game
