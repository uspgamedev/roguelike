
// Header File
#include "game/base/levelmanager.h"

// External Dependencies
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <ugdk/graphic/node.h>
#include <ugdk/script/virtualobj.h>
#include <ugdk/script/scriptmanager.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/action/time/timemanager.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"
#include "game/base/gameobject.h"
#include "game/builder/objectbuilder.h"
#include "game/component/shape.h"

// Using
using std::endl;
using std::ofstream;
using std::string;
using std::vector;
using ugdk::math::Vector2D;
using ugdk::math::Integer2D;
using ugdk::script::VirtualObj;
using game::action::time::TimeManager;
using game::base::GameController;
using game::builder::ObjectBuilder;

namespace game {
namespace base {

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

/* Taken from:
   http://roguebasin.roguelikedevelopment.org/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels */
void LevelManager::GenerateFromFile() {
    GameController* gc = GameController::reference();

    GenerateCaveLevel();
    VirtualObj level_data = SCRIPT_MANAGER()->LoadModule("new_level");
    if(!level_data) return;

    if(!level_data["width"] || !level_data["height"] || !level_data["map"]) return;

    int width = level_data["width"].value<int>();
    int height = level_data["height"].value<int>();
    string map_string = level_data["map"].value<std::string>();
    
    ObjectBuilder builder = ObjectBuilder();
	Vector2D pos = Vector2D();
    vector< vector<GameTile*> > tiles;
    
    for(int y = 0; y < height; ++y) {
		vector<GameTile*> vect;
		pos.x = 0;
		for(int x = 0; x < width; ++x) {
			GameTile* gt = new GameTile(x, y);
            gt->node()->set_zindex(-1.0);
			gt->node()->modifier()->set_offset(pos);
			gc->content_node()->AddChild(gt->node());
			vect.push_back(gt);

			pos.x += GameController::TILE_SIZE.x;
    
		}
		tiles.push_back(vect);
		pos.y += GameController::TILE_SIZE.y;
	}
    
    gc->set_tiles(tiles);
    gc->set_map_size(Integer2D(pos.x/GameController::TILE_SIZE.x, pos.y/GameController::TILE_SIZE.y));
    gc->BlackoutTiles();

    map_string.erase( std::remove(map_string.begin(), map_string.end(), '\n'), map_string.end() );
    for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; x++) {
	        if(map_string[x + (y * width)] == '#') {
                // Creates a new wall and adds it to the map.
                GameObject* new_wall = builder.BuildWall();
                gc->AddGameObject(new_wall);
                new_wall->shape_component()->PlaceAt(Integer2D(x, y));
            }
	    }
	}
    
    GameObject* hero;
    gc->set_hero(hero = builder.BuildHero());
    gc->AddGameObject(hero);
    gc->AddTask(new TimeManager());
    int x, y;
    do {
        x = rand()%width;
        y = rand()%height;
    } while(!hero->shape_component()->TryPlace(Integer2D(x,y)));
    hero->shape_component()->PlaceAt(Integer2D(x,y));
    
}

void LevelManager::GenerateCaveLevel() {
    char map[60][60];
    char temp_map[60][60];

    int width = 60;
    int height = 60;
    int walls_nearby = 0;

    // Part 1 of the generation
    // Winit(p) = rand[0,100) < 40
    for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x)
            if(rand()%100 < 40)
                map[x][y] = '#';
            else
                map[x][y] = '.';
    
    // Part 2 of the generation
    // Rule: Repeat 4: W?(p) = R1(p) ? 5 || R2(p) ? 2
    for( int i = 0; i < 4; ++i ) {
        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                walls_nearby = 0;

                for(int j = -1; j <= 1; ++j) {
                    for(int k = -1; k <= 1; ++k)
                        if ( (x+j < 0 || x+j >= width ) || (y+k < 0 || y+k >= height ) )
                            continue;
                        else if(map[x+j][y+k] == '#')
                            walls_nearby += 1;
                }

                if(walls_nearby >= 5) {
                    temp_map[x][y] = '#';
                    continue;
                }

                walls_nearby = 0;
                for(int j = -2; j <= 2; ++j) {
                    for(int k = -2; k <= 2; ++k)
                        if ( (x+j < 0 || x+j >= width ) || (y+k < 0 || y+k >= height ) )
                            continue;
                        else if(map[x+j][y+k] == '#')
                            walls_nearby += 1;
                }
                
                if(walls_nearby <= 2)
                    temp_map[x][y] = '#';
                else
                    temp_map[x][y] = '.';
            }
        }
        for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
                map[x][y] = temp_map[x][y];
    }

    // Part 3 of the generation:
    // Repeat 3: W?(p) = R1(p) ? 5
    for( int i = 0; i < 3; ++i ) {
        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                walls_nearby = 0;

                for(int j = -1; j <= 1; ++j) {
                    for(int k = -1; k <= 1; ++k)
                        if ( (x+j < 0 || x+j >= width ) || (y+k < 0 || y+k >= height ) )
                            continue;
                        else if(map[x+j][y+k] == '#')
                            walls_nearby += 1;
                }
                
                if(walls_nearby >= 5)
                    map[x][y] = '#';
                else
                    map[x][y] = '.';
            }
        }
    }
    
    /*for(int x = 0; x < width; ++x) {
        map[x][0] = '#';
        map[x][height - 1] = '#';
    }
    
    for(int y = 1; y < height - 1; ++y) {
        map[0][y] = '#';
        map[width - 1][y] = '#';
    }*/

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            printf("%c",map[x][y]);
        }
        printf("\n");
    }

    ofstream level_file;
    level_file.open("data/scripts/new_level.lua");
    level_file << "height = " << height << endl;
    level_file << "width = " << width << endl;
    level_file << "map = [[" << endl;

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            level_file << map[x][y];
        }
        level_file << endl;
    }

    level_file << "]]";
    level_file.close();
}

} // namespace base
} // namespace game