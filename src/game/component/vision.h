#ifndef ROGUELIKE_COMPONENT_VISION_H_
#define ROGUELIKE_COMPONENT_VISION_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <list> // eye_coords()
#include <set> // relevant_octants_, eyes_
#include <ugdk/math/frame.h> // eye_frame_

// Internal Dependencies
#include "game/alg/los/eye.h"
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Forward Declarations
#include <ugdk/math.h>
#include "utils/integer2Dutils.h"
#include "game/base.h"
#include "game/alg.h"

namespace game {
namespace component {

class Vision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Vision(game::base::GameObject* owner);
    virtual ~Vision();

    const base::GameObject* owner() const { return owner_; }
    const std::set<int>& relevant_octants() const { return relevant_octants_; }

    void See();

    void set_dir(const ugdk::math::Integer2D& dir) { dir_ = dir; }

    void clean_visible_tiles() { visible_tiles_.clear(); }
    void see_tile(ugdk::math::Integer2D tile) { visible_tiles_.insert(tile); }

  private:
    void face_ahead();
    void update_octants(int start);

    double range_;
    std::set<int> relevant_octants_;
    std::set<ugdk::math::Integer2D> visible_tiles_;
    alg::los::Processor* losprocessor_;

    alg::los::Eye left_eye_;
    alg::los::Eye right_eye_;
    std::set<alg::los::Eye*> eyes_;

    bool initialized_;
    game::base::GameController* gamecontroller_;

    ugdk::math::Integer2D dir_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_VISION_H_