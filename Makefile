CC := gcc
CPPFLAGS := -MMD -I include/
CFLAGS := -Wall -Wextra -g

LIBDIR := lib
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(LIBDIR)/%.o)
DEPS := $(OBJS:.o=.d)


.PHONY: all examples mrproper clean

all: $(LIBDIR)/libqlearning.a

$(LIBDIR)/libqlearning.a: $(OBJS)
	$(AR) -q $@ $^

$(LIBDIR)/%.o: src/%.c
	@mkdir -p $(LIBDIR)
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS)


examples: frozenlake

frozenlake: CPPFLAGS := -I include/
frozenlake: $(LIBDIR)/libqlearning.a
	$(CC) examples/*.c -o $@ $(CPPFLAGS) $(CFLAGS) -L$(LIBDIR) -lqlearning


mrproper:
	$(RM) frozenlake
	$(RM) -r $(LIBDIR)

clean:
	$(RM) $(LIBDIR)/*.o

-include $(DEPS)
