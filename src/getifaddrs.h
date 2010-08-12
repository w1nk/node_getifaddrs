// Copyright (C) 2010 Lee Smith <notwink@gmail.com>

#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ifaddrs.h>
#include <v8.h>
#include <node.h>

namespace getifaddrs_v8 {
void Initialize( v8::Handle<v8::Object> target );
v8::Handle<v8::Value> interfaces( const v8::Arguments &args );
}

