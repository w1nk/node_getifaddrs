// Copyright (C) 2010 Lee Smith <notwink@gmail.com>

#include "getifaddrs.h"

#include <cstring>

using namespace v8;
using namespace node;

extern "C"
void init( Handle<Object> target ) {
  HandleScope scope;
  getifaddrs_v8::Initialize( target );
}

namespace getifaddrs_v8 {

void Initialize( Handle<Object> target ) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(interfaces);

  target->Set( String::NewSymbol( "interfaces" ), t->GetFunction() );
}

  Handle<Value> interfaces( const Arguments &args ) {
    HandleScope scope;
    
    struct ifaddrs *list;
    if(getifaddrs(&list) < 0)
      {
	return Undefined();
      }

    struct ifaddrs *cur;
    int ifcount = 0;
    for(cur = list; cur != NULL; cur = cur->ifa_next)
      {
	if(cur->ifa_addr->sa_family != AF_INET)
	  continue;
	ifcount++;
      }

    Local<Array> interfaces = Array::New(ifcount);
    ifcount = 0;
    for(cur = list; cur != NULL; cur = cur->ifa_next)
      {
        if(cur->ifa_addr->sa_family != AF_INET)
          continue;

	Local<Array> interface = Array::New(2);
	struct sockaddr_in *addrStruct = (struct sockaddr_in *)cur->ifa_addr;
	interface->Set(String::New(cur->ifa_name), String::New(inet_ntoa(addrStruct->sin_addr)));
	interfaces->Set(ifcount++, interface);
      }
    
    freeifaddrs(list);
    return interfaces;
    //return Undefined();
  }
}
