// Header File
#include "game/component/controller_player.h"

// External Dependencies
#include <list>
#include <ugdk/base/engine.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gamething.h"
#include "game/component/shape.h"
#include "game/component/vision.h"

// Using
using std::list;
using ugdk::input::InputManager;
using ugdk::math::Integer2D;
using ugdk::time::TimeAccumulator;
using game::action::time::TimeElapsed;
using game::base::GameObject;
using game::base::GameThing;

namespace game {
namespace component {

#define DELAY_HOLD 250
#define HOLD_TICK_INTERVAL 25

ControllerPlayer::ControllerPlayer(GameObject* owner)
  : super(owner), where_to_(0,0), time_held_(DELAY_HOLD), hold_tick_(HOLD_TICK_INTERVAL) {
    time_held_.Pause();
    hold_tick_.Pause();
}
ControllerPlayer::~ControllerPlayer() {}

TimeElapsed ControllerPlayer::Act() {
    //double time_carry = super::Act(); //TODO: herp.
    Cast("see");

    InputManager* input = INPUT_MANAGER();

    // Derp stuff
    if( input->KeyPressed(ugdk::input::K_z) )
        return Cast("ouch");
    if( input->KeyPressed(ugdk::input::K_f) )
        return Cast("fire",Integer2D(35,4)); //TODO: MANOMANOMANO

    // Movement
    if( input->KeyPressed(ugdk::input::K_RIGHT) || input->KeyPressed(ugdk::input::K_LEFT) ||
        input->KeyPressed(ugdk::input::K_UP)    || input->KeyPressed(ugdk::input::K_DOWN) ) {

        time_held_.Restart(DELAY_HOLD);
        hold_tick_.Restart(HOLD_TICK_INTERVAL);

        if(input->KeyPressed(ugdk::input::K_RIGHT)) {
            if(     input->KeyDown(ugdk::input::K_UP)  ) where_to_ = Integer2D( 1,-1);
            else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Integer2D( 1, 1);
            else where_to_ = Integer2D( 1, 0);
        }
        else if(input->KeyPressed(ugdk::input::K_LEFT)) {
            if(     input->KeyDown(ugdk::input::K_UP)  ) where_to_ = Integer2D(-1,-1);
            else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Integer2D(-1, 1);
            else where_to_ = Integer2D(-1, 0);
        }
        else if(input->KeyPressed(ugdk::input::K_UP)) {
            if(     input->KeyDown(ugdk::input::K_LEFT) ) where_to_ = Integer2D(-1,-1);
            else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Integer2D( 1,-1);
            else where_to_ = Integer2D( 0,-1);
        }
        else { // if(input->KeyPressed(ugdk::input::K_DOWN)) {
            if(     input->KeyDown(ugdk::input::K_LEFT) ) where_to_ = Integer2D(-1, 1);
            else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Integer2D( 1, 1);
            else where_to_ = Integer2D( 0, 1);
        }
    }

    if( input->KeyReleased(ugdk::input::K_RIGHT) || input->KeyReleased(ugdk::input::K_LEFT) ||
        input->KeyReleased(ugdk::input::K_UP)    || input->KeyReleased(ugdk::input::K_DOWN) ) {
        
        time_held_.Restart(DELAY_HOLD);
        time_held_.Pause();
        hold_tick_.Restart(HOLD_TICK_INTERVAL);
        hold_tick_.Pause();

        double ret = Cast("step",where_to_);
        where_to_ = Integer2D(0,0);

        return ret;
    }
    if ( ( input->KeyDown(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_LEFT) ||
           input->KeyDown(ugdk::input::K_UP)    || input->KeyDown(ugdk::input::K_DOWN) )
         && time_held_.Expired() && hold_tick_.Expired() ) {

        hold_tick_.Restart(HOLD_TICK_INTERVAL);
        if(where_to_.x != 0 || where_to_.y != 0) {
            return Cast("step",where_to_);
        }
    }

    return false;
}

} // namespace component
} // namespace game