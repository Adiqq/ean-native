#include "IntervalPoint.h"

Nan::Persistent<v8::FunctionTemplate> IntervalPoint::constructor;

NAN_MODULE_INIT(IntervalPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(IntervalPoint::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("IntervalPoint").ToLocalChecked());

  // link our getters and setter to the object property
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), IntervalPoint::HandleGetters, IntervalPoint::HandleSetters);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), IntervalPoint::HandleGetters, IntervalPoint::HandleSetters);

  Nan::SetPrototypeMethod(ctor, "getLowerX", GetLowerX);
  Nan::SetPrototypeMethod(ctor, "getUpperX", GetUpperX);
  Nan::SetPrototypeMethod(ctor, "getLowerY", GetLowerY);
  Nan::SetPrototypeMethod(ctor, "getUpperY", GetUpperY);
  target->Set(Nan::New("IntervalPoint").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(IntervalPoint::New) {
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("IntervalPoint::New - called without new keyword").ToLocalChecked());
  }

  // expect exactly 2 arguments
  if(info.Length() != 2) {
    return Nan::ThrowError(Nan::New("IntervalPoint::New - expected arguments x, y").ToLocalChecked());
  }

  // expect arguments to be numbers
  if(!info[0]->IsNumber() || !info[1]->IsNumber()) {
    return Nan::ThrowError(Nan::New("IntervalPoint::New - expected arguments to be numbers").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  IntervalPoint* intervalPoint = new IntervalPoint();
  intervalPoint->Wrap(info.Holder());

  // initialize it's values
  intervalPoint->x = info[0]->NumberValue();
  intervalPoint->y = info[1]->NumberValue();

  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(IntervalPoint::HandleGetters) {
  IntervalPoint* self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "x") {
    info.GetReturnValue().Set(self->x.lower());
  } else if (propertyName == "y") {
    info.GetReturnValue().Set(self->y.lower());
  } else {
    info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_SETTER(IntervalPoint::HandleSetters) {
  IntervalPoint* self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());

  if(!value->IsNumber()) {
    return Nan::ThrowError(Nan::New("expected value to be a number").ToLocalChecked());
  }

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "x") {
    self->x = value->NumberValue();
  } else if (propertyName == "y") {
    self->y = value->NumberValue();
  }
}

NAN_METHOD(IntervalPoint::GetLowerX) {
  IntervalPoint * self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());
  info.GetReturnValue().Set(self->x.lower());
}

NAN_METHOD(IntervalPoint::GetUpperX) {
  IntervalPoint * self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());
  info.GetReturnValue().Set(self->x.upper());
}

NAN_METHOD(IntervalPoint::GetLowerY) {
  IntervalPoint * self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());
  info.GetReturnValue().Set(self->y.lower());
}

NAN_METHOD(IntervalPoint::GetUpperY) {
  IntervalPoint * self = Nan::ObjectWrap::Unwrap<IntervalPoint>(info.This());
  info.GetReturnValue().Set(self->y.upper());
}