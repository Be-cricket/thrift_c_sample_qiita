#!/usr/local/bin/thrift --java --c_glib --py

namespace c_glib  sample
namespace py sample


#
# hello              :Sample implementation
service Basic
{
     void ping(),
     string hello(1:string arg),
}
