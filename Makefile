CC := gcc
CFLAGS := -Wall -Wextra -g
LDFLAGS := -I include/
LIBDIR := lib
OBJECTS := $(addprefix $(LIBDIR)/,$(patsubst %.c,%.o,$(notdir $(wildcard src/*.c))))

.PHONY: all examples mrproper clean


all: mrproper $(LIBDIR)/libqlearning.a

$(LIBDIR)/libqlearning.a: $(OBJECTS)
	ar -q $@ $^

$(LIBDIR)/%.o: src/%.c
	@mkdir -p $(LIBDIR)
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS)


examples: frozenlake

frozenlake: $(LIBDIR)/libqlearning.a
	$(CC) examples/*.c -o $@ $(CFLAGS) $(LDFLAGS) -L$(LIBDIR) -lqlearning


mrproper:
	rm -f frozenlake
	rm -rf $(LIBDIR)

clean:
	rm -f $(LIBDIR)/*.o
