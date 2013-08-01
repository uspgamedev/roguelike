
// Header File
#include "game/alg/los/octantprocessor.h"

// External Dependencies
#include <cassert>
#include <ugdk/math/frame.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/equationalline.h"

// Using
using std::list;
using std::set;
using std::tr1::bind;
using std::tr1::function;
using std::tr1::placeholders::_1;
using ugdk::Frame;
using ugdk::math::Integer2D;
using ugdk::Vector2D;
using namespace game::alg::los::enums;
using game::alg::EquationalLine;

namespace game {
namespace alg {
namespace los {

OctantProcessor::OctantProcessor(int octant_id, const VisibleTileAction& visible_tile_action, const double& sight_range,
                                 const set<Eye*>& eyes, const function<bool (const Integer2D&)>& blocks_vision)
  : octant_(octant_id, sight_range*sight_range), visible_tile_action_(visible_tile_action),
    sight_range_(sight_range), eyes_(eyes), blocks_vision_(blocks_vision),
    cone_processor_(bind( &OctantProcessor::process_cone_here, this, _1 )) {
}

OctantProcessor::~OctantProcessor() { clean_cones(); }

void OctantProcessor::ProcessOctant() {
    //TODO: for each octant { for each eye { [...] } } ? (should be the opposite of this)
    for(auto et = eyes_.begin() ; et != eyes_.end() ; ++et) {
	    // Reset the octant.
        octant_.set_origin((*et)->coords);
	    octant_.iterator()->Reset();

        //TODO: delegate this next step to octant.
        // Find out the true eye frame: flip the y axis, and rotate accordingly.
        Frame eye_frame = (*et)->frame;
        Frame eye;
        switch(octant_.rotations()) {
          case 0:  eye.set_left(       eye_frame.left()   );    eye.set_top(       eye_frame.top()    );
                  eye.set_right(       eye_frame.right()  ); eye.set_bottom(       eye_frame.bottom() ); break;
          case 1:  eye.set_left(       eye_frame.top()    );    eye.set_top( 1.0 - eye_frame.right()  );
                  eye.set_right(       eye_frame.bottom() ); eye.set_bottom( 1.0 - eye_frame.left()   ); break;
          case 2:  eye.set_left( 1.0 - eye_frame.right()  );    eye.set_top( 1.0 - eye_frame.bottom() );
                  eye.set_right( 1.0 - eye_frame.left()   ); eye.set_bottom( 1.0 - eye_frame.top()    ); break;
          case 3:  eye.set_left( 1.0 - eye_frame.bottom() );    eye.set_top(       eye_frame.left()   );
                  eye.set_right( 1.0 - eye_frame.top()    ); eye.set_bottom(       eye_frame.right()  ); break;
          default: break;
        }

        // Setup the startup cones.
        EquationalLineDouble upper_line( Vector2D(eye.right(), eye.bottom()), Vector2D(  eye.right(), -sight_range_) );
	    EquationalLineDouble lower_line( Vector2D(eye.left() , eye.top()   ), Vector2D( sight_range_,     eye.top()) );

	    Cone* startup_cone = new Cone(upper_line,lower_line);
	    cones_.push_back(startup_cone);

        // Iterate through the octant.
        while(!octant_.iterator()->end()) {

            if(!octant_.FocusIsOutOfBounds()) {
                // iterate through the cone list, verifying the current focused tile.
                cones_.remove_if( cone_processor_ );
            }

            ++*(octant_.iterator());
        }
        clean_cones();
    }
}

bool OctantProcessor::process_cone_here(Cone* cone) {
    // Get the stuffs.
    Integer2D fake_coords = octant_.FakeCoordinates();
    Integer2D focus_tile = octant_.FocusCoordinates();

    // First analyse how this tile relates to this cone.
    bump::BumpType bt = cone->ComputeBumpType(fake_coords);

    // If the cone intersects with it, it is visible.
    if( bt != bump::ABV && bt != bump::BLW )
		if( !octant_.FocusIsControlTile() )
			visible_tile_action_(focus_tile,cone->upper(),cone->lower(),bt);

    // If it doesn't block the vision, then we move on and keep the cone alive.
    if(!blocks_vision_(focus_tile))
        return false;

    // Otherwise,
    Cone* newcone = nullptr;
    switch(bt) {
        case bump::BLK: // do nothing and kill this cone.
            return true;
        case bump::UPR: // do an upper bump.
            cone->UpperBump(fake_coords);
            break;
        case bump::LWR: // do a lower bump.
            cone->LowerBump(fake_coords);
            break;
        case bump::MDL: // split the cone in two, and make an upper bump and a lower bump respectively.
            newcone = new Cone(*cone); 
            cone->UpperBump(fake_coords);
            newcone->LowerBump(fake_coords);
            cones_.push_back(newcone);
            break;
        case bump::ABV: // ignore these cases
        case bump::BLW: break;
        default: assert(false); break;
    }
    return false;
}

void OctantProcessor::clean_cones() {
    for( auto ct = cones_.begin(); ct != cones_.end(); ++ct )
        delete (*ct);
    cones_.clear();
}

} // namespace los
} // namespace alg
} // namespace game
