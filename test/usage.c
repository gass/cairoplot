#include <bar-plot.h>
#include <memory-handler.h>
#include <png-handler.h>
#include <label.h>
#include <string.h>

void label_test()
{
	while(TRUE)
	{
		/* For C users. What's the param limit for varargs? */
		CpLabelList* labels = cp_label_list_new(3, "one", "two", "three", NULL);
		cp_label_list_free(labels);
		
		/* For bindings */
		gchar** data = g_malloc(sizeof(gchar*) * 3);
		data[0] = "one";
		data[1] = "two";
		data[2] = "three";
		
		labels = cp_label_list_newv(3, data);
		g_free(data);
		
		/* Copy */
		CpLabelList* copy_of = cp_label_list_copy(labels);
		cp_label_list_free(copy_of);
		
		cp_label_list_free(labels);
	}
}

void callback(CpPlot* plot, gpointer data)
{
	g_debug("Callback! %s", (gchar*)data);
}

int main(int argc, char* argv[])
{
	g_type_init();
	
	label_test();
	
	CpPlot* plot = cp_bar_plot_new();
	CpHandler* handler = cp_png_handler_new("out-usage.png");
	CpColor* color = cp_color_new_rgba(0.9, 0.9, 0.9, 0.5);
		
	g_object_set(plot, "handler", handler, "bg-color", color, NULL);
	cp_plot_render(plot);
		
	g_boxed_free(CP_TYPE_COLOR, color);
	g_object_unref(plot);
	g_object_unref(handler);
	
	return 0;
}
