#include "SinStrategy.h"

#define PI 3.14159265

std::vector<Point*> SinStrategy::getPoints(int n, double min, double max ){
    auto vec = std::vector<Point*>();
    double step = (2*PI)/n;
    double range = max - min;
    for(int i = 0; i < n; i++){
        Point *point = new Point();
        point->x = i;
        point->y = (sin(i * step) * range) + range;
        vec.push_back(point);
    }
    return vec;
}

std::vector<IntervalPoint*> SinStrategy::getIntervalPoints(int n, double min, double max){
    auto vec = std::vector<IntervalPoint*>();
    double step = (2*PI)/n;
    double range = max - min;
    for(int i = 0; i < n; i++){
        IntervalPoint *point = new IntervalPoint();
        point->x = i;
        point->y = (sin(i * step) * range) + range;
        vec.push_back(point);
    }
    return vec;
}