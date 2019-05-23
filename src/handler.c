/*
 * handler.c
 * Handling "hello" and "ping" message.
 *
 * Written by Be-cricke on 6/17/2018
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib-object.h>

#include <thrift/c_glib/thrift.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol_factory.h>
#include <thrift/c_glib/protocol/thrift_protocol_factory.h>
#include <thrift/c_glib/server/thrift_server.h>
#include <thrift/c_glib/server/thrift_simple_server.h>
#include <thrift/c_glib/transport/thrift_buffered_transport_factory.h>
#include <thrift/c_glib/transport/thrift_server_socket.h>
#include <thrift/c_glib/transport/thrift_server_transport.h>

#include "gen-c_glib/sample_basic.h"
#include "gen-c_glib/sample_sample_types.h"
#include "handler.h"

GQuark
g_sample_error_quark (void)
{
  return g_quark_from_static_string ("g-sample-error-quark");
}

/* ------------------------------------------------------------------------------------- */
/*                 The implementation of SampleBasicimplHandler follows.                  */
/* -----------------------------  API Handlers (START)---------------------------------- */

G_DEFINE_TYPE (SampleBasicimplHandler,
               sample_basicimpl_handler,
               SAMPLE_TYPE_BASIC_HANDLER)

/* Each of a handler's methods accepts at least two parameters: As
   pointer to the service-interface implementation (the handler object
   itself) and a handle to a GError structure to receive information
   about any error that occurs.

   On success, a handler method returns TRUE. A return value of FALSE
   indicates an error occurred and the error parameter has been
   set. (Methods should not return FALSE without first setting the
   error parameter.) */

/**
 *
 * A sample implementation.
 * "Hello" api.
 * 
 */
static gboolean
sample_basicimpl_handler_hello(sampleBasicIf * iface, gchar ** _return, const gchar * arg, GError ** error)
{
  THRIFT_UNUSED_VAR (iface);
  THRIFT_UNUSED_VAR (error);

   
  GString *retValue;
  retValue = g_string_new( NULL );
  g_string_printf( retValue ,"Server received: %s \n" , arg );
  puts( retValue->str );
  
  *_return = retValue->str;
  
  return TRUE;
}



/**
 *
 * Confirm reachability.
 *
 */
static gboolean 
sample_basicimpl_handler_ping (sampleBasicIf * iface, GError ** error)
{
  THRIFT_UNUSED_VAR (iface);
  THRIFT_UNUSED_VAR (error);
  g_return_val_if_fail (SAMPLE_IS_BASIC_HANDLER (iface), FALSE);

  return TRUE;

}


/*------------------------------  API Handlers (END)-----------------------------------*/


/* SAMPLE basicimpl Handler's instance finalizer (destructor) */
static void
sample_basicimpl_handler_finalize (GObject *object)
{
  SampleBasicimplHandler *self =
    SAMPLE_BASICIMPL_HANDLER (object);

  /* Free our calculation-log hash table */
  g_hash_table_unref (self->log);
  self->log = NULL;

  /* Chain up to the parent class */
  G_OBJECT_CLASS (sample_basicimpl_handler_parent_class)->
    finalize (object);
}

/* SampleBasicimplHandler's instance initializer (constructor) */
static void
sample_basicimpl_handler_init (SampleBasicimplHandler *self)
{
    /* Create our calculation-log hash table */
  self->log = g_hash_table_new_full (g_int_hash,
                                     g_int_equal,
                                     g_free,
                                     g_object_unref);
}

/* SampleBasicimplHandler's class initializer */
static void
sample_basicimpl_handler_class_init (SampleBasicimplHandlerClass *klass)
{
  
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  sampleBasicHandlerClass *sample_basic_handler_class =
    SAMPLE_BASIC_HANDLER_CLASS (klass);

  /* Register our destructor */
  gobject_class->finalize = sample_basicimpl_handler_finalize;

  /* Register our implementations of CalculatorHandler's methods */
  sample_basic_handler_class->hello =
    sample_basicimpl_handler_hello;
  sample_basic_handler_class->ping = 
    sample_basicimpl_handler_ping;

}
