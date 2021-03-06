// Header File
#include "game/component/controller.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/action/skill/skillmanager.h"
#include "game/base/gameobject.h"
#include "game/component/energy.h"

// Using
using std::string;
using ugdk::math::Integer2D;
using game::action::skill::GameTargets;
using game::action::skill::SkillManager;
using game::action::time::TimeElapsed;
using game::base::GameObject;

namespace game {
namespace component {
    
TimeElapsed Controller::Act() {
    return owner_->energy_component()->PopTimeCarry();
}

TimeElapsed Controller::Cast(const string& skill, const GameTargets& targets) {
    return SkillManager::reference()->Cast(skill,owner_,targets);
}
TimeElapsed Controller::Cast(const string& skill, const Integer2D& target) {
    return SkillManager::reference()->Cast(skill,owner_,target);
}
TimeElapsed Controller::Cast(const string& skill, GameObject* target) {
    return SkillManager::reference()->Cast(skill,owner_,target);
}
TimeElapsed Controller::Cast(const string& skill) {
    return SkillManager::reference()->Cast(skill,owner_);
}

} // namespace component
} // namespace game