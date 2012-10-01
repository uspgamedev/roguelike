#ifndef ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_
#define ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_

// Inheritance
#include <ugdk/action/task.h>

// External Dependencies
#include <queue>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace time {

class obj_less {
  public:
    obj_less() {}
    ~obj_less() {}
    bool operator()(const base::GameObject* a, const base::GameObject* b) const;
};

typedef std::priority_queue< base::GameObject*, std::vector<base::GameObject*>, obj_less >
        ObjectQueue;

class TimeManager : public ugdk::action::Task {
  typedef ugdk::action::Task super;

  public:
    TimeManager() {}
    ~TimeManager() {}

    void operator()(double dt);

  private:
     ObjectQueue actors_;
};

} // namespace time
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_ */