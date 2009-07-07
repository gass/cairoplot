#include "label.h"

void cp_label_list_free(CpLabelList* self)
{
	if(self->color)
		cp_color_free(self->color);
	
	if(self->list)
	{
		gsize i;
		for(i = 0; i < self->list_size; ++i)
			g_free(self->list[i]);
		
		g_free(self->list);
	}
	
	g_slice_free(CpLabelList, self);
}

static CpLabelList* base_new(gsize list_size)
{
	CpLabelList* self = g_slice_new(CpLabelList);
	g_return_val_if_fail(self != NULL, NULL);
	
	self->list = g_malloc(sizeof(gchar*) * list_size + 1);
	if(!self->list) {cp_label_list_free(self); return NULL;}
	
	self->color = cp_color_new_rgba(0, 0, 0, 1);
	if(!self->color) {cp_label_list_free(self); return NULL;}
	
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
			cp_label_list_free(self);
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
			cp_label_list_free(self);
			return NULL;
		}
	}
	
	return self;
}

CpLabelList* cp_label_list_copy(CpLabelList* list)
{
	CpLabelList* self = base_new(list->list_size);
	g_return_val_if_fail(self != NULL, NULL);
	
	*self->color = *list->color;
	
	gsize i;
	for(i = 0; i < list->list_size; ++i)
	{
		self->list[i] = g_strdup(list->list[i]);
		
		if(!self->list[i])
		{
			self->list_size = i;
			cp_label_list_free(self);
			return NULL;
		}
	}
	
	return self;
}
