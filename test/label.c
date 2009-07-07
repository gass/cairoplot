#include <label.h>

int main(int argc, char* argv[])
{
	g_type_init();
	
	gsize i;
	for(i = 0; i < 1000; ++i)
	{
		/* For C users  */
		CpLabelList* labels = cp_label_list_new(3, "one", "two", "three", NULL);
		g_object_unref(labels);
		
		/* For bindings */
		gchar** data = g_malloc(sizeof(gchar*) * 3);
		data[0] = "one";
		data[1] = "two";
		data[2] = "three";
		
		labels = cp_label_list_newv(3, data);
		g_free(data);
		
		gchar** test;
		g_object_get(labels, "list", &test, NULL);
		g_strfreev(test);
		
		g_object_unref(labels);
	}
	
	return 0;
}
