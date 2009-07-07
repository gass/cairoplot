#include "memory-handler.h"

/* Declarations */
static void cp_memory_handler_real_prepare(CpHandler* self, CpPlot* plot);
static void cp_memory_handler_real_commit(CpHandler* self, CpPlot* plot);

static void cp_memory_handler_finalize(GObject* obj);
static void cp_memory_handler_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_memory_handler_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	DUMMY_PROP,
	FILENAME_PROP,
};

static CpHandlerClass* cp_memory_handler_parent_class = NULL;

/* Special functions */

static void cp_memory_handler_class_init (CpMemoryHandlerClass* klass)
{
	cp_memory_handler_parent_class = g_type_class_peek_parent(klass);
	CP_HANDLER_CLASS (klass)->prepare = cp_memory_handler_real_prepare;
	CP_HANDLER_CLASS (klass)->commit = cp_memory_handler_real_commit;
	G_OBJECT_CLASS (klass)->get_property = cp_memory_handler_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_memory_handler_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_memory_handler_finalize;
}

static void cp_memory_handler_instance_init(CpMemoryHandler* self)
{
}

static void cp_memory_handler_finalize(GObject* obj)
{	
	G_OBJECT_CLASS(cp_memory_handler_parent_class)->finalize(obj);
}

GType cp_memory_handler_get_type (void)
{
	static GType cp_memory_handler_type_id = 0;
	
	if(!cp_memory_handler_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpMemoryHandlerClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_memory_handler_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpMemoryHandler),
			0,
			(GInstanceInitFunc) cp_memory_handler_instance_init,
			NULL
		};
		
		cp_memory_handler_type_id = g_type_register_static(
			CP_TYPE_HANDLER, "CpMemoryHandler", &g_define_type_info, 0
		);
	}
	
	return cp_memory_handler_type_id;
}

static void cp_memory_handler_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	//CpMemoryHandler* self = CP_PNG_HANDLER(object);
	
	switch(property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_memory_handler_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	//CpMemoryHandler* self = CP_PNG_HANDLER(object);
	
	switch(property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

void cp_memory_handler_real_prepare(CpHandler* self, CpPlot* plot)
{
	self->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, plot->width, plot->height);
	plot->cr = cairo_create(self->surface);
	cp_memory_handler_parent_class->prepare(self, plot);
}

void cp_memory_handler_real_commit(CpHandler* self, CpPlot* plot)
{
	cp_memory_handler_parent_class->commit(self, plot);
}

CpHandler* cp_memory_handler_new()
{
	return CP_HANDLER(g_object_new(CP_TYPE_MEMORY_HANDLER, NULL));
}
