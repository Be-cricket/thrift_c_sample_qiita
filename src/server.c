/*
 * This file is the main program.
 * 
 */

#include <glib-object.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#define DEBUG_WRITE_LOG(s) printf( s );puts(""); 


/* ---------------------------------------------------------------- */


/* Our server object, declared globally so it is accessible within the
   SIGINT signal handler */
ThriftServer *server = NULL;

/* A flag that indicates whether the server was interrupted with
   SIGINT (i.e. Ctrl-C) so we can tell whether its termination was
   abnormal */
gboolean sigint_received = FALSE;

/* Handle SIGINT ("Ctrl-C") signals by gracefully stopping the
   server */
static void
sigint_handler (int signal_number)
{
  THRIFT_UNUSED_VAR (signal_number);

  /* Take note we were called */
  sigint_received = TRUE;

   
  /* Shut down the server gracefully */
  if (server != NULL)
    thrift_server_stop (server);
}


/**
 * Main function.
 *
 */
int main ( void ){

  sampleBasicHandler *handler;
  sampleBasicProcessor *processor;
    
  ThriftServerTransport *server_transport;
  ThriftTransportFactory *transport_factory;
  ThriftProtocolFactory *protocol_factory;

  struct sigaction sigint_action;

  GError *error = NULL;
  int exit_status = 0;
   
#if (!GLIB_CHECK_VERSION (2, 36, 0))
  g_type_init ();
#endif

 
  /* Create an instance of our handler, which provides the service's
     methods' implementation */

  handler = 
     g_object_new (SAMPLE_TYPE_BASIC_HANDLER, 
                   NULL); 
 
  
  /* Create an instance of the service's processor, automatically
     generated by the Thrift compiler, which parses incoming messages
     and dispatches them to the appropriate method in the handler */
  processor =
    g_object_new (SAMPLE_TYPE_BASIC_PROCESSOR,
                  "handler", handler,
                  NULL);

  /* Create our server socket, which binds to the specified port and
     listens for client connections */
  server_transport =
    g_object_new (THRIFT_TYPE_SERVER_SOCKET,
                  "port", 9090,
                  NULL);

  /* Create our transport factory, used by the server to wrap "raw"
     incoming connections from the client (in this case with a
     ThriftBufferedTransport to improve performance) */
  transport_factory =
    g_object_new (THRIFT_TYPE_BUFFERED_TRANSPORT_FACTORY,
                  NULL);

  /* Create our protocol factory, which determines which wire protocol
     the server will use (in this case, Thrift's binary protocol) */
  protocol_factory =
    g_object_new (THRIFT_TYPE_BINARY_PROTOCOL_FACTORY,
                  NULL);

  /* Create the server itself */
  server =
    g_object_new (THRIFT_TYPE_SIMPLE_SERVER,
                  "processor",                processor,
                  "server_transport",         server_transport,
                  "input_transport_factory",  transport_factory,
                  "output_transport_factory", transport_factory,
                  "input_protocol_factory",   protocol_factory,
                  "output_protocol_factory",  protocol_factory,
                  NULL);

  /* Install our SIGINT handler, which handles Ctrl-C being pressed by
     stopping the server gracefully (not strictly necessary, but a
     nice touch) */
  memset (&sigint_action, 0, sizeof (sigint_action));
  sigint_action.sa_handler = sigint_handler;
  sigint_action.sa_flags = SA_RESETHAND;
  sigaction (SIGINT, &sigint_action, NULL);

  /* Start the server, which will run until its stop method is invoked
     (from within the SIGINT handler, in this case) */

  DEBUG_WRITE_LOG("Starting the server...");

  thrift_server_serve (server, &error);

  /* If the server stopped for any reason other than having been
     interrupted by the user, report the error */
  if (!sigint_received) {
    g_message ("thrift_server_serve: %s",
               error != NULL ? error->message : "(null)");
    g_clear_error (&error);
  }

  DEBUG_WRITE_LOG("done.");
  
  g_object_unref (server);
  g_object_unref (transport_factory);
  g_object_unref (protocol_factory);
  g_object_unref (server_transport);

  g_object_unref (processor);
  g_object_unref (handler);

  return exit_status;

}

