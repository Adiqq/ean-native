#include "PointFactory.h"
#include "RandomPointStrategy.h"

Nan::Persistent<v8::FunctionTemplate> PointFactory::constructor;

NAN_MODULE_INIT(PointFactory::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(PointFactory::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("PointFactory").ToLocalChecked());

    Nan::SetPrototypeMethod(ctor, "generatePoints", GeneratePoints);

  target->Set(Nan::New("PointFactory").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(PointFactory::New) {
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("PointFactory::New - called without new keyword").ToLocalChecked());
  }

  // expect exactly 2 arguments
  if(info.Length() != 1) {
    return Nan::ThrowError(Nan::New("PointFactory::New - expected arguments strategyType").ToLocalChecked());
  }

  // expect arguments to be numbers
  if(!info[0]->IsString()) {
    return Nan::ThrowError(Nan::New("PointFactory::New - expected arguments to be object").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  PointFactory* factory = new PointFactory();
  factory->Wrap(info.Holder());
  v8::String::Utf8Value param(info[0]->ToString());
  std::string strategyName = std::string(*param);
  // initialize it's values
  if(strategyName == "RPS"){
    factory->strategy = new RandomPointStrategy(); 
  }

  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(PointFactory::GeneratePoints) {
  // unwrap this Vector
  PointFactory * self = Nan::ObjectWrap::Unwrap<PointFactory>(info.This());

  if(info.Length() != 3) {
    return Nan::ThrowError(Nan::New("PointFactory::GeneratePoints - expected 3 arguments").ToLocalChecked());
  }
  // unwrap the Vector passed as argument
  Nan::Maybe<int32_t> n = Nan::To<int32_t>(info[0]);
  Nan::Maybe<double> min = Nan::To<double>(info[1]);
  Nan::Maybe<double> max = Nan::To<double>(info[2]);

  std::vector<Point*>  points = self->strategy->getPoints(n.FromJust(), min.FromJust(), max.FromJust());

  v8::Isolate *isolate = info.GetIsolate();
  v8::Handle<v8::Array> array = v8::Array::New(isolate, points.size());
  for(int i = 0; i < points.size(); i++){
    // get FunctionTemplate from persistent object
    v8::Local<v8::FunctionTemplate> tpl = Nan::New(Point::constructor);

    // get function from template
    v8::Local<v8::Function> cons = tpl->GetFunction();

    const int argc = 2;
    v8::Local<v8::Value> argv[argc] = {
      Nan::New(points[i]->x),
      Nan::New(points[i]->y)
    };
    // create new instance in the current context
    v8::MaybeLocal<v8::Object> instance = cons->NewInstance(
        isolate->GetCurrentContext(), argc, argv);

    // use as Local<Object>
    v8::Local<v8::Object> obj = instance.ToLocalChecked();
    array->Set(i, obj);
  }
  info.GetReturnValue().Set(array);
}