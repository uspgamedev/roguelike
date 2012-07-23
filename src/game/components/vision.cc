// Header File
#include "game/components/vision.h"

// External Dependencies
#include <list>
// (none)
#include <ugdk/graphic/node.h>  //TODO rem.
#include <ugdk/graphic/modifier.h> //TODO rem.

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/alg/losprocessor.h"

// Using
using std::list;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using game::alg::LosProcessor;

namespace game {
namespace component {

Vision::Vision(game::base::GameObject* owner) : super(owner), range_(29.5), initialized_(false) {

    for(int i = 1; i <= 8; ++i)
        relevant_octants_.insert(nth_orientation(i));

/*
    for(int i = 2; i <= 7; ++i)
        relevant_octants_.insert(nth_orientation(i));
*/

//    relevant_octants_.insert(nth_orientation(1));
//    relevant_octants_.insert(nth_orientation(2));
//    relevant_octants_.insert(nth_orientation(3));
//    relevant_octants_.insert(nth_orientation(4));
//    relevant_octants_.insert(nth_orientation(5));
//    relevant_octants_.insert(nth_orientation(6));
//    relevant_octants_.insert(nth_orientation(7));
//    relevant_octants_.insert(nth_orientation(8));

    losprocessor_ = new LosProcessor(this);
}

Vision::~Vision() {
    delete losprocessor_;
}

void Vision::Initialize() {
    initialized_ = true;
    /*
    for(int i = 1; i <= 8; ++i)
        relevant_octants_.insert(nth_orientation(i));
    */
    relevant_octants_.insert(1);
    See();
}

void Vision::MarkVisible(const GameTile* tile) {
    tile->node()->modifier()->set_visible(true);
    //TODO: use visible_tiles_
}

void Vision::Update(double) {}

void Vision::See() {
    if(initialized_) {
        const GameController* gamecontroller = GameController::reference();

        gamecontroller->BlackoutTiles();
        losprocessor_->Process();
    }
}

void Vision::CycleOctant() {
    std::map<int,int> octs;

    for(int i = 1; i <= 9; ++i)
        octs[nth_orientation(i)] = i;

    auto rt = relevant_octants_.begin();
    int o = octs[*rt] + 1;
    if(o >= 9) o = 1;
    relevant_octants_.clear();
    relevant_octants_.insert(nth_orientation(o));
    See();
}

bool Vision::BlocksVision(const GameTile* tile) {
    //TODO: POARR NAO TUDO BLOCA VISAO NEH
    const list<GameObject*> stuff = tile->objects_here();
    for(auto ot = stuff.begin(); ot != stuff.end(); ++ot) {
        if(*ot != owner_) return true;
    }
    return false;
}

} // namespace component
} // namespace game