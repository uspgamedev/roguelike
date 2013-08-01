#ifndef ROGUELIKE_ALG_LOS_H_
#define ROGUELIKE_ALG_LOS_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/alg.h"

namespace game {
namespace alg {
namespace los {

namespace enums {

namespace bump {
enum BumpType {
    ABV = 0, // tile está completamente acima do cone de visão
    UPR = 1, // tile colide com a upper line do cone apenas
    MDL = 2, // tile está dentro do cone de visão, sem colidir com nenhuma linha
    BLK = 3, // tile bloqueia o campo de visão completamente (colide com as duas linhas)
    LWR = 4, // tile colide com a lower line do cone apenas
    BLW = 5  // tile está completamente abaixo do cone de visão
};
}

} // namespace enums

typedef std::tr1::function<void (const ugdk::math::Integer2D& tile, const EquationalLineDouble& upper, const EquationalLineDouble& lower, enums::bump::BumpType bump)> VisibleTileAction;

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_H_