#include <bar-plot.h>

void callback(CpPlot* plot, gpointer data)
{
	g_debug("Callback! %s", data);
}

int main(int argc, char* argv[])
{
	g_type_init();
	gint i;
	
	for(i = 0; i < 2000; ++i)
	{
		CpPlot* plot = cp_bar_plot_new();
		CpColor* color = cp_color_new_rgba(1, 0, 0, 1);
		g_object_set(plot, "border-color", color, NULL);
		cp_color_free(color);
		
		g_object_get(plot, "border-color", &color, NULL);
		g_assert(color->r == 1);
		g_assert(color->g == 0);
		g_assert(color->b == 0);
		g_assert(color->a == 1);
		cp_color_free(color);
		
		g_object_unref(plot);
	}
	
	return 0;
}
