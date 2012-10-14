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
// (none)

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
struct TimePassed {
    bool passed;
    double time;

    TimePassed(bool passed) : passed(passed), time(-1.0) {} // meant to be used only with passed == false.
    TimePassed(double time) : passed( true ), time(time) {}

    operator   bool() { return passed; }
    operator double() { return   time; }
};
struct SpendInfo {
    TimePassed timepassed;
    Efficiency efficiency;

    SpendInfo(const TimePassed& timepassed, const Efficiency& efficiency)
      : timepassed(timepassed), efficiency(efficiency) {}

    operator       bool() { return timepassed; }
    operator Efficiency() { return efficiency; }
    operator TimePassed() { return timepassed; }
};

typedef std::tr1::function<void (base::GameObject*, const GameTargets&, const Efficiency&)>
        GameAction;

class Skill {
  public:
    Skill() {}
    virtual ~Skill() {}

    virtual TimePassed operator()(base::GameObject* caster, const GameTargets& targets) = 0;
    virtual TimePassed operator()(base::GameObject* caster, const ugdk::math::Integer2D& target);
    virtual TimePassed operator()(base::GameObject* caster, base::GameObject* target);
    virtual TimePassed operator()(base::GameObject* caster);

    // Needed for GenericContainer
    static Skill* LoadFromFile(const std::string&) { return nullptr; }
};


} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILL_H_ */