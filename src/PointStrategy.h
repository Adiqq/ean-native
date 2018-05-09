#ifndef POINT_STRATEGY_H
#define POINT_STRATEGY_H
#include <vector>
#include <Point.h>
#include <IntervalPoint.h>
class PointStrategy {
public:
  virtual std::vector<Point*> getPoints(int n, double min, double max) = 0;
  virtual std::vector<IntervalPoint*> getIntervalPoints(int n, double min, double max) = 0;
};

#endif