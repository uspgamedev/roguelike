// Header File
#include "game/base/gameobject.h"

// External Dependencies
#include <functional>
#include <ugdk/action/scene.h>
#include <ugdk/graphic/node.h>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/action/skill/skillmanager.h"
#include "game/component/controller.h"
#include "game/component/vision.h"
#include "game/component/damageable.h"
#include "game/component/energy.h"
#include "game/component/shape.h"
#include "game/component/sound.h"
#include "game/component/graphic.h"

// Defines
#define        USING_DEFINITION(compo,type) using game::component::type;
#define INITIALIZE_WITH_NULLPTR(compo,type) compo##_component_(nullptr),
#define       DESTRUCTOR_ACTION(compo,type) if(compo##_component_) delete compo##_component_;
#define     INI_ARG_DECLARATION(compo,type) type* compo##_component,
#define          INI_ASSIGNMENT(compo,type) compo##_component_ = compo##_component;
#define           UPDATE_ACTION(compo,type) if(compo##_component_) compo##_component_->Update(dt);

// Using
using std::string;
using std::function;
using ugdk::action::Scene;
using ugdk::math::Integer2D;
using game::action::skill::GameTargets;
using game::action::skill::SkillManager;
FORALL_COMPONENTS(USING_DEFINITION) // ;

namespace game {
namespace base {

GameObject::GameObject()
  : super(),
	FORALL_COMPONENTS(INITIALIZE_WITH_NULLPTR) // ,
    die_() {}

GameObject::~GameObject() {
	FORALL_COMPONENTS(DESTRUCTOR_ACTION) // ;
}

void GameObject::Initialize( FORALL_COMPONENTS(INI_ARG_DECLARATION) // ;
                             const function<void (void)>& die) {
    FORALL_COMPONENTS(INI_ASSIGNMENT) // ;
    die_ = die;
}

void GameObject::Update(double dt) {
    FORALL_UPDATEABLE_COMPONENTS(UPDATE_ACTION) // ;
}

void GameObject::Die() {
    GameController* gc = base::GameController::reference();

    if(die_) // if die_ is a valid tr1::function
        die_();
    to_be_removed_ = true;
    gc->RequireBlackout();
}

void GameObject::OnSceneAdd(Scene* scene) {
    graphic_component()->OnSceneAdd(scene);
}

} // namespace base
} // namespace game