// External Dependencies
#include <ugdk/base/engine.h>           // needed for engine
#include <ugdk/graphic/videomanager.h>  // needed for SetVSync()

// Internal Dependencies
#include "game/base/gamecontroller.h"   // needed for GameController::reference()
#include "game/action/time/timemanager.h"

//TODO: MANOMANOMANOMANOMANOMANO
static void LevelLoader();
// endMANOMANOMANOMANOMANOMANO

int main(int argc, char **argv) {
	ugdk::Configuration engine_config;
	engine_config.window_title = "AWESUMENFUCKINTASTIC-EST. Game. Ever.";
	engine_config.window_size = ugdk::Vector2D(1200.0, 900.0);
	engine_config.fullscreen = false;
    engine_config.base_path = "./data/";

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);
	engine->video_manager()->SetVSync(true);

    ugdk::action::Scene* main_scene = game::base::GameController::reference();
    LevelLoader();

    engine->PushScene(main_scene);
    engine->Run();

    engine->Release();
    return 0;
}

#include "game/base/gameobject.h"
#include "game/builder/objectbuilder.h"
#include "game/component/shape.h"
#include "game/component/vision.h"

static void LevelLoader() {

    using ugdk::math::Integer2D;
    using game::base::GameController;
    using game::base::GameObject;
    using game::builder::ObjectBuilder;

    GameController* gc = GameController::reference();

    // Time for hard-coded awesomeness to start!
    ObjectBuilder builder = ObjectBuilder();

    // Build the basic instances
    GameObject* hero;
    gc->set_hero(hero = builder.BuildHero());

	gc->AddGameObject(hero);
    GameObject* enemy = builder.BuildEnemy();
	gc->AddGameObject(enemy);
	GameObject* item = builder.BuildItem();
	gc->AddGameObject(item);

    GameObject* wall_1 = builder.BuildWall();
    gc->AddGameObject(wall_1);
    GameObject* wall_2 = builder.BuildWall();
    gc->AddGameObject(wall_2);
    GameObject* wall_3 = builder.BuildWall();
    gc->AddGameObject(wall_3);
    GameObject* wall_4 = builder.BuildWall();
    gc->AddGameObject(wall_4);
    GameObject* wall_5 = builder.BuildWall();
    gc->AddGameObject(wall_5);
    GameObject* wall_6 = builder.BuildWall();
    gc->AddGameObject(wall_6);
    GameObject* wall_7 = builder.BuildWall();
    gc->AddGameObject(wall_7);
    GameObject* wall_8 = builder.BuildWall();
    gc->AddGameObject(wall_8);
    GameObject* wall_9 = builder.BuildWall();
    gc->AddGameObject(wall_9);
    GameObject* wall_0 = builder.BuildWall();
    gc->AddGameObject(wall_0);

    // Place them on the map.
    hero->shape_component()->PlaceAt(Integer2D(10,4));
    enemy->shape_component()->PlaceAt(Integer2D(35,4));
    item->shape_component()->PlaceAt(Integer2D(2,2));
    wall_1->shape_component()->PlaceAt(Integer2D(17,8));
    wall_2->shape_component()->PlaceAt(Integer2D(18,8));
    wall_3->shape_component()->PlaceAt(Integer2D(19,8));
    wall_4->shape_component()->PlaceAt(Integer2D(30,0));
    wall_5->shape_component()->PlaceAt(Integer2D(18,20));
    wall_6->shape_component()->PlaceAt(Integer2D(19,21));
    wall_7->shape_component()->PlaceAt(Integer2D(18,22));
    wall_8->shape_component()->PlaceAt(Integer2D(18,15));
    wall_9->shape_component()->PlaceAt(Integer2D(17,16));
    wall_0->shape_component()->PlaceAt(Integer2D(18,17));
}
