#ifndef ROGUELIKE_ACTION_TIME_TIMEELAPSED_H_
#define ROGUELIKE_ACTION_TIME_TIMEELAPSED_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {
namespace time {

struct TimeElapsed {
    bool elapsed;
    double  time;

    TimeElapsed(bool elapsed) : elapsed(elapsed), time( 0.0) {}
    TimeElapsed(double  time) : elapsed(  true ), time(time) {}

    operator   bool() const { return elapsed; }
    operator double() const { return    time; }

    TimeElapsed& operator+=(const TimeElapsed &rhs) {
        if( (bool)rhs == false ) return *this;
        this->elapsed = true;
        this->time += (double)rhs;
        return *this;
    }
};

} // namespace time
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_TIME_TIMEELAPSED_H_ */