
// Header File
#include "game/builder/objectbuilder.h"

// External Dependencies
#include <string>
#include <limits>
#include <ugdk/graphic/light.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/modifier.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/controller_ai.h"
#include "game/component/controller_idle.h"
#include "game/component/controller_player.h"
#include "game/component/vision.h"
#include "game/component/damageable.h"
#include "game/component/energy.h"
#include "game/component/shape_rectangular.h"
#include "game/component/graphic_rectangular.h"

// Using
using std::numeric_limits;
using ugdk::graphic::Light;
using ugdk::graphic::Node;
using ugdk::Vector2D;
using game::base::GameController;
using game::base::GameObject;
using game::component::ControllerAi;
using game::component::ControllerIdle;
using game::component::ControllerPlayer;
using game::component::Vision;
using game::component::ShapeRectangular;
using game::component::Damageable;
using game::component::Energy;
using game::component::GraphicRectangular;

namespace game {
namespace builder {

GameObject* ObjectBuilder::BuildHero() {

    GameObject* hero = new GameObject();
    hero->Initialize(
        new   ControllerPlayer(hero),
        new             Vision(hero),
        new         Damageable(hero, 10.0),
        new             Energy(hero),
        new   ShapeRectangular(hero, 1, 1, 1.0, 0.25, 1.0e-9),
        new GraphicRectangular(hero, "@", 3.0),
        nullptr,
        [](){ GameController* gc = GameController::reference(); gc->BlackoutTiles(); gc->set_hero(nullptr);}
    );

    Node* light_node = new Node();
    Light* light = new Light();
    light->set_dimension(Vector2D(800.0,800.0));
    light_node->set_light(light);
    light_node->modifier()->set_offset(Vector2D(static_cast<GraphicRectangular*>(hero->graphic_component())->rect_size().x/2));
    
    hero->graphic_component()->node()->AddChild(light_node);

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {
    
    GameObject* enemy = new GameObject();
    enemy->Initialize(
        new      ControllerAi(enemy),
        new            Vision(enemy),//nullptr,
        new   Damageable(enemy, 4.0),
        new            Energy(enemy),
        new   ShapeRectangular(enemy, 4, 4, 3.0, 0.8, 1.0e-9),
        new GraphicRectangular(enemy, "E", 2.0),
        nullptr
    );
    GameController* gc = GameController::reference();
    static_cast<ControllerAi*>(enemy->controller_component())->NewMapSize(gc->map_size());
    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {

    GameObject* item = new GameObject();
    item->Initialize(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new   ShapeRectangular(item, 1, 1, 0.1, 0.025, 0.0),
        new GraphicRectangular(item, "!", 1.0),
        nullptr
    );

    return item;
}

GameObject* ObjectBuilder::BuildWall() {

    GameObject* wall = new GameObject();
    wall->Initialize(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new   ShapeRectangular(wall, 1, 1, numeric_limits<double>::infinity(), 0.0, 0.0 ),
        new GraphicRectangular(wall, "null", 1.0),
        nullptr
    );

    return wall;
}

} // namespace builder
} // namespace game