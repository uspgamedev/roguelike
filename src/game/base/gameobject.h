#ifndef ROGUELIKE_BASE_GAMEOBJECT_H_
#define ROGUELIKE_BASE_GAMEOBJECT_H_

// Inheritance
// (none)

// External Dependencies
#include <set>
#include <string>
#include <functional>
#include <list>                 // template class
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
#include "game/action/skill/skill.h"

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

// Defines
#define FORALL_UPDATEABLE_COMPONENTS(action)    \
    action(    graphic,    Graphic)

#define FORALL_COMPONENTS(action)           \
    action( controller, Controller)         \
    action(     vision,     Vision)         \
    action( damageable, Damageable)         \
    action(     energy,     Energy)         \
    action(      shape,      Shape)         \
    action(    graphic,    Graphic)         \
    action(      sound,      Sound)


#define FULL_TYPE(type) component::type*

#define INI_FULLTYPE_ARG_DECLARATION(compo,type) FULL_TYPE(type) compo##_component,

#define GETTER_DECLARATION(compo,type)                                              \
          FULL_TYPE(type) compo##_component()       { return compo##_component_; }  \
    const FULL_TYPE(type) compo##_component() const { return compo##_component_; }

#define SETTER_DECLARATION(compo,type)                                                                          \
    void set_##compo##_component(FULL_TYPE(type) compo##_component) { compo##_component_ = compo##_component; }

#define ATTRIBUTES_DECLARATION(compo,type) FULL_TYPE(type) compo##_component_;


namespace game {
namespace base {

class GameObject {
  public:
    GameObject();
    ~GameObject();

    void Initialize(
        FORALL_COMPONENTS(INI_FULLTYPE_ARG_DECLARATION) // note lack of ","
        const std::function<void (void)>& die = std::function<void (void)>()
    );

    void Update(double dt);
    
    FORALL_COMPONENTS(GETTER_DECLARATION) // ends in "}"
    FORALL_COMPONENTS(SETTER_DECLARATION) // ends in "}"

    void Die();
    bool dead() const { return to_be_removed_; }
    
    void OnSceneAdd(ugdk::action::Scene* scene);

  private:
	FORALL_COMPONENTS(ATTRIBUTES_DECLARATION) // note lack of ";"

	bool to_be_removed_;

    std::function<void (void)> die_;
};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_GAMEOBJECT_H_