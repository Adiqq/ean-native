#include "LsaInterval.h"
#include <cmath>

Nan::Persistent<v8::FunctionTemplate> LsaInterval::constructor;

NAN_MODULE_INIT(LsaInterval::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(LsaInterval::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("LsaInterval").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "addPoint", AddPoint);
  Nan::SetPrototypeMethod(ctor, "calculateA0", CalculateA0);
  Nan::SetPrototypeMethod(ctor, "calculateA1", CalculateA1);

  target->Set(Nan::New("LsaInterval").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(LsaInterval::New) {
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("LsaInterval::New - called without new keyword").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  LsaInterval* lsa = new LsaInterval();
  lsa->Wrap(info.Holder());

  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(LsaInterval::AddPoint) {
  // unwrap this LsaInterval
  LsaInterval * self = Nan::ObjectWrap::Unwrap<LsaInterval>(info.This());

  if (!Nan::New(IntervalPoint::constructor)->HasInstance(info[0])) {
    return Nan::ThrowError(Nan::New("LsaInterval::Add - expected argument to be instance of IntervalPoint").ToLocalChecked());
  }
  // unwrap the LsaInterval passed as argument
  IntervalPoint * point = Nan::ObjectWrap::Unwrap<IntervalPoint>(info[0]->ToObject());
  self->points.push_back(point);
  info.GetReturnValue().SetNull();
}

NAN_METHOD(LsaInterval::CalculateA0) {
  // unwrap this LsaInterval
  LsaInterval * self = Nan::ObjectWrap::Unwrap<LsaInterval>(info.This());

  double count = self->points.size();
  boost::numeric::interval<double> x_square_sum = 0.0;
  boost::numeric::interval<double> y_sum = 0.0;
  boost::numeric::interval<double> x_y_sum = 0.0;
  boost::numeric::interval<double> x_sum = 0.0;
  for(IntervalPoint *point : self->points){
    x_square_sum += pow(point->x , 2);
    y_sum += point->y;
    x_y_sum += point->x * point->y;
    x_sum += point->x;
  }
  boost::numeric::interval<double> a0 = (x_square_sum*y_sum - x_y_sum * x_sum) / (count * x_square_sum - pow(x_sum , 2));
  const int argc = 2;
  v8::Isolate *isolate = info.GetIsolate();
  v8::Handle<v8::Array> array = v8::Array::New(isolate, argc);
  v8::Local<v8::Number> lower = Nan::New(a0.lower());
  v8::Local<v8::Number> upper = Nan::New(a0.upper());
  array->Set(0, lower);
  array->Set(1, upper);
  info.GetReturnValue().Set(array);
}

NAN_METHOD(LsaInterval::CalculateA1) {
  // unwrap this LsaInterval
  LsaInterval * self = Nan::ObjectWrap::Unwrap<LsaInterval>(info.This());

  double count = self->points.size();
  boost::numeric::interval<double> x_square_sum = 0.0;
  boost::numeric::interval<double> y_sum = 0.0;
  boost::numeric::interval<double> x_y_sum = 0.0;
  boost::numeric::interval<double> x_sum = 0.0;
  for(IntervalPoint *point : self->points){
    x_square_sum += pow(point->x , 2);
    y_sum += point->y;
    x_y_sum += point->x * point->y;
    x_sum += point->x;
  }
  boost::numeric::interval<double> a1 = (count * x_y_sum - x_sum * y_sum) / (count * x_square_sum - pow(x_sum , 2));
  const int argc = 2;
  v8::Isolate *isolate = info.GetIsolate();
  v8::Handle<v8::Array> array = v8::Array::New(isolate, argc);
  v8::Local<v8::Number> lower = Nan::New(a1.lower());
  v8::Local<v8::Number> upper = Nan::New(a1.upper());
  array->Set(0, lower);
  array->Set(1, upper);
  info.GetReturnValue().Set(array);
}
