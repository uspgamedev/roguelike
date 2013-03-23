// Header File
#include "game/component/controller_ai.h"

// External Dependencies
#include <cmath>
#include <cstdlib>
#include "ugdk/math/integer2D.h"

// Internal Dependencies
#include "game/action/time/timeelapsed.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/energy.h"
#include "game/component/vision.h"

// Using
using ugdk::math::Integer2D;

namespace game {
namespace component {

action::time::TimeElapsed ControllerAi::Act() {
    Cast("see");
    for(int i = 0; i < map_.size(); ++i)
        for(int j = 0; j < map_[0].size(); ++j)
            map_[i][j] = INT_MAX;
    //for(auto it = owner_->vision_component()->visible_tiles().begin(); it != owner_->vision_component()->visible_tiles().end(); ++it)
    //    map_[(*it).x][(*it).y] = INT_MAX;
    for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it)
        map_[(*it).x][(*it).y] = 0;

    game::base::GameController* gc = game::base::GameController::reference();
    Integer2D hero_pos = Integer2D(-1, -1);
    Integer2D this_pos = (*owner_->shape_component()->occupying_tiles().begin());

    for(auto it = owner_->vision_component()->visible_tiles().begin(); it != owner_->vision_component()->visible_tiles().end(); ++it)
        for(auto git = gc->Tile(*it)->objects_here().begin(); git != gc->Tile(*it)->objects_here().end(); ++git)
            if( (*git) == gc->hero())
                hero_pos = (*gc->hero()->shape_component()->occupying_tiles().begin());

    if(hero_pos == Integer2D(-1, -1))
        return Cast("idle", owner_);
    else
        target_ = game::base::GameThing(hero_pos);

    if(InMeleeRange(gc->hero()))
        return Cast("melee", gc->hero());

    Integer2D dir;
    if(hero_pos.x - this_pos.x == 0)
        dir.x = 0;
    else
        dir.x = (hero_pos.x - this_pos.x)/abs(hero_pos.x - this_pos.x);

    if(hero_pos.y - this_pos.y == 0)
        dir.y = 0;
    else
        dir.y = (hero_pos.y - this_pos.y)/abs(hero_pos.y - this_pos.y);

    owner_->vision_component()->set_dir(dir);

    Integer2D step = TryPath(hero_pos, this_pos);
    if((step.x != 0 || step.y != 0) && owner_->shape_component()->TryPlace(this_pos + step))
        return Cast("step", step);
    return Cast("idle", owner_);
    
}

void ControllerAi::NewMapSize(ugdk::math::Integer2D size) {
    map_.resize(size.x);
    clean_map_.resize(size.x);
    for(int i = 0; i < size.x; ++i) {
        map_[i].resize(size.y);
        clean_map_.resize(size.y);
    }
}

void ControllerAi::NewMapSize(int x, int y) {
    map_.resize(x);
    clean_map_.resize(x);
    for(int i = 0; i < x; ++i) {
        map_[i].resize(y);
        clean_map_.resize(y);
    }
}

bool ControllerAi::InMeleeRange(game::base::GameObject* target) {
    for(auto tait = target->shape_component()->occupying_tiles().begin(); tait != target->shape_component()->occupying_tiles().end(); ++tait)
        for(auto cait = owner_->shape_component()->occupying_tiles().begin(); cait != owner_->shape_component()->occupying_tiles().end(); ++cait) {
            printf("%f\n", ((*tait) - (*cait)).Length());
            if( ((*tait) - (*cait)).Length() < 2 )
                return true;
        }
    return false;
}

void ControllerAi::HearSound(int intensity) {
    if (target_.is_obj() ) {

    }
}

Integer2D ControllerAi::TryPath(Integer2D destination, Integer2D origin) {
    //WARNING: This shit only works with Rectangular Shapes.
    bool walkable = false;
    Integer2D return_value = Integer2D(0, 0);
    int return_distance = 0;
    std::queue<Integer2D> paths;
    std::queue<Integer2D> steps;
    std::queue<int>       distances;

    for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it )
        if( (*it) == destination )
            return Integer2D(0, 0);

    paths.push(Integer2D(0, 0));
    steps.push(Integer2D(0, 0));
    distances.push(1);

    do {
        Integer2D path = paths.front();
        Integer2D step     = steps.front();
        int       distance = distances.front();
        paths.pop();
        steps.pop();
        distances.pop();

        if( (return_value.x != 0 || return_value.x != 0) && distance > return_distance )
            return return_value;

        for(int i = -1; i < 2; i++)
            for(int j = -1; j < 2; j++) {
                //check if is an actual step
                if(i == 0 && j == 0)
                    continue;
                Integer2D offset = Integer2D(i, j);
                //check if object can be placed here
                if(!owner_->shape_component()->TryPlace(origin + path + offset, gc->hero()))
                    continue;
                //check if path not checked already
                for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it )
                    if(map_[(*it).x + path.x + i][(*it).y + path.y + j] > distance) {
                        map_[(*it).x + path.x + i][(*it).y + path.y + j] = distance;
                        walkable = true;
                    }
                if(walkable) {
                    walkable = false;
                    for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it )
                        if( (*it) + path + offset == destination && (return_value == Integer2D(0, 0) ||
                            (destination - step).Length() < (destination - return_value).Length() ) ) {
                                return_value = step;
                                return_distance = distance;
                        }
                    paths.push(path + offset);
                    if(step == Integer2D(0, 0))
                        steps.push(offset);
                    else
                        steps.push(step);
                    distances.push(distance + 1);
                }
            }
    } while(!paths.empty());

    return return_value;
}

/*static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}*/

} // namespace component
} // namespace game