
// Header File
#include "game/action/time/timemanager.h"

// External Dependencies
#include <algorithm>
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

bool IsDead(GameObject* actor) {
    return actor->dead();
}

namespace game {
namespace action {
namespace time {

void TimeManager::operator()(double) {
    GameController* gc = GameController::reference();
    std::vector<GameObject*> actors = gc->actors();
    if(!actors.empty()) {
        for(std::vector<GameObject*>::iterator it = actors.begin(); it != actors.end(); it++) {
            actors_.push_back(*it);
            actors_time_[*it] = current_tick_;
        }
        gc->ClearActorsList();
    }

    if( actors_.empty() ) {
        gc->Finish();
        return;
    }

    GameObject* next = *(actors_.begin());
    TimeElapsed time_elapsed = next->controller_component()->Act();
    if(time_elapsed.elapsed) {
        std::vector<GameObject*>::iterator nend = std::remove_if(actors_.begin(), actors_.end(), IsDead);
        actors_.erase(nend, actors_.end());
        current_tick_++;
        assert( static_cast<double>(time_elapsed) >= 0.0 ); // Remove this if you want to allow time_elapsed < 0.0
        GameController::reference()->Spawn();
        time_has_passed(time_elapsed);
        actors_time_[next] = current_tick_ + 5;
    }
}

void TimeManager::time_has_passed(const TimeElapsed& time) {

    game::base::GameController* gc = game::base::GameController::reference();

    for(std::vector<GameObject*>::iterator it = actors_.begin(); it != actors_.end() ; ++it)
        (*it)->energy_component()->Regen(time);
    SortStructure sorter(this);
    std::sort(actors_.begin(), actors_.end(), sorter);

    gc->PassTime(time);
    gc->AdjustCamera(); //TODO: move to a better place
}

} // namespace time
} // namespace action
} // namespace game
