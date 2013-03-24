#ifndef ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_
#define ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_

// Inheritance
#include <ugdk/action/task.h>

// External Dependencies
#include <map>
#include <vector>

// Internal Dependencies
#include "game/action/time/timeelapsed.h"
#include "game/base/gameobject.h"
#include "game/component/energy.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace time {

typedef std::set< base::GameObject*, bool (*)(const base::GameObject*, const base::GameObject*) > ObjectQueue;

class TimeManager : public ugdk::action::Task {
  typedef ugdk::action::Task super;
  struct SortStructure {
      TimeManager* manager_;
      SortStructure(TimeManager* manager) { manager_ = manager; };

      bool operator()(base::GameObject* a, base::GameObject* b) {
          if (manager_->actors_time_[a] < manager_->actors_time_[b] )
              return true;
          else if (manager_->actors_time_[a] > manager_->actors_time_[b])
              return false;
          else {
              double mean_a = a->energy_component()->Mean();
              double mean_b = b->energy_component()->Mean();
              return mean_a > mean_b || ( mean_a == mean_b && a < b );
          }
      }
  };

  public:
    TimeManager() : current_tick_(0) {}
    ~TimeManager() {}
    bool CompareFunction(base::GameObject* a, base::GameObject* b);

    void operator()(double dt);

  private:
     int current_tick_;
     void time_has_passed(const TimeElapsed& time);
     std::map<base::GameObject*, int> actors_time_;
     std::vector<base::GameObject*> actors_;

    // ObjectQueue& actors_;
};

} // namespace time
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_ */