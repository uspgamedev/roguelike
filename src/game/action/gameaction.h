#ifndef ROGUELIKE_ACTION_GAMEACTION_H_
#define ROGUELIKE_ACTION_GAMEACTION_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {

// Arguments: caster, targets, power.
typedef std::tr1::function<void (base::GameObject*, const std::list<base::GameThing*>&, double)>
        GameAction;

// Arguments: caster, targets.
// Return value: true if valid, false if not valid.
typedef std::tr1::function<bool (const base::GameObject*, const std::list<base::GameThing*>&)>
        TargetValidator;

// Arguments: caster, targets.
// Return value: double representing the power at the spent cost.
//               0.0 means "not enough minimum resources", 1.0 means "100% power".
typedef std::tr1::function<double (base::GameObject*, const std::list<base::GameThing*>&)>
        ResourceSpender;

} // nmespace base
} // namespace game

#endif /* BADGAME_BASE_GAMEACTION_H_ */