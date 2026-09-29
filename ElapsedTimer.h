#ifndef WORKER_CLOCK_ELAPSED_TIMER_H
#define WORKER_CLOCK_ELAPSED_TIMER_H

// Tracks elapsed time as a single running total, exposing it as H:M:S.
class ElapsedTimer {
 public:
  void tick() { totalSeconds_++; }

  long hours() const { return totalSeconds_ / 3600; }
  long minutes() const { return (totalSeconds_ / 60) % 60; }
  long seconds() const { return totalSeconds_ % 60; }

 private:
  long totalSeconds_ = 0;
};

#endif // WORKER_CLOCK_ELAPSED_TIMER_H
