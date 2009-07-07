$(RM)=rm -f

.PHONY: run
run: usage label color
	@LD_LIBRARY_PATH=../ ./usage
	gnome-open out-usage.png
	@LD_LIBRARY_PATH=../ ./label
	@LD_LIBRARY_PATH=../ ./color
	
.PHONY: usage
usage: usage.c
	$(CC) -g -Wall usage.c -o usage -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot
	
.PHONY: label
label: label.c
	$(CC) -g -Wall label.c -o label -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot
	
.PHONY: color
color: color.c
	$(CC) -g -Wall color.c -o color -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot

clean:
	$(RM) usage label color out*
