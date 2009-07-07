$(RM)=rm -f

.PHONY: run
run: usage
	@LD_LIBRARY_PATH=../ ./usage
	gnome-open out-usage.png
	
.PHONY: usage
usage: usage.c
	$(CC) -g -Wall usage.c -o usage -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot

clean:
	$(RM) usage out*
