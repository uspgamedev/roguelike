#ifndef ROGUELIKE_COMPONENT_GRAPHIC_H_
#define ROGUELIKE_COMPONENT_GRAPHIC_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <set>
#include <string>

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/action.h>
#include <ugdk/graphic.h>
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace component {

class Graphic : public ComponentBase {
  typedef ComponentBase super;
  public:
    Graphic(game::base::GameObject* owner, const std::string& visual_representation, double zindex);
    virtual ~Graphic();

    virtual void Update(double dt) = 0;
    virtual void NodeLogic(const std::set<ugdk::math::Integer2D>& occupying_tiles) = 0;

    void SetVisibility(bool visibility);

    const ugdk::graphic::Node* node() const { return node_; }
          ugdk::graphic::Node* node()       { return node_; }

    void OnSceneAdd(ugdk::action::Scene* scene);

  protected:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_GRAPHIC_H_