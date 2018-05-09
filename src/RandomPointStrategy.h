#ifndef RANDOM_POINT_STRATEGY_H
#define RANDOM_POINT_STRATEGY_H

#include <PointStrategy.h>
#include <random>

class RandomPointStrategy : public PointStrategy {
public:
  std::vector<Point*> getPoints(int n, double min, double max);
  std::vector<IntervalPoint*> getIntervalPoints(int n, double min, double max);
private:
  double getRandom(double min, double max);
  std::default_random_engine re;
};

#endif