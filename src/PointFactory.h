#ifndef POINT_FACTORY_H
#define POINT_FACTORY_H

#include <nan.h>
#include <PointStrategy.h>
#include <string>

class PointFactory : public Nan::ObjectWrap {
public:

  PointStrategy *strategy;
  std::string pointType;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static NAN_METHOD(GeneratePoints);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

#endif