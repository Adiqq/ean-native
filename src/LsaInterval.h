#ifndef LSA_INTERVAL_H
#define LSA_INTERVAL_H

#include <nan.h>
#include <IntervalPoint.h>
#include <vector>
class LsaInterval : public Nan::ObjectWrap {
public:
  std::vector<IntervalPoint*> points;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(AddPoint);
  static NAN_METHOD(CalculateA0);
  static NAN_METHOD(CalculateA1);
  static NAN_METHOD(GetResult);
  static NAN_METHOD(GetError);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif
