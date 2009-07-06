#ifndef __CP_PLOT_H__
#define __CP_PLOT_H__

#include <glib.h>
#include <glib-object.h>
#include "color.h"

G_BEGIN_DECLS

#define CP_TYPE_PLOT (cp_plot_get_type ())
#define CP_PLOT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_PLOT, CpPlot))
#define CP_PLOT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_PLOT, CpPlotClass))
#define CP_IS_PLOT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_PLOT))
#define CP_IS_PLOT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_PLOT))
#define CP_PLOT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_PLOT, CpPlotClass))

typedef struct
{
	GObject parent_instance;	
	CpColor* border_color;
	int width, height;
} CpPlot;

typedef struct
{
	GObjectClass parent_class;
	void (*render) (CpPlot* self);
} CpPlotClass;

GType cp_plot_get_type (void);
void cp_plot_render(CpPlot* self);
CpPlot* cp_plot_new();

G_END_DECLS

#endif
