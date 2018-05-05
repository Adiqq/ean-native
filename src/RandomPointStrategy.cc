#include "RandomPointStrategy.h"
#include "Point.h"

std::vector<Point*> RandomPointStrategy::getPoints(int n, double min, double max ){
    auto vec = std::vector<Point*>();
    for(int i = 0; i < n; i++){
        Point *point = new Point();
        point->x = i;
        point->y = getRandom(min,max);
        vec.push_back(point);
    }
    return vec;
}

double RandomPointStrategy::getRandom(double min, double max){
    std::uniform_real_distribution<double> unif(min,max);
    return unif(re);
}