#ifndef __CP_LABEL_H__
#define __CP_LABEL_H__

#include "color.h"

G_BEGIN_DECLS

/**
 * Represents a list of labels and its properties.
 */
typedef struct
{
	CpColor* color;
	gchar** list;
	gdouble angle;
	gsize list_size;
} CpLabelList;

CpLabelList* cp_label_list_new(gsize list_size, gchar* label, ...);
CpLabelList* cp_label_list_newv(gsize list_size, gchar** labels);
CpLabelList* cp_label_list_copy(CpLabelList* list);
void cp_label_list_free(CpLabelList* list);

G_END_DECLS

#endif
