﻿#ifndef ROGUELIKE_ACTION_SKILL_SELF_H_
#define ROGUELIKE_ACTION_SKILL_SELF_H_

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

typedef std::function<bool (const base::GameObject*)>
        SelfValidator;

typedef std::function<SpendInfo (base::GameObject*)>
        SelfSpender;

typedef std::function<void (base::GameObject*, const Efficiency&)>
        SelfAction;

class Self : public Skill {
  typedef Skill super;
  public:
    Self( const SelfValidator& validator,
          const   SelfSpender&   spender,
          const    SelfAction&    action  );
    virtual ~Self() {}

    time::TimeElapsed operator()(base::GameObject* caster, const GameTargets&);

  private:
    SelfValidator validator_;
    SelfSpender     spender_;
    SelfAction       action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SELF_H_