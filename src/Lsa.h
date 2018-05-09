#ifndef LSA_H
#define LSA_H

#include <nan.h>
#include <Point.h>
#include <vector>
class Lsa : public Nan::ObjectWrap {
public:
  std::vector<Point*> points;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(AddPoint);
  static NAN_METHOD(CalculateA0);
  static NAN_METHOD(CalculateA1);
  static NAN_METHOD(GetError);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif
