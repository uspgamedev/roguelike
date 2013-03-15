// External Dependencies
#include <time.h>
#include <ugdk/modules.h>
#include <ugdk/base/engine.h>           // needed for engine
#include <ugdk/graphic/videomanager.h>  // needed for SetVSync()
#include <ugdk/script/scriptmanager.h>
#include <ugdk/script/virtualobj.h>
#include <ugdk/script/languages/lua/luawrapper.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"   // needed for GameController::reference()
#include "game/base/levelmanager.h"
#include "game/action/time/timemanager.h"

static void InitScripts() {
    using ugdk::script::lua::LuaWrapper;

    //inicializando lua
    LuaWrapper* lua_wrapper = new LuaWrapper();
    ugdk::RegisterLuaModules(lua_wrapper);
    SCRIPT_MANAGER()->Register("Lua", lua_wrapper);
}

int main(int argc, char **argv) {
	ugdk::Configuration engine_config;
	engine_config.window_title = "AWESUMENFUCKINTASTIC-EST. Game. Ever.";
	engine_config.window_size = ugdk::Vector2D(1200.0, 900.0);
	engine_config.fullscreen = false;
    engine_config.base_path = "./data/";

    ugdk::Engine* engine = ugdk::Engine::reference();
    InitScripts();
    engine->Initialize(engine_config);
    
    {
        SCRIPT_MANAGER()->LoadModule("init_constants");
    }

	engine->video_manager()->SetVSync(true);
    engine->video_manager()->SetLightSystem(true);

    srand ( time(NULL) );
    ugdk::action::Scene* main_scene = game::base::GameController::reference();
    game::base::LevelManager* lm = new game::base::LevelManager();
    lm->GenerateFromFile();
    //LevelLoader();

    engine->PushScene(main_scene);
    engine->Run();

    engine->Release();
    return 0;
}