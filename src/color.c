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
	cc->type = CP_TYPE_COLOR;
	
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
	cc->r = r;
	cc->g = g;
	cc->b = b;
	cc->a = a;
	
	return cc;
}

void cp_color_free(CpColor* self)
{
	g_slice_free(CpColor, self);
}

