#ifndef ROGUELIKE_ACTION_SKILL_SIMPLE_H_
#define ROGUELIKE_ACTION_SKILL_SIMPLE_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
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

typedef std::tr1::function<bool (const base::GameObject*, const base::GameThing&)>
        SimpleValidator;

typedef std::tr1::function<SpendInfo (base::GameObject*, const base::GameThing&)>
        SimpleSpender;

typedef std::tr1::function<void (base::GameObject*, base::GameThing&, const Efficiency&)>
        SimpleAction;

class Simple : public Skill {
  typedef Skill super;
  public:
    Simple(const SimpleValidator& validator, const SimpleSpender& spender, const SimpleAction& action);
    virtual ~Simple() {}
    
    TimePassed operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    SimpleValidator validator_;
    SimpleSpender spender_;
    SimpleAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SIMPLE_H_