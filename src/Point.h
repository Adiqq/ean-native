#ifndef POINT_H
#define POINT_H

#include <nan.h>

class Point : public Nan::ObjectWrap {
public:
  double x;
  double y;
  
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static NAN_GETTER(HandleGetters);
  static NAN_SETTER(HandleSetters);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

#endif