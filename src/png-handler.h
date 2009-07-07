#ifndef __CP_PNG_HANDLER_H__
#define __CP_PNG_HANDLER_H__

#include "handler.h"

G_BEGIN_DECLS

#define CP_TYPE_PNG_HANDLER (cp_png_handler_get_type ())
#define CP_PNG_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_PNG_HANDLER, CpPNGHandler))
#define CP_PNG_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_PNG_HANDLER, CpPNGHandlerClass))
#define CP_IS_PNG_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_PNG_HANDLER))
#define CP_IS_PNG_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_PNG_HANDLER))
#define CP_PNG_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_PNG_HANDLER, CpPNGHandlerClass))

/**
 * Handler implementation for PNG images.
 */
typedef struct
{
	CpHandler parent_instance;
	gchar* filename;
} CpPNGHandler;

typedef struct
{
	CpHandlerClass parent_class;
} CpPNGHandlerClass;

GType cp_png_handler_get_type (void);
CpHandler* cp_png_handler_new(const gchar* filename);

G_END_DECLS

#endif
