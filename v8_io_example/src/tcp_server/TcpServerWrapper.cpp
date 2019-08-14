#include "TcpServerWrapper.h"

extern Isolate* GetIsolate();
v8::Persistent<v8::Function> r_call;
// Extracts a C string from a V8 Utf8Value.
extern char* ToCString(const v8::String::Utf8Value& value);

void runCallBack(char* buf) {
    if(!r_call.IsEmpty()) {
        v8::Local<v8::Function> func = v8::Local<v8::Function>::New(GetIsolate(), r_call);
        if (!func.IsEmpty()) {
            v8::Local<v8::Value> argv[1];
            argv[0] = String::NewFromUtf8(GetIsolate(), buf, NewStringType::kNormal)
                            .ToLocalChecked();
			Local<Context> context = GetIsolate()->GetCurrentContext();
            MaybeLocal<Value> js_result = func->Call(context, context->Global(), 1, argv);
        }
  	}
}

void start(const FunctionCallbackInfo<Value>& args) {
	v8::Isolate* isolate = args.GetIsolate();
    if (args[1]->IsFunction()) {
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1]);
        v8::Function * ptr = *func;
        r_call.Reset(isolate, func);
    }
	v8::String::Utf8Value str(GetIsolate(), args[0]);  
	const char* cstr = ToCString(str); 
	if(strcmp("IO_BLOKING", cstr) == 0) {
		TcpServer::start(IO_BLOKING);
	} else if (strcmp("IO_NON_BLOKING", cstr) == 0) {
		TcpServer::start(IO_NON_BLOKING);
	} else if (strcmp("IO_MUTIPLEXING", cstr) == 0) {
		TcpServer::start(IO_MUTIPLEXING);
	} else {
		fprintf(stderr,"Server mode %s is not support.\n", cstr);
	}
	
}

Local<Object> WrapTcpServerObject(TcpServer *t) {

	EscapableHandleScope handle_scope(GetIsolate());

	Local<ObjectTemplate> class_t;
	Local<ObjectTemplate> raw_t = ObjectTemplate::New(GetIsolate());
        raw_t->SetInternalFieldCount(1);
        raw_t->Set(
		v8::String::NewFromUtf8(GetIsolate(), "start", v8::NewStringType::kNormal).ToLocalChecked(),
		v8::FunctionTemplate::New(GetIsolate(), start));
	class_t = Local<ObjectTemplate>::New(GetIsolate(),raw_t);
        //create instance
        Local<Object> result = class_t->NewInstance(GetIsolate()->GetCurrentContext()).ToLocalChecked();
	//create wrapper
        Local<External> ptr = External::New(GetIsolate(),t);
	result->SetInternalField(0,ptr);
	return handle_scope.Escape(result);
}
