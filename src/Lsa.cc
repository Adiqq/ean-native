#include "Lsa.h"
#include <cmath>

Nan::Persistent<v8::FunctionTemplate> Lsa::constructor;

NAN_MODULE_INIT(Lsa::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Lsa::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Lsa").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "addPoint", AddPoint);
  Nan::SetPrototypeMethod(ctor, "calculateA0", CalculateA0);
  Nan::SetPrototypeMethod(ctor, "calculateA1", CalculateA1);
  Nan::SetPrototypeMethod(ctor, "getError", GetError);

  target->Set(Nan::New("Lsa").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Lsa::New) {
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("Lsa::New - called without new keyword").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  Lsa* lsa = new Lsa();
  lsa->Wrap(info.Holder());

  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Lsa::AddPoint) {
  // unwrap this Lsa
  Lsa * self = Nan::ObjectWrap::Unwrap<Lsa>(info.This());

  if (!Nan::New(Point::constructor)->HasInstance(info[0])) {
    return Nan::ThrowError(Nan::New("Lsa::Add - expected argument to be instance of Point").ToLocalChecked());
  }
  // unwrap the Lsa passed as argument
  Point * point = Nan::ObjectWrap::Unwrap<Point>(info[0]->ToObject());
  self->points.push_back(point);
  info.GetReturnValue().SetNull();
}

NAN_METHOD(Lsa::CalculateA0) {
  // unwrap this Lsa
  Lsa * self = Nan::ObjectWrap::Unwrap<Lsa>(info.This());

  int count = self->points.size();
  double x_square_sum = 0.0;
  double y_sum = 0.0;
  double x_y_sum = 0.0;
  double x_sum = 0.0;
  for(Point *point : self->points){
    x_square_sum += pow(point->x , 2);
    y_sum += point->y;
    x_y_sum += point->x * point->y;
    x_sum += point->x;
  }
  double a0 = (x_square_sum*y_sum - x_y_sum * x_sum) / (count * x_square_sum - pow(x_sum , 2));
  info.GetReturnValue().Set(a0);
}

NAN_METHOD(Lsa::CalculateA1) {
  // unwrap this Lsa
  Lsa * self = Nan::ObjectWrap::Unwrap<Lsa>(info.This());

  int count = self->points.size();
  double x_square_sum = 0.0;
  double y_sum = 0.0;
  double x_y_sum = 0.0;
  double x_sum = 0.0;
  for(Point *point : self->points){
    x_square_sum += pow(point->x , 2);
    y_sum += point->y;
    x_y_sum += point->x * point->y;
    x_sum += point->x;
  }
  double a1 = (count * x_y_sum - x_sum * y_sum) / (count * x_square_sum - pow(x_sum , 2));
  info.GetReturnValue().Set(a1);
}

NAN_METHOD(Lsa::GetError) {
  // unwrap this Lsa
  Lsa * self = Nan::ObjectWrap::Unwrap<Lsa>(info.This());

  int count = self->points.size();
  double x_square_sum = 0.0;
  double y_sum = 0.0;
  double x_y_sum = 0.0;
  double x_sum = 0.0;
  for(Point *point : self->points){
    x_square_sum += pow(point->x , 2);
    y_sum += point->y;
    x_y_sum += point->x * point->y;
    x_sum += point->x;
  }
  double a0 = (x_square_sum*y_sum - x_y_sum * x_sum) / (count * x_square_sum - pow(x_sum , 2));
  double a1 = (count * x_y_sum - x_sum * y_sum) / (count * x_square_sum - pow(x_sum , 2));

  double error = 0.0;
  for(auto i = 0; i < count; i++){
    Point *point = self->points[i];
    error += pow(point->y - (a1*point->x + a0), 2);
  }

  info.GetReturnValue().Set(error);
}

