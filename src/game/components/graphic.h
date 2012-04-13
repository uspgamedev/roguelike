#ifndef BADGAME_COMPONENT_GRAPHIC_H_
#define BADGAME_COMPONENT_GRAPHIC_H_

// Inheritance
// (none)

// External Dependencies
#include <list>                 // template class
#include <ugdk/graphic/node.h>  // needed for new Node(-)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Graphic {
  public:
    Graphic::Graphic() : owner_(nullptr), node_(new ugdk::graphic::Node()) {}
    Graphic::~Graphic() { delete node_; }

    void set_owner(game::base::GameObject* owner) { owner_ = owner; } //TODO: Mudar para ser no construtor

    virtual void Update(double dt) = 0;

	virtual void NodeLogic(const std::list<game::base::GameTile*>& occupying_tiles_) = 0;

          ugdk::graphic::Node* node()       { return node_; }
    const ugdk::graphic::Node* node() const { return node_; }

  protected:
    game::base::GameObject* owner_;

  private:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_H_