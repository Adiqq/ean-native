#ifndef RANDOM_POINT_STRATEGY_H
#define RANDOM_POINT_STRATEGY_H

#include <PointStrategy.h>

class RandomPointStrategy : public PointStrategy {
public:
  std::vector<Point> getPoints(int n, double min, double max);
};

#endif