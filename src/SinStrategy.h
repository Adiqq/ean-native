#ifndef SIN_STRATEGY_H
#define SIN_STRATEGY_H

#include <PointStrategy.h>
#include <math.h>

class SinStrategy : public PointStrategy {
public:
  std::vector<Point*> getPoints(int n, double min, double max);
  std::vector<IntervalPoint*> getIntervalPoints(int n, double min, double max);
};

#endif