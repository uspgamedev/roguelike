// Header File
#include "game/component/controller_ai.h"

// External Dependencies
#include <cmath>
#include <cstdlib>
#include <vector>
#include "ugdk/math/integer2D.h"

// Internal Dependencies
#include "game/action/time/timeelapsed.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/energy.h"
#include "game/component/vision.h"

// Using
using ugdk::math::Integer2D;
using game::action::time::TimeElapsed;
using game::base::GameController;

struct PathElement {
    Integer2D offset_;
    Integer2D step_;
    double walked_distance_;
    double distance_to_target_;
} path;

class ElementComparator {
    public:
        ElementComparator() {}
        bool operator()(const PathElement& lhs, const PathElement& rhs) {
            if (lhs.walked_distance_ + lhs.distance_to_target_ > rhs.walked_distance_ + rhs.distance_to_target_)
                return true;
            return false;
        }
};

namespace game {
namespace component {

ControllerAi::ControllerAi(game::base::GameObject* owner) : super(owner) {}
ControllerAi::~ControllerAi() {}

TimeElapsed ControllerAi::Act() {
    GameController* gc = GameController::reference();

    Cast("see");
    
    Integer2D hero_pos = Integer2D(-1, -1);
    Integer2D this_pos = (*owner_->shape_component()->occupying_tiles().begin());

    for(auto it = owner_->vision_component()->visible_tiles().begin(); it != owner_->vision_component()->visible_tiles().end(); ++it)
        for(auto git = gc->Tile(*it)->objects_here().begin(); git != gc->Tile(*it)->objects_here().end(); ++git)
            if( (*git) == gc->hero())
                hero_pos = (*gc->hero()->shape_component()->occupying_tiles().begin());

    if(hero_pos == Integer2D(-1, -1))
        return Cast("idle", owner_);
    else
        target_ = gc->Tile(hero_pos);

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
        for(auto cait = owner_->shape_component()->occupying_tiles().begin(); cait != owner_->shape_component()->occupying_tiles().end(); ++cait)
            if( ((*tait) - (*cait)).Length() < 2 )
                return true;
    return false;
}

void ControllerAi::HearSound(int intensity) {
    //TODO: implement
}

Integer2D ControllerAi::TryPath(Integer2D destination, Integer2D origin) {
    for(int i = 0; i < map_.size(); ++i)
        for(int j = 0; j < map_[0].size(); ++j)
            map_[i][j] = INT_MAX;
    for(auto  it = owner_->vision_component()->visible_tiles().begin();  it != owner_->vision_component()->visible_tiles().end(); ++it)
        map_[(*it).x][(*it).y] = INT_MAX;
    for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it)
        map_[(*it).x][(*it).y] = 0;

    GameController* gc = GameController::reference();

    //TODO: WARNING: This shit only works with Rectangular Shapes.
    bool walkable = false;
    Integer2D return_value = Integer2D(0, 0);
    double return_distance = 0.0;
    
    for(auto it = owner_->shape_component()->occupying_tiles().begin(); it != owner_->shape_component()->occupying_tiles().end(); ++it )
        if( (*it) == destination )
            return Integer2D(0, 0);

    std::priority_queue<PathElement, std::vector<PathElement>, ElementComparator> elements;
    PathElement starting_point;
    starting_point.step_ = Integer2D(0, 0);
    starting_point.offset_ = Integer2D(0, 0);
    starting_point.walked_distance_ = 0;
    starting_point.distance_to_target_ = (destination - origin).Length();
    elements.push(starting_point);

    do {
        PathElement element = elements.top();
        elements.pop();
        Integer2D path   = element.offset_;
        Integer2D step   = element.step_;
        double distance  = element.walked_distance_;
        
        distance += 1;
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
                        if( (*it) + path + offset == destination)
                            return step;
                    PathElement new_element = element;
                    if( new_element.step_ == Integer2D(0, 0) )
                        new_element.step_ = offset;
                    else
                        new_element.step_ = step;
                    new_element.distance_to_target_ = (destination - (origin + path + offset)).Length();
                    new_element.walked_distance_    = distance;
                    new_element.offset_ = element.offset_ + offset;
                    elements.push(new_element);
                }
            }
    } while(!elements.empty());
    
    printf("No step.\n\n");
    return Integer2D(0, 0);
}

/*static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}*/

} // namespace component
} // namespace game