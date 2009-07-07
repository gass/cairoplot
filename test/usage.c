#include <bar-plot.h>
#include <memory-handler.h>
#include <png-handler.h>

void callback(CpPlot* plot, gpointer data)
{
	g_debug("Callback! %s", (gchar*)data);
}

int main(int argc, char* argv[])
{
	g_type_init();
	
	CpPlot* plot = cp_bar_plot_new();
	CpHandler* handler = cp_png_handler_new("out-usage.png");
	CpColor* color = cp_color_new_rgba(0.9, 0.9, 0.9, 0.5);
		
	g_object_set(plot, "handler", handler, "bg-color", color, NULL);
	g_signal_connect(plot, "pre-render", G_CALLBACK(callback), "pre");
	g_signal_connect(plot, "pos-render", G_CALLBACK(callback), "pos");
	cp_plot_render(plot);
		
	g_boxed_free(CP_TYPE_COLOR, color);
	g_object_unref(plot);
	g_object_unref(handler);
	
	return 0;
}
