#include "handler.h"

/* Declarations */
static void cp_handler_real_prepare(CpHandler* self, CpPlot* plot);
static void cp_handler_real_commit(CpHandler* self, CpPlot* plot);

static void cp_handler_finalize(GObject* obj);
static void cp_handler_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_handler_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	DUMMY_PROP,
};

static gpointer cp_handler_parent_class = NULL;

/* Special functions */

static void cp_handler_class_init (CpHandlerClass* klass)
{
	cp_handler_parent_class = g_type_class_peek_parent(klass);
	CP_HANDLER_CLASS (klass)->prepare = cp_handler_real_prepare;
	CP_HANDLER_CLASS (klass)->commit = cp_handler_real_commit;
	G_OBJECT_CLASS (klass)->get_property = cp_handler_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_handler_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_handler_finalize;
}

static void cp_handler_instance_init(CpHandler* self)
{
}

static void cp_handler_finalize(GObject* obj)
{
	G_OBJECT_CLASS(cp_handler_parent_class)->finalize(obj);
}

GType cp_handler_get_type (void)
{
	static GType cp_handler_type_id = 0;
	
	if(!cp_handler_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpHandlerClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_handler_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpHandler),
			0,
			(GInstanceInitFunc) cp_handler_instance_init,
			NULL
		};
		
		cp_handler_type_id = g_type_register_static(
			G_TYPE_OBJECT, "CpHandler", &g_define_type_info, G_TYPE_FLAG_ABSTRACT
		);
	}
	
	return cp_handler_type_id;
}

static void cp_handler_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	switch(property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_handler_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	switch(property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

void cp_handler_prepare(CpHandler* self, CpPlot* plot)
{
	CP_HANDLER_GET_CLASS(self)->prepare(self, plot);
}

void cp_handler_real_prepare(CpHandler* self, CpPlot* plot)
{
	
}

void cp_handler_commit(CpHandler* self, CpPlot* plot)
{
	CP_HANDLER_GET_CLASS(self)->commit(self, plot);
}

void cp_handler_real_commit(CpHandler* self, CpPlot* plot)
{
	if(plot->cr) cairo_destroy(plot->cr);
	if(self->surface) cairo_surface_destroy(self->surface);
}
