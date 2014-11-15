
// Header File
#include "game/alg/los/processor.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/alg/los/octantprocessor.h"

// Using
using std::set;
using std::function;
using ugdk::math::Integer2D;


namespace game {
namespace alg {
namespace los {

Processor::Processor(const set<int>& relevant_octants, const VisibleTileAction& visible_tile_action,
                     const double& sight_range, const set<Eye*>& eyes,
                     const function<bool (const Integer2D&)>& blocks_vision)
  : relevant_octants_(relevant_octants), visible_tile_action_(visible_tile_action) {
    for(int i=0; i<8; ++i)
        octants_[i] = new OctantProcessor(i,visible_tile_action,sight_range,eyes,blocks_vision);
}

Processor::~Processor() {
    for(int i=0; i<8; ++i)
        delete octants_[i];
}

void Processor::Process() {
    for(auto rt = relevant_octants_.begin(); rt != relevant_octants_.end(); ++rt)
        octants_[*rt]->ProcessOctant();
}

} // namespace los
} // namespace alg
} // namespace game
