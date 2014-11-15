// Header File
#include "game/component/graphic.h"

// External Dependencies
#include <ugdk/action/scene.h>
#include <ugdk/graphic/node.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using std::string;
using ugdk::action::Scene;
using ugdk::ui::Node;
using game::base::GameObject;

namespace game {
namespace component {

Graphic::Graphic(GameObject* owner, const string& visual_representation, double zindex)
  : super(owner), node_(new Node()) {
    node_->set_zindex(zindex);
}
Graphic::~Graphic() { delete node_; }

void Graphic::OnSceneAdd(Scene* scene) {
    scene->content_node()->AddChild(node_);
}

void Graphic::SetVisibility(bool visibility) {
    node_->modifier()->set_visible(visibility);
}

} // namespace component
} // namespace game