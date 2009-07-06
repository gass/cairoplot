$(RM)=rm -f

.PHONY: run
run: usage
	@LD_LIBRARY_PATH=../ ./usage

.PHONY: usage
usage: usage.c
	$(CC) -g usage.c -o usage -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot
	gnome-open out.png

clean:
	$(RM) usage out*
