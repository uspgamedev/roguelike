// Header File
#include "game/component/vision.h"

// External Dependencies
#include <set>
#include <ugdk/math/frame.h>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/alg/los/processor.h"

// Using
using std::set;
using ugdk::math::Integer2D;
using game::alg::los::Eye;
using game::alg::los::Processor;
using game::base::GameController;
using game::base::GameObject;

namespace game {
namespace component {

bool blocks_vision(const Integer2D& tile) {
    const GameController* gc = GameController::reference();

    return !gc->Tile(tile)->objects_here().empty();
}

Vision::Vision(game::base::GameObject* owner)
  : super(owner), range_(20.5),
    initialized_(false), gamecontroller_(GameController::reference()),
    left_eye_(0,0,0.40,0.40,0.60,0.60), right_eye_(0,0,0.40,0.40,0.60,0.60),
    dir_(0,-1) {

    for(int i = 0; i < 6; ++i)
        relevant_octants_.insert((i+5)%8);
    
    eyes_.insert(  &left_eye_ );
    eyes_.insert( &right_eye_ );
    losprocessor_ = new Processor(relevant_octants_,visible_tiles_,range_,eyes_,blocks_vision);
}

Vision::~Vision() {
    delete losprocessor_;
}

void Vision::See() {
    if( gamecontroller_->TilesNeededBlackout() ) {
        face_ahead();
        losprocessor_->Process();
        for(auto vt = visible_tiles_.begin() ; vt != visible_tiles_.end() ; ++vt) {
            gamecontroller_->MarkVisible(owner_, *vt);
        }
    }
}

void Vision::face_ahead() {
    if(dir_.x == 1) {
        if(dir_.y == 1) {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(1,0);
            right_eye_.coords = left_eye_.coords + Integer2D(-1,1);
            update_octants(0);
        } else if(dir_.y == 0) {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(1,0);
            right_eye_.coords = left_eye_.coords + Integer2D(0,1);
            update_octants(7);
        } else /* if(dir_.y == -1) */ {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin());
            right_eye_.coords = left_eye_.coords + Integer2D(1,1);
            update_octants(6);
        }
    } else if(dir_.x == 0) {
        if(dir_.y == 1) {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(1,1);
            right_eye_.coords = left_eye_.coords + Integer2D(-1,0);
            update_octants(1);
        } else /* if(dir_.y == -1) */ {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin());
            right_eye_.coords = left_eye_.coords + Integer2D(1,0);
            update_octants(5);
        } 
    } else if(dir_.x == -1) {
        if(dir_.y == 1) {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(1,1);
            right_eye_.coords = left_eye_.coords + Integer2D(-1,-1);
            update_octants(2);
        } else if(dir_.y == 0) {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(0,1);
            right_eye_.coords = left_eye_.coords + Integer2D(0,-1);
            update_octants(3);
        } else /* if(dir_.y == -1) */ {
            left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin()) + Integer2D(0,1);
            right_eye_.coords = left_eye_.coords + Integer2D(1,-1);
            update_octants(4);
        }
    }
}

void Vision::update_octants(int start) {
    relevant_octants_.clear();
    for(int i = 0; i < 6; ++i)
        relevant_octants_.insert((i+start)%8);
}

} // namespace component
} // namespace game