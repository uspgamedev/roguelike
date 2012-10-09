#ifndef ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_
#define ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_

// Inheritance
#include <ugdk/action/task.h>

// External Dependencies
#include <set>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace time {

typedef std::set< base::GameObject*, bool (*)(const base::GameObject*, const base::GameObject*) > ObjectQueue;

class TimeManager : public ugdk::action::Task {
  typedef ugdk::action::Task super;

  public:
    TimeManager(ObjectQueue& actors) : actors_(actors) {}
    ~TimeManager() {}

    void operator()(double dt);

  private:
     void time_has_passed(double time);

     ObjectQueue& actors_;
};

} // namespace time
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_ */