#ifndef ROGUELIKE_ACTION_SKILL_SKILL_H_
#define ROGUELIKE_ACTION_SKILL_SKILL_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <string>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
#include "game/action/time/timeelapsed.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

typedef std::list<base::GameThing> GameTargets;

struct Efficiency {
    double efficiency;

    Efficiency(double efficiency) : efficiency(efficiency) {}

    operator double() { return efficiency; }
};
struct SpendInfo {
    time::TimeElapsed time_elapsed;
    Efficiency    efficiency;

    SpendInfo(const time::TimeElapsed& time_elapsed, const Efficiency& efficiency)
      : time_elapsed(time_elapsed), efficiency(efficiency) {}

    operator              bool() { return time_elapsed; }
    operator        Efficiency() { return   efficiency; }
    operator time::TimeElapsed() { return time_elapsed; }
};

typedef std::tr1::function<void (base::GameObject*, const GameTargets&, const Efficiency&)>
        GameAction;

class Skill {
  public:
    Skill() {}
    virtual ~Skill() {}

    virtual time::TimeElapsed operator()(base::GameObject* caster, const GameTargets& targets) = 0;
    virtual time::TimeElapsed operator()(base::GameObject* caster, const ugdk::math::Integer2D& target);
    virtual time::TimeElapsed operator()(base::GameObject* caster, base::GameObject* target);
    virtual time::TimeElapsed operator()(base::GameObject* caster);

    // Needed for GenericContainer
    static Skill* LoadFromFile(const std::string&) { return nullptr; }
};


} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILL_H_ */