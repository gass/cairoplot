.PHONY: run
run: usage
	@LD_LIBRARY_PATH=../ ./usage

usage: usage.c
	$(CC) -g usage.c -o usage -I../src `pkg-config --cflags --libs pangocairo` -L../ -lcairoplot

clean:
	rm usage
