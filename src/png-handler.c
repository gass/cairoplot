#include "png-handler.h"

/* Declarations */
static void cp_png_handler_real_prepare(CpHandler* self, CpPlot* plot);
static void cp_png_handler_real_commit(CpHandler* self, CpPlot* plot);

static void cp_png_handler_finalize(GObject* obj);
static void cp_png_handler_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_png_handler_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	DUMMY_PROP,
	FILENAME_PROP,
};

/* aux */

void set_filename(CpPNGHandler* self, gchar* filename)
{
	if(self->filename) g_free(self->filename);
	self->filename = filename;
}

static CpHandlerClass* cp_png_handler_parent_class = NULL;

/* Special functions */

static void cp_png_handler_class_init (CpPNGHandlerClass* klass)
{
	cp_png_handler_parent_class = g_type_class_peek_parent(klass);
	CP_HANDLER_CLASS (klass)->prepare = cp_png_handler_real_prepare;
	CP_HANDLER_CLASS (klass)->commit = cp_png_handler_real_commit;
	G_OBJECT_CLASS (klass)->get_property = cp_png_handler_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_png_handler_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_png_handler_finalize;
	
	/* properties */
	GParamSpec* pspec = g_param_spec_string("filename", "filename", "filename", NULL, 
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), FILENAME_PROP, pspec);
}

static void cp_png_handler_instance_init(CpPNGHandler* self)
{
}

static void cp_png_handler_finalize(GObject* obj)
{
	CpPNGHandler* self = CP_PNG_HANDLER(obj);
	if(self->filename) g_free(self->filename);
	
	G_OBJECT_CLASS(cp_png_handler_parent_class)->finalize(obj);
}

GType cp_png_handler_get_type (void)
{
	static GType cp_png_handler_type_id = 0;
	
	if(!cp_png_handler_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpPNGHandlerClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_png_handler_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpPNGHandler),
			0,
			(GInstanceInitFunc) cp_png_handler_instance_init,
			NULL
		};
		
		cp_png_handler_type_id = g_type_register_static(
			CP_TYPE_HANDLER, "CpPNGHandler", &g_define_type_info, 0
		);
	}
	
	return cp_png_handler_type_id;
}

static void cp_png_handler_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	CpPNGHandler* self = CP_PNG_HANDLER(object);
	
	switch(property_id)
	{
		case FILENAME_PROP:
			g_value_set_string(value, self->filename);
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_png_handler_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	CpPNGHandler* self = CP_PNG_HANDLER(object);
	
	switch(property_id)
	{
		case FILENAME_PROP:
			set_filename(self, g_value_dup_string(value));
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

void cp_png_handler_real_prepare(CpHandler* self, CpPlot* plot)
{
	self->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, plot->width, plot->height);
	plot->cr = cairo_create(self->surface);
	cp_png_handler_parent_class->prepare(self, plot);
}

void cp_png_handler_real_commit(CpHandler* self, CpPlot* plot)
{
	cairo_show_page(plot->cr);
	cairo_surface_write_to_png(self->surface, CP_PNG_HANDLER(self)->filename);
	cp_png_handler_parent_class->commit(self, plot);
}

CpHandler* cp_png_handler_new(const gchar* filename)
{
	return CP_HANDLER(g_object_new(CP_TYPE_PNG_HANDLER, "filename", filename, NULL));
}
