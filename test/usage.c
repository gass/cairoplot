#include <bar-plot.h>
#include <png-handler.h>

void callback(CpPlot* plot, gpointer data)
{
	g_debug("Callback! %s", data);
}

int main(int argc, char* argv[])
{
	g_type_init();
	gint i;
	
	for(i = 0; i < 1; ++i)
	{
		CpPlot* plot = cp_bar_plot_new();
		CpHandler* handler = cp_png_handler_new("out.png");
		
		g_object_set(plot, "handler", handler, NULL);
		cp_plot_render(plot);
		
		g_object_unref(plot);
		g_object_unref(handler);
	}
	
	return 0;
}
