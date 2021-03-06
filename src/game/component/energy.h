#ifndef ROGUELIKE_COMPONENT_ENERGY_H_
#define ROGUELIKE_COMPONENT_ENERGY_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <cmath>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Energy : public ComponentBase {
  typedef ComponentBase super;
  public:
    Energy(game::base::GameObject* owner)
      : super(owner),
              arms_(100.0),       legs_(100.0),       eyes_(100.0),
          max_arms_(100.0),   max_legs_(100.0),   max_eyes_(100.0),
        regen_arms_(  1.0), regen_legs_(  1.0), regen_eyes_(  1.0),
        time_carry_(  0.0),
         last_tick_(    0),  next_tick_(    0) {}
    ~Energy() {}

    // Getters
    double       arms() const { return       arms_; }
    double       legs() const { return       legs_; }
    double       eyes() const { return       eyes_; }
    double   max_arms() const { return   max_arms_; }
    double   max_legs() const { return   max_legs_; }
    double   max_eyes() const { return   max_eyes_; }
    double regen_arms() const { return regen_arms_; }
    double regen_legs() const { return regen_legs_; }
    double regen_eyes() const { return regen_eyes_; }
    int     last_tick() const { return  last_tick_; }
    int     next_tick() const { return  next_tick_; }

    // Setters
    void       set_arms(double       arms) {       arms_ =       arms; }
    void       set_legs(double       legs) {       legs_ =       legs; }
    void       set_eyes(double       eyes) {       eyes_ =       eyes; }
    void   set_max_arms(double   max_arms) {   max_arms_ =   max_arms; }
    void   set_max_legs(double   max_legs) {   max_legs_ =   max_legs; }
    void   set_max_eyes(double   max_eyes) {   max_eyes_ =   max_eyes; }
    void set_regen_arms(double regen_arms) { regen_arms_ = regen_arms; }
    void set_regen_legs(double regen_legs) { regen_legs_ = regen_legs; }
    void set_regen_eyes(double regen_eyes) { regen_eyes_ = regen_eyes; }
    void  set_last_tick(int     last_tick) {  last_tick_ =  last_tick; }
    void  set_next_tick(int     next_tick) {  next_tick_ =  next_tick; }

    void set_time_carry(double   time_carry) { time_carry_ = time_carry; }

    // Useful stuff
    double Mean() const { return (arms_ + legs_ + eyes_) / 3.0 ; }
    void Regen(double time) {
        arms_ = std::max(0.0, std::min(max_arms_, arms_+regen_arms_*time));
        legs_ = std::max(0.0, std::min(max_legs_, legs_+regen_legs_*time));
        eyes_ = std::max(0.0, std::min(max_eyes_, eyes_+regen_eyes_*time));
    }

    bool Spend(double arms, double legs, double eyes) {
        if(arms_ < arms) return false; // not enough arms.
        if(legs_ < legs) return false; // not enough energ.. uh, legs
        if(eyes_ < eyes) return false; // YOU REQUIRE ADITIONAL PYLONS, I MEAN, EYES.
        arms_ -= arms;
        legs_ -= legs;
        eyes_ -= eyes;
        return true;
    }

    double PopTimeCarry() { double ret = time_carry_; time_carry_ = 0.0; return ret; }

  private:
    double arms_;
    double legs_;
    double eyes_;

    double max_arms_;
    double max_legs_;
    double max_eyes_;

    double regen_arms_;
    double regen_legs_;
    double regen_eyes_;
    
    int    last_tick_;
    int    next_tick_;

    double time_carry_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_VISION_H_