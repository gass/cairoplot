#ifndef __CP_LABEL_H__
#define __CP_LABEL_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef gchar** CpLabel;

CpLabel cp_label_new(guint size, gchar* label, ...);
void cp_label_free(CpLabel ptr);

G_END_DECLS

#endif
