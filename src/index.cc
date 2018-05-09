#include <nan.h>
#include "Vector.h"
#include "Point.h"
#include "Lsa.h"
#include "LsaInterval.h"
#include "IntervalPoint.h"
#include "PointFactory.h"

NAN_MODULE_INIT(InitModule) {
  Vector::Init(target);
  Point::Init(target);
  Lsa::Init(target);
  LsaInterval::Init(target);
  IntervalPoint::Init(target);
  PointFactory::Init(target);
}

NODE_MODULE(myModule, InitModule);
