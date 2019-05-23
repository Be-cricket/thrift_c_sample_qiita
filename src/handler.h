/*
 * handler.h
 * Handling the basic operation.
 *
 * Written by Be-cricket on 6/17/2018
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <thrift/c_glib/processor/thrift_dispatch_processor.h>

/* for glib gerror */
GQuark
g_sample_error_quark (void);

/** for glib error proc */
#define G_SAMPLE_ERROR g_sample_error_quark() 




/* --------------------------------------------------------------------- */
/*         Following: The declareration for GLib                         */
/* --------------------------------------------------------------------- */
G_BEGIN_DECLS

/* In the C (GLib) implementation of Thrift, the actual work done by a
   server---that is, the code that runs when a client invokes a
   service method---is defined in a separate "handler" class that
   implements the service interface. Here we define the
   SampleBasicImplHandler class

   If you're new to GObject, try not to be intimidated by the quantity
   of code here---much of it is boilerplate and can mostly be
   copied-and-pasted from existing work. For more information refer to
   the GObject Reference Manual, available online at
   https://developer.gnome.org/gobject/. */

#define TYPE_SAMPLE_BASICIMPL_HANDLER \
  (sample_basicimpl_handler_get_type ())

#define SAMPLE_BASICIMPL_HANDLER(obj)                                \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj),                                   \
                               TYPE_SAMPLE_BASICIMPL_HANDLER,        \
                               SampleBasicimplHandler))
#define SAMPLE_BASICIMPL_HANDLER_CLASS(c)                    \
  (G_TYPE_CHECK_CLASS_CAST ((c),                                \
                            TYPE_SAMPLE_BASICIMPL_HANDLER,   \
                            SampleBasicimplHandlerClass))
#define IS_SAMPLE_BASICIMPL_HANDLER(obj)                             \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),                                   \
                               TYPE_SAMPLE_BASICIMPL_HANDLER))
#define IS_SAMPLE_BASICIMPL_HANDLER_CLASS(c)                 \
  (G_TYPE_CHECK_CLASS_TYPE ((c),                                \
                            TYPE_SAMPLE_BASICIMPL_HANDLER))
#define SAMPLE_BASICIMPL_HANDLER_GET_CLASS(obj)              \
  (G_TYPE_INSTANCE_GET_CLASS ((obj),                            \
                              TYPE_SAMPLE_BASICIMPL_HANDLER, \
                              SampleBasicimplHandlerClass))

struct _SampleBasicimplHandler {
  sampleBasicHandler parent_instance;

  /* private */
  GHashTable *log;
};
typedef struct _SampleBasicimplHandler SampleBasicimplHandler;

struct _SampleBasicimplHandlerClass {
  sampleBasicHandlerClass parent_class;
};
typedef struct _SampleBasicimplHandlerClass SampleBasicimplHandlerClass;

GType sample_basicimpl_handler_get_type (void);

G_END_DECLS


#endif /* HANDLER_H */
