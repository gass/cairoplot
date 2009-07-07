#include "label.h"

static void cp_label_list_finalize(GObject* obj);
static void cp_label_list_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_label_list_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	DUMMY_PROP,
	COLOR_PROP,
	LIST_PROP,
	ANGLE_PROP,
	LIST_SIZE_PROP,
	FONT_SIZE_PROP
};

static gpointer cp_label_list_parent_class = NULL;

/* Special functions */

static void cp_label_list_class_init (CpLabelListClass* klass)
{
	cp_label_list_parent_class = g_type_class_peek_parent(klass);
	
	G_OBJECT_CLASS (klass)->get_property = cp_label_list_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_label_list_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_label_list_finalize;
	
	/* properties */
	GParamSpec* pspec = g_param_spec_object("color", "color", "color", CP_TYPE_LABEL_LIST,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), COLOR_PROP, pspec);
	
	pspec = g_param_spec_boxed("list", "list", "list", G_TYPE_STRV,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), LIST_PROP, pspec);
	
	pspec = g_param_spec_double("angle", "angle", "angle", 0, 360, 0,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), ANGLE_PROP, pspec);
	
	pspec = g_param_spec_uint("list-size", "list-size", "list-size", 0, G_MAXUINT, 0,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), LIST_SIZE_PROP, pspec);
	
	pspec = g_param_spec_uint("font-size", "font-size", "font-size", 0, G_MAXUINT, 0,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), FONT_SIZE_PROP, pspec);
}

static void cp_label_list_instance_init(CpLabelList* self)
{
}

static void cp_label_list_finalize(GObject* object)
{
	CpLabelList* self = CP_LABEL_LIST(object);
	
	if(self->color)
		cp_color_free(self->color);
	
	if(self->list)
	{
		gsize i;
		for(i = 0; i < self->list_size; ++i)
			g_free(self->list[i]);
		
		g_free(self->list);
	}
	
	G_OBJECT_CLASS(cp_label_list_parent_class)->finalize(object);
}

GType cp_label_list_get_type (void)
{
	static GType cp_label_list_type_id = 0;
	
	if(!cp_label_list_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpLabelListClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_label_list_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpLabelList),
			0,
			(GInstanceInitFunc) cp_label_list_instance_init,
			NULL
		};
		
		cp_label_list_type_id = g_type_register_static(
			G_TYPE_OBJECT, "CpLabelList", &g_define_type_info, 0
		);
	}
	
	return cp_label_list_type_id;
}

static void cp_label_list_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	CpLabelList* self = CP_LABEL_LIST(object);
	
	switch(property_id)
	{
		case COLOR_PROP:
			g_value_set_boxed(value, self->color);
			break;
		
		case LIST_PROP:
			g_value_set_boxed(value, self->list);
			break;
			
		case ANGLE_PROP:
			g_value_set_double(value, self->angle);
			break;
		
		case LIST_SIZE_PROP:
			g_value_set_uint(value, self->list_size);
			break;
			
		case FONT_SIZE_PROP:
			g_value_set_uint(value, self->font_size);
			break;
		
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_label_list_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	CpLabelList* self = CP_LABEL_LIST(object);
	
	switch(property_id)
	{
		case COLOR_PROP:
			*self->color = *CP_COLOR(g_value_get_boxed(value));
			break;
		
		case LIST_PROP:
			if(self->list) g_strfreev(self->list);
			self->list = g_value_dup_boxed(value);
			break;
		
		case ANGLE_PROP:
			self->angle = g_value_get_double(value);
			break;
		
		case LIST_SIZE_PROP:
			g_warn_if_reached();
			break;
			
		case FONT_SIZE_PROP:
			self->font_size = g_value_get_uint(value);
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

static CpLabelList* base_new(gsize list_size)
{
	CpLabelList* self = CP_LABEL_LIST(g_object_new(CP_TYPE_LABEL_LIST, NULL));
	g_return_val_if_fail(self != NULL, NULL);
	
	self->list = g_malloc(sizeof(gchar*) * list_size + 1);
	if(!self->list) {g_object_unref(self); return NULL;}
	
	self->color = cp_color_new_rgba(0, 0, 0, 1);
	if(!self->color) {g_object_unref(self); return NULL;}
	
	self->list[list_size] = NULL;
	self->list_size = list_size;
	self->angle = 0;
	
	return self;
}

CpLabelList* cp_label_list_new(gsize list_size, gchar* label, ...)
{
	CpLabelList* self = base_new(list_size);
	g_return_val_if_fail(self != NULL, NULL);
	
	va_list labels;
	va_start(labels, label);
	gsize counter = 0;
	
	while(counter < list_size && label)
	{
		self->list[counter] = g_strdup(label);
		
		if(!self->list[counter])
		{
			self->list_size = counter;
			g_object_unref(self);
			self = NULL;
			goto end;
		}
		
		label = va_arg(labels, gchar*);
		++counter;
	}
	
	end:
	va_end(labels);
	
	return self;
}

CpLabelList* cp_label_list_newv(gsize list_size, gchar** labels)
{
	CpLabelList* self = base_new(list_size);
	g_return_val_if_fail(self != NULL, NULL);
	
	gsize i;
	for(i = 0; i < list_size; ++i)
	{
		self->list[i] = g_strdup(labels[i]);
	
		if(!self->list[i])
		{
			self->list_size = i;
			g_object_unref(self);
			return NULL;
		}
	}
	
	return self;
}
