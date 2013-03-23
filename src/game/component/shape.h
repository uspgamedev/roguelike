#ifndef ROGUELIKE_COMPONENT_SHAPE_H_
#define ROGUELIKE_COMPONENT_SHAPE_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <set> // template class
#include <ugdk/math/integer2D.h>
#include "utils/integer2Dutils.h"

// Internal Dependencies
#include "game/action/aim.h"

// Forward Declarations
#include "game/base.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"

namespace game {
namespace component {

class Shape : public ComponentBase {
  typedef ComponentBase super;
  public:
    Shape(game::base::GameObject* owner, double stay_sizeclass = 1.0, double pass_sizeclass = 0.25, double enter_sizeclass = 1.0e-5 )
      : super(owner), stay_sizeclass_(stay_sizeclass), pass_sizeclass_(pass_sizeclass), enter_sizeclass_(enter_sizeclass), aim_(nullptr) {}
    virtual ~Shape() {
        for(auto it = occupying_tiles_.begin(); it != occupying_tiles_.end(); it++)
            base::GameController::reference()->Tile((*it))->RemoveObject(this->owner_);
        if(aim_) delete aim_;
    }

    void set_stay_sizeclass(  double stay_sizeclass ) { stay_sizeclass_  = stay_sizeclass;  }
    void set_pass_sizeclass(  double pass_sizeclass ) { pass_sizeclass_  = pass_sizeclass;  }
    void set_enter_sizeclass( double enter_sizeclass) { enter_sizeclass_ = enter_sizeclass; }

    double stay_sizeclass()  const { return stay_sizeclass_;  }
    double pass_sizeclass()  const { return pass_sizeclass_;  }
    double enter_sizeclass() const { return enter_sizeclass_; }
    const std::set<ugdk::math::Integer2D>& occupying_tiles() const { return occupying_tiles_; } 
          std::set<ugdk::math::Integer2D>& occupying_tiles()       { return occupying_tiles_; }

    action::Aim* aim() { return aim_; } 

    virtual const ugdk::math::Integer2D& PlaceAt(const ugdk::math::Integer2D& tile) = 0;
    virtual const ugdk::math::Integer2D& Move(const std::list<ugdk::math::Integer2D>& mov) = 0;
    virtual const ugdk::math::Integer2D& Step(const ugdk::math::Integer2D& dir) = 0;

    virtual bool TryPlace(const ugdk::math::Integer2D& destination, game::base::GameObject* ignore = 0) const = 0;

  protected:
    double stay_sizeclass_;
    double pass_sizeclass_;
    double enter_sizeclass_;
	std::set<ugdk::math::Integer2D> occupying_tiles_;

    action::Aim* aim_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_SHAPE_H_