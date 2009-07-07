#ifndef __CP_TYPES_H__
#define __CP_TYPES_H__

#include "color.h"
#include "label.h"

/* handle cyclic dependencies between CpPlot and CpHandler */

G_BEGIN_DECLS

/**
 * A Handler is defined here as an object that provides the surface and cairo
 * context for the plot, making easy to reuse a plot for several output types.
 * Abstract.
 */
typedef struct
{
	GObject parent_instance;
	cairo_surface_t* surface;
} CpHandler;

/**
 * Holds common properties and methods of plots. Abstract.
 */
typedef struct
{
	GObject parent_instance;
	cairo_t* cr;
	CpHandler* handler;

	CpColor* border_color;
	CpColor* bg_color;
	
	gint v_labels_lenght;
	gchar** v_labels;
	gint h_labels_lenght;
	gchar** h_labels;
	
	gdouble line_width;
	gint width, height;
} CpPlot;

typedef struct
{
	GObjectClass parent_class;
	void (*render) (CpPlot* self);
	void (*render_bounding_box) (CpPlot* self);
	void (*render_background) (CpPlot* self);
} CpPlotClass;

typedef struct
{
	CpPlotClass parent_class;
	void (*prepare) (CpHandler* self, CpPlot* plot);
	void (*commit) (CpHandler* self, CpPlot* plot);
} CpHandlerClass;

G_END_DECLS

#endif
