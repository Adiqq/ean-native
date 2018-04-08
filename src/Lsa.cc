#include "Lsa.h"

Nan::Persistent<v8::FunctionTemplate> Lsa::constructor;

NAN_MODULE_INIT(Lsa::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Lsa::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Lsa").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "addPoint", AddPoint);
  Nan::SetPrototypeMethod(ctor, "calculateA0", CalculateA0);
  Nan::SetPrototypeMethod(ctor, "calculateA1", CalculateA1);

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

  double count = self->points.size();
  v8::Local<v8::Number> countLocal = Nan::New(count);
  info.GetReturnValue().Set(countLocal);
}

NAN_METHOD(Lsa::CalculateA1) {
  // unwrap this Lsa
  Lsa * self = Nan::ObjectWrap::Unwrap<Lsa>(info.This());

  double count = self->points.size();
  v8::Local<v8::Number> countLocal = Nan::New(count);
  info.GetReturnValue().Set(countLocal);
}
