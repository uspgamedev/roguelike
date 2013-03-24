
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
using std::sort;
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

    // Move GameController's actors_ to TimeManager's actors_
    std::vector<GameObject*> actors = gc->actors();
    if(!actors.empty()) {
        for(std::vector<GameObject*>::iterator it = actors.begin(); it != actors.end(); it++) {
            actors_.push_back(*it);
            actors_time_[*it] = current_tick_;
        }
        gc->ClearActorsList();
    }

    // End the game if the hero is no more.
    if( gc->hero() == nullptr ) {
        gc->Finish();
        return;
    }

    // Give control to the next actor, and make it act
    GameObject* next = *(actors_.begin());
    TimeElapsed time_elapsed = next->controller_component()->Act();

    //TODO: move these to a better place
    if(next == gc->hero()) {
        gc->BlackoutTiles();
        gc->AdjustCamera();
        gc->LightHeroVisibleTiles();
    }

    // Tidy up if time has elapsed.
    if((bool)time_elapsed && (double)time_elapsed > 0.0 ) { // Change this to != 0.0 if you want to allow time_elapsed < 0.0
        std::vector<GameObject*>::iterator nend = std::remove_if(actors_.begin(), actors_.end(), IsDead);
        actors_.erase(nend, actors_.end());
        current_tick_++;
        gc->Spawn();
        time_has_passed(time_elapsed);
        actors_time_[next] = current_tick_ + 5;
    }
}

void TimeManager::time_has_passed(const TimeElapsed& time) {
    //TODO: clean up old energy code
    //GameController* gc = GameController::reference();

    //for(std::vector<GameObject*>::iterator it = actors_.begin(); it != actors_.end() ; ++it)
    //    (*it)->energy_component()->Regen(time);
    SortStructure sorter = SortStructure(this);
    sort(actors_.begin(), actors_.end(), sorter);

    //gc->PassTime(time);
}

} // namespace time
} // namespace action
} // namespace game
