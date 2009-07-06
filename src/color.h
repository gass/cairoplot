#ifndef __CP_COLOR_H__
#define __CP_COLOR_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define CP_TYPE_COLOR             (cp_color_get_type())
#define CP_COLOR(object)          ((CpColor*)object)
#define CP_IS_COLOR(object)       ((object) && (CP_COLOR(object)->type == CP_TYPE_COLOR))

typedef struct
{
	GType type;
	double r,g,b,a;
} CpColor;

G_END_DECLS

GType cp_color_get_type();
CpColor* cp_color_new();
CpColor* cp_color_copy(const CpColor* object);
CpColor* cp_color_new_rgba(double r, double g, double b, double a);
void cp_color_free(CpColor* self);

#endif
