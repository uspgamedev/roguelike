#ifndef ROGUELIKE_ALG_LOS_PROCESSOR_H_
#define ROGUELIKE_ALG_LOS_PROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <array>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <set>

// Internal Dependencies
#include "game/alg/los/eye.h"

// Forward Declarations
#include <ugdk/math.h>
#include "utils/integer2Dutils.h"
#include "game/alg.h"

namespace game {
namespace alg {
namespace los {

class Processor {
  // lacks operator=
  Processor& operator=(const Processor&);

  public:
    Processor(const std::set<int>& relevant_octants, std::set<ugdk::math::Integer2D>& visible_tiles,
              const double& sight_range, const std::set<Eye*>& eyes,
              const std::tr1::function<bool (const ugdk::math::Integer2D&)>& blocks_vision);
    ~Processor();

    void Process();

  private:
    const std::set<int>& relevant_octants_;
    std::set<ugdk::math::Integer2D>& visible_tiles_;

    std::array<OctantProcessor*,8> octants_;
};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_PROCESSOR_H_