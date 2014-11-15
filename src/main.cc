// External Dependencies
#include <time.h>

#include <ugdk/script.h>
#include <ugdk/system/engine.h>
#include <ugdk/script/scriptmanager.h>
#include <ugdk/script/virtualobj.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"   // needed for GameController::reference()
#include "game/base/levelmanager.h"


int main(int argc, char **argv) {
	ugdk::system::Configuration engine_config;
	engine_config.windows_list[0].title = "Undeadest. Game. Ever.";
    engine_config.base_path = "./data/";

	ugdk::script::InitScripts();
	ugdk::system::Initialize(engine_config);

    
    {
        SCRIPT_MANAGER()->LoadModule("init_constants");
    }

    srand ( (int)time(NULL) );
	auto main_scene = ugdk::MakeUnique<game::base::GameController>();

    game::base::LevelManager* lm = new game::base::LevelManager();
    lm->GenerateFromFile();

	ugdk::system::PushScene(std::move(main_scene));

	ugdk::system::Run();
	ugdk::system::Release();
    return 0;
}