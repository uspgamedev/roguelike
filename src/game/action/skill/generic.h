#ifndef ROGUELIKE_ACTION_SKILL_GENERIC_H_
#define ROGUELIKE_ACTION_SKILL_GENERIC_H_

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

typedef std::function<bool (const base::GameObject*, const GameTargets&)>
        GenericValidator;

typedef std::function<SpendInfo (base::GameObject*, const GameTargets&)>
        GenericSpender;

typedef GameAction
        GenericAction;

class Generic : public Skill {
  typedef Skill super;
  public:
    Generic(const GenericValidator& validator, const GenericSpender& spender, const GenericAction& action);
    virtual ~Generic() {}

    time::TimeElapsed operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    GenericValidator validator_;
    GenericSpender     spender_;
    GenericAction       action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_GENERIC_H_