ACLOCAL_AMFLAGS = -I m4 --install

bin_PROGRAMS = blip
blip_SOURCES = src/blip.c vendor/mpc/mpc.c

blip_CFLAGS = $(DEPS_CFLAGS)
blip_LDFLAGS = $(DEPS_LIBS) -lm
