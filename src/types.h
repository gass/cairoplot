#ifndef __CP_TYPES_H__
#define __CP_TYPES_H__

/* handle cyclic dependencies between CpPlot and CpHandler */

G_BEGIN_DECLS

typedef struct
{
	GObject parent_instance;
} CpHandler;

typedef struct
{
	GObject parent_instance;
	cairo_t* cr;
	CpColor* border_color;
	CpHandler* handler;
	gint width, height;
} CpPlot;

typedef struct
{
	GObjectClass parent_class;
	void (*render) (CpPlot* self);
	void (*render_bounding_box) (CpPlot* self);
} CpPlotClass;

typedef struct
{
	GObjectClass parent_class;
	void (*prepare) (CpHandler* self, CpPlot* plot);
	void (*commit) (CpHandler* self, CpPlot* plot);
} CpHandlerClass;

G_END_DECLS

#endif
