// Header File
#include "game/component/controller_player.h"

// External Dependencies
#include <list>
#include <ugdk/base/engine.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>
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
using ugdk::math::Vector2D;
using ugdk::time::TimeAccumulator;
using game::action::Aim;
using game::action::time::TimeElapsed;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameThing;

namespace game {
namespace component {

#define DELAY_HOLD 250
#define HOLD_TICK_INTERVAL 25

ControllerPlayer::ControllerPlayer(GameObject* owner)
  : super(owner), where_to_(Integer2D(0,0)),
    time_held_(DELAY_HOLD), hold_tick_(HOLD_TICK_INTERVAL),
    gc(game::base::GameController::reference()){
    time_held_.Pause();
    hold_tick_.Pause();
}
ControllerPlayer::~ControllerPlayer() {}

TimeElapsed ControllerPlayer::Act() {
    //double time_carry = super::Act(); //TODO: change the time system of the game
    TimeElapsed total_time_elapsed = TimeElapsed(false);
    InputManager* input = INPUT_MANAGER();

    // Cursor
    Aim* aim = owner_->shape_component()->aim();
    if (aim->IsActive()) {
        total_time_elapsed += cursor(aim);
        Cast("see");
        return total_time_elapsed;
    }

    if( input->KeyPressed(ugdk::input::K_s) ) {
        gc->SpawnMonster();
    }

    if( input->KeyPressed(ugdk::input::K_f) ) {
        where_to_ = Integer2D(0,0);
        aim->AimAt((*owner_->shape_component()->occupying_tiles().begin()));
        aim->ToggleAim();
        return false;
    }

    // Derp stuff //TODO: Derp. Remove.
    if( input->KeyPressed(ugdk::input::K_z) ) {
        total_time_elapsed += Cast("ouch");
        Cast("see");
        return total_time_elapsed;
    }

    total_time_elapsed += Cast("step", movement());
    Cast("see");
    return total_time_elapsed;
}

TimeElapsed ControllerPlayer::cursor(Aim* aim) {
    InputManager* input = INPUT_MANAGER();

    if(input->KeyPressed(ugdk::input::K_ESCAPE)) {
        where_to_ = *(owner_->shape_component()->occupying_tiles().begin());
        aim->ToggleAim();
        return false;
    }
    
    if( input->KeyPressed(ugdk::input::K_f) )
        return Cast("fire", aim->AimedAt());

    aim->AimAt(aim->AimedAt() + movement());
    return false;
}


// brocoli's somewhatly awesomely movementely codely.
Integer2D ControllerPlayer::movement() {
    InputManager* input = INPUT_MANAGER();

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

        Integer2D ret = where_to_;
        where_to_ = Integer2D(0, 0);

        return ret;
    }
    if ( ( input->KeyDown(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_LEFT) ||
           input->KeyDown(ugdk::input::K_UP)    || input->KeyDown(ugdk::input::K_DOWN) ) ) {

        if( time_held_.Expired() && hold_tick_.Expired() ) {
            hold_tick_.Restart(HOLD_TICK_INTERVAL);
            return where_to_;
        }

    } else {
        time_held_.Restart(DELAY_HOLD);
        time_held_.Pause();
        hold_tick_.Restart(HOLD_TICK_INTERVAL);
        hold_tick_.Pause();

        where_to_ = Integer2D(0,0);
    }

    return Integer2D(0,0);
}


} // namespace component
} // namespace game