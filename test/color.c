#include <color.h>

int main(int argc, char* argv[])
{
	g_type_init();
	gdouble r = 0.1, g = 0.2, b = 0.3, a = 0.4;
	gdouble nr = 0.1, ng = 0.2, nb = 0.3, na = 0.4;
	
	gsize i;
	for(i = 0; i < 1000; ++i)
	{
		CpColor* cp = cp_color_new_rgba(r, g, b, a);
		cp_color_get_rgba(cp, &nr, &ng, &nb, &na);
		g_assert(nr == r);
		g_assert(ng == g);
		g_assert(nb == b);
		g_assert(na == a);
		g_boxed_free(CP_TYPE_COLOR, cp);
	}
	
	return 0;
}
