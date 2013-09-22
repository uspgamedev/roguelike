#ifndef ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_
#define ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <list> //TODO: Use a better data structure for cones_.
#include <set>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <ugdk/math/integer2D.h>
#include "utils/integer2Dutils.h"

// Internal Dependencies
#include "game/alg/los/cone.h"
#include "game/alg/los/eye.h"
#include "game/alg/los/octant.h"

// Forward Declarations
#include "game/alg.h"
#include "game/alg/los.h"

namespace game {
namespace alg {
namespace los {

class OctantProcessor {
    // lacks operator=

  public:
    OctantProcessor(int octant_id, const VisibleTileAction& visible_tile_action, const double& sight_range,
                    const std::set<Eye*>& eyes, const std::tr1::function<bool (const ugdk::math::Integer2D&)>& blocks_vision);
    ~OctantProcessor();

    void ProcessOctant();

	void set_origin(const ugdk::math::Integer2D& origin) { octant_.set_origin(origin); }

  private:
    bool process_cone_here(Cone* cone);
    void clean_cones();

    Octant octant_;
    std::list<Cone*> cones_;
    
    const VisibleTileAction visible_tile_action_;
    const double& sight_range_;
    const std::set<Eye*>& eyes_;

    const std::tr1::function<bool (ugdk::math::Integer2D&)> blocks_vision_;
	const std::tr1::function<bool (Cone*)> cone_processor_; // process_cone_here's incarnation as a non-method function.
};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_