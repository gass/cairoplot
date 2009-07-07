# Compiler and flags
PKG_PACKAGES=pangocairo
CFLAGS=-c -g -pipe -Wall `pkg-config --cflags $(PKG_PACKAGES)`
LDFLAGS=-shared `pkg-config --libs $(PKG_PACKAGES)`

# Source
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

# Platform dependent
RM=rm -f
NAME=libcairoplot.so

# Rules

.PHONY: all
all: $(SOURCES) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) src/*.o $(NAME)

.PHONY: commit
commit:
	make clean
	git add .
	git commit
