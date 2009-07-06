#include "plot.h"

/* Declarations */
static void cp_plot_real_render(CpPlot* self);
static void cp_plot_finalize(GObject* obj);
static void cp_plot_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_plot_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* aux */
static void set_border_color(CpPlot* self, CpColor* ptr)
{
	*self->border_color = *ptr;
}

/* Private */
enum
{
	DUMMY_PROP,
	WIDTH_PROP,
	HEIGHT_PROP,
	BORDER_COLOR_PROP,
};

enum
{
	PRE_RENDER_SIGNAL,
	POS_RENDER_SIGNAL,
	LAST_SIGNAL
};

#define DEFAULT_HEIGHT 400
#define DEFAULT_WIDTH 400

static gpointer cp_plot_parent_class = NULL;
static guint plot_signals[LAST_SIGNAL] = {0};

/* Special functions */

static void cp_plot_class_init (CpPlotClass* klass)
{
	cp_plot_parent_class = g_type_class_peek_parent(klass);
	CP_PLOT_CLASS (klass)->render = cp_plot_real_render;
	G_OBJECT_CLASS (klass)->get_property = cp_plot_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_plot_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_plot_finalize;
	
	/* properties */
	GParamSpec* pspec = g_param_spec_int("width", "width", "width", 0, G_MAXINT, DEFAULT_WIDTH,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), WIDTH_PROP, pspec);
	
	pspec = g_param_spec_int ("height", "height", "height", 0, G_MAXINT, DEFAULT_HEIGHT,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), HEIGHT_PROP, pspec);
	
	pspec = g_param_spec_boxed ("border-color", "border-color", "border-color", CP_TYPE_COLOR,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), BORDER_COLOR_PROP, pspec);
	
	/* signals */
	plot_signals[PRE_RENDER_SIGNAL] = g_signal_new("pre-render", CP_TYPE_PLOT,
		G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	plot_signals[POS_RENDER_SIGNAL] = g_signal_new("pos-render", CP_TYPE_PLOT,
		G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}

static void cp_plot_instance_init(CpPlot * self)
{
	self->border_color = cp_color_new_rgba(0, 0, 0, 1);
	self->width = DEFAULT_WIDTH;
	self->height = DEFAULT_HEIGHT;
}

static void cp_plot_finalize (GObject* obj)
{
	CpPlot* self = CP_PLOT(obj);
	cp_color_free(self->border_color);
	G_OBJECT_CLASS(cp_plot_parent_class)->finalize(obj);
}

GType cp_plot_get_type (void)
{
	static GType cp_plot_type_id = 0;
	
	if(!cp_plot_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpPlotClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_plot_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpPlot),
			0,
			(GInstanceInitFunc) cp_plot_instance_init,
			NULL
		};
		
		cp_plot_type_id = g_type_register_static
		(
			G_TYPE_OBJECT, "CpPlot", &g_define_type_info, 0
		);
	}
	
	return cp_plot_type_id;
}

static void cp_plot_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	CpPlot* self = CP_PLOT(object);
	
	switch(property_id)
	{
		case WIDTH_PROP:
			g_value_set_int(value, self->width);
			break;
			
		case HEIGHT_PROP:
			g_value_set_int(value, self->height);
			break;
			
		case BORDER_COLOR_PROP:
			g_value_set_boxed(value, self->border_color);
			break;
		
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_plot_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	CpPlot* self = CP_PLOT(object);
	
	switch(property_id)
	{
		case WIDTH_PROP:
			self->width = g_value_get_int(value);
			break;
			
		case HEIGHT_PROP:
			self->height = g_value_get_int(value);
			break;
			
		case BORDER_COLOR_PROP:
			set_border_color(self, g_value_get_boxed(value));
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

CpPlot* cp_plot_new()
{
	return CP_PLOT(g_object_new(CP_TYPE_PLOT, NULL));
}

void cp_plot_render (CpPlot* self)
{
	g_signal_emit(self, plot_signals[PRE_RENDER_SIGNAL], 0);
	CP_PLOT_GET_CLASS(self)->render(self);
	g_signal_emit(self, plot_signals[POS_RENDER_SIGNAL], 0);
}

void cp_plot_real_render(CpPlot* self)
{
	g_debug("Plot rendered with size == (%d, %d)!", self->width, self->height);
}
