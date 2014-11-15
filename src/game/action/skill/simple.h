#ifndef ROGUELIKE_ACTION_SKILL_SIMPLE_H_
#define ROGUELIKE_ACTION_SKILL_SIMPLE_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
#include <functional>

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

typedef std::function<bool (const base::GameObject*, const base::GameThing&)>
        SimpleValidator;

typedef std::function<SpendInfo (base::GameObject*, const base::GameThing&)>
        SimpleSpender;

typedef std::function<void (base::GameObject*, base::GameThing&, const Efficiency&)>
        SimpleAction;

class Simple : public Skill {
  typedef Skill super;
  public:
    Simple(const SimpleValidator& validator, const SimpleSpender& spender, const SimpleAction& action);
    virtual ~Simple() {}
    
    time::TimeElapsed operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    SimpleValidator validator_;
    SimpleSpender spender_;
    SimpleAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SIMPLE_H_