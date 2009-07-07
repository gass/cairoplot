#include "color.h"

GType cp_color_get_type()
{
	static GType our_type = 0;
	
	if(!our_type)
		our_type = g_boxed_type_register_static(
			"CpColor",
			(GBoxedCopyFunc)cp_color_copy,
			(GBoxedFreeFunc)cp_color_free
		);
		
	return our_type;
}

CpColor* cp_color_new()
{
	CpColor *cc = g_slice_new(CpColor);
	
	return cc;
}

CpColor* cp_color_copy(const CpColor* object)
{
	CpColor *cc = cp_color_new();
	*cc = *object;
	
	return cc;
}

CpColor* cp_color_new_rgba(double r, double g, double b, double a)
{
	CpColor *cc = cp_color_new();
	cp_color_set_rgba(cc, r, g, b, a);
	
	return cc;
}

void cp_color_free(CpColor* self)
{
	g_slice_free(CpColor, self);
}

void cp_color_set_rgba(CpColor* self, gdouble r, gdouble g, gdouble b, gdouble a)
{
	self->r = r;
	self->g = g;
	self->b = b;
	self->a = a;
}

void cp_color_get_rgba(CpColor* self, gdouble* r, gdouble* g, gdouble* b, gdouble* a)
{
	*r = self->r;
	*g = self->g;
	*b = self->b;
	*a = self->a;
}
