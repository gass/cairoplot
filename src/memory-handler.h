#ifndef __CP_MEMORY_HANDLER_H__
#define __CP_MEMORY_HANDLER_H__

#include "handler.h"

G_BEGIN_DECLS

#define CP_TYPE_MEMORY_HANDLER (cp_memory_handler_get_type ())
#define CP_MEMORY_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_MEMORY_HANDLER, CpMemoryHandler))
#define CP_MEMORY_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_MEMORY_HANDLER, CpMemoryHandlerClass))
#define CP_IS_MEMORY_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_MEMORY_HANDLER))
#define CP_IS_MEMORY_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_MEMORY_HANDLER))
#define CP_MEMORY_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_MEMORY_HANDLER, CpMemoryHandlerClass))

/**
 * Handler implementation that doesn't outputs anything. Useful for tests.
 */
typedef struct
{
	CpHandler parent_instance;
} CpMemoryHandler;

typedef struct
{
	CpHandlerClass parent_class;
} CpMemoryHandlerClass;

GType cp_memory_handler_get_type (void);
CpHandler* cp_memory_handler_new();

G_END_DECLS

#endif
