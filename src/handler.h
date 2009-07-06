#ifndef __CP_HANDLER_H__
#define __CP_HANDLER_H__

#include "plot.h"
#include "types.h"

G_BEGIN_DECLS

#define CP_TYPE_HANDLER (cp_handler_get_type ())
#define CP_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_HANDLER, CpHandler))
#define CP_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_HANDLER, CpHandlerClass))
#define CP_IS_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_HANDLER))
#define CP_IS_HANDLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_HANDLER))
#define CP_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_HANDLER, CpHandlerClass))

GType cp_handler_get_type (void);
void cp_handler_prepare (CpHandler* self, CpPlot* plot);
void cp_handler_commit (CpHandler* self, CpPlot* plot);

G_END_DECLS

#endif
