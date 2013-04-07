#ifndef ROGUELIKE_COMPONENT_CONTROLLER_AI_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_AI_H_

// Inheritance
#include "game/base/gamecontroller.h"
#include "game/component/controller.h"

// External Dependencies
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <climits>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gamething.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ControllerAi : public Controller {
  typedef Controller super;
  // lacks operator=
  ControllerAi& operator=(const ControllerAi&);

  public:
    ControllerAi(game::base::GameObject* owner);
    ~ControllerAi();

    action::time::TimeElapsed Act();
    void NewMapSize(int x, int y);
    void NewMapSize(ugdk::math::Integer2D size);
    bool InMeleeRange(game::base::GameObject* target);
    ugdk::math::Integer2D TryPath(ugdk::math::Integer2D, ugdk::math::Integer2D);
    void HearSound(int intensity);

  private:
    std::vector< std::vector<double> > map_;
    std::vector< std::vector<double> > clean_map_;
    std::deque<ugdk::math::Integer2D> tile_queue_;
    game::base::GameTile* target_;
    int hostility_level_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_AI_H_