#include "label.h"

/* TODO: protect allocation */
CpLabel cp_label_new(guint size, gchar* label, ...)
{
	va_list labels;
	va_start(labels, label);
	
	CpLabel self = g_malloc(sizeof(gchar*) * size + 1);
	guint ct = 0;
	
	while(ct < size && label)
	{
		self[ct] = g_strdup(label);
		label = va_arg(labels, gchar*);
		++ct;
	}
	
	self[size] = NULL;
	va_end(labels);
	
	return self;
}

void cp_label_free(CpLabel ptr)
{
	g_boxed_free(G_TYPE_STRV, ptr);
}
