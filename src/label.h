#ifndef __CP_LABEL_H__
#define __CP_LABEL_H__

#include "color.h"

G_BEGIN_DECLS

#define CP_TYPE_LABEL_LIST (cp_label_list_get_type ())
#define CP_LABEL_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_LABEL_LIST, CpLabelList))
#define CP_LABEL_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_LABEL_LIST, CpLabelListClass))
#define CP_IS_LABEL_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_LABEL_LIST))
#define CP_IS_LABEL_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_LABEL_LIST))
#define CP_LABEL_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_LABEL_LIST, CpLabelListClass))

/**
 * Represents a list of labels and its properties.
 */
typedef struct
{
	GObject parent_instance;
	CpColor* color;
	gchar** list;
	gdouble angle;
	gsize list_size;
	gsize font_size;
} CpLabelList;

typedef struct
{
	GObjectClass parent_class;
} CpLabelListClass;

GType cp_label_list_get_type();
CpLabelList* cp_label_list_new(gsize list_size, gchar* label, ...);
CpLabelList* cp_label_list_newv(gsize list_size, gchar** labels);

G_END_DECLS

#endif
