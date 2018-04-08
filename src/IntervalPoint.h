#ifndef INTERVAL_POINT_H
#define INTERVAL_POINT_H

#include <nan.h>
#include <iostream>
#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>

class IntervalPoint : public Nan::ObjectWrap {
public:
  boost::numeric::interval<double> x;
  boost::numeric::interval<double> y;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static NAN_GETTER(HandleGetters);
  static NAN_SETTER(HandleSetters);

  static NAN_METHOD(GetLowerX);
  static NAN_METHOD(GetUpperX);

  static NAN_METHOD(GetLowerY);
  static NAN_METHOD(GetUpperY);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

#endif