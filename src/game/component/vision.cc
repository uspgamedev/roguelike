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
    left_eye_(0,0,0.1,0.1,0.9,0.2), right_eye_(0,0,0.1,0.1,0.9,0.2) {

    for(int i = 0; i < 8; ++i)
        relevant_octants_.insert((i+0)%8);
    
    eyes_.insert(  &left_eye_ );
    eyes_.insert( &right_eye_ );
    losprocessor_ = new Processor(relevant_octants_,visible_tiles_,range_,eyes_,blocks_vision);
}

Vision::~Vision() {
    delete losprocessor_;
}

void Vision::See() {
    if( gamecontroller_->TilesNeededBlackout() ) {
        
        left_eye_.coords = *(owner_->shape_component()->occupying_tiles().begin());
        right_eye_.coords = left_eye_.coords + Integer2D(1,0);
        
        losprocessor_->Process();
        for(auto vt = visible_tiles_.begin() ; vt != visible_tiles_.end() ; ++vt) {
            gamecontroller_->MarkVisible(*vt);
        }
    }
}

void Vision::CycleOctant() {
	auto rt = relevant_octants_.begin();
	int i = *rt;
	while( (++rt != relevant_octants_.end()) && i+1 == *(rt) )
		++i;
	if( rt != relevant_octants_.end() )
		relevant_octants_.erase(*rt);
	else
		relevant_octants_.erase(*(relevant_octants_.begin()));
	
	relevant_octants_.insert((i+1)%8);
    See();
}

} // namespace component
} // namespace game