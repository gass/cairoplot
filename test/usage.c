#include <bar-plot.h>

void callback(CpPlot* plot, gpointer data)
{
	g_debug("Callback! %s", data);
}

int main(int argc, char* argv[])
{
	g_type_init();
	
	while(TRUE)
	{
		CpPlot* plot = cp_plot_new();
		CpColor* color = cp_color_new_rgba(1, 0, 0, 1);
		g_object_set(plot, "border-color", color, NULL);
		cp_color_free(color);
		
		g_object_get(plot, "border-color", &color, NULL);
		g_debug("%lf %lf %lf %lf", color->r, color->g, color->b, color->a);
		cp_color_free(color);
		
		g_object_unref(plot);
	}
	
	return 0;
}
