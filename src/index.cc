#include <nan.h>
#include "Vector.h"
#include "Point.h"
#include "Lsa.h"

NAN_MODULE_INIT(InitModule) {
  Vector::Init(target);
  Point::Init(target);
  Lsa::Init(target);
}

NODE_MODULE(myModule, InitModule);
