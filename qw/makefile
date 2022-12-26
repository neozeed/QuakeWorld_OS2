################################################################
#
# $Id:$
#
# $Log:$
#
CC=  gcc
STRIP=  strip

#CFLAGS=-g -Wall -DNORMALUNIX -DLINUX # -DUSEASM
#CFLAGS= -O0  -DNORMALUNIX -I../wat/inc
CFLAGS=-O0 -Did386=0  -I.
#LDFLAGS=-L/usr/X11R6/lib
#LIBS=-lXext -lX11 -lnsl -lm
LDFLAGS= -g
LIBS= -lbsd -lsocket -lgraph

# subdirectory for objects
O=os2

# not too sophisticated dependency
OBJS=				\
$(O)/cd_null.o	\
$(O)/d_edge.o \
$(O)/r_aclip.o	\
$(O)/r_vars.o	\
$(O)/d_fill.o	\
$(O)/r_alias.o	\
$(O)/sbar.o	\
$(O)/cl_demo.o	\
$(O)/d_init.o	\
$(O)/keys.o	\
$(O)/r_bsp.o	\
$(O)/screen.o	\
$(O)/cl_input.o	\
$(O)/d_modech.o	\
$(O)/mathlib.o	\
$(O)/r_draw.o	\
$(O)/d_part.o	\
$(O)/menu.o	\
$(O)/r_edge.o	\
$(O)/cl_parse.o	\
$(O)/d_polyse.o	\
$(O)/model.o	\
$(O)/r_efrag.o	\
$(O)/cl_tent.o	\
$(O)/d_scan.o	\
$(O)/r_light.o	\
$(O)/cmd.o	\
$(O)/d_sky.o	\
$(O)/r_main.o	\
$(O)/view.o	\
$(O)/common.o	\
$(O)/d_sprite.o	\
$(O)/r_misc.o	\
$(O)/wad.o	\
$(O)/d_surf.o	\
$(O)/nonintel.o	\
$(O)/r_part.o	\
$(O)/console.o	\
$(O)/d_vars.o	\
$(O)/r_sky.o	\
$(O)/zone.o	\
$(O)/crc.o	\
$(O)/d_zpoint.o	\
$(O)/r_sprite.o \
$(O)/cvar.o	\
$(O)/draw.o	\
$(O)/r_surf.o   \
$(O)/pmove.o   \
$(O)/pmovetst.o   \
$(O)/cl_ents.o   \
$(O)/cl_pred.o   \
$(O)/cl_cam.o   \
$(O)/cl_main.o	\
$(O)/skin.o   \
$(O)/md4.o   \
$(O)/net_udp.o	\
$(O)/net_chan.o	\
$(O)/snd_null.o	\
$(O)/in_null.o	\
$(O)/kbd_os2.o \
$(O)/j.o	\
$(O)/vid_os2.o

all:	 qw.exe

clean:
	del os2\*.o
	del qw.exe
	del dqw.exe
	

qw.exe:	$(OBJS) $(O)/sys_os2.o
	$(CC) $(LDFLAGS) $(OBJS) $(O)/sys_os2.o \
	-o dqw.exe $(LIBS)
	emxbind -e -f dqw.exe


SLOW=$(CC) -O0 -o $@ -c $<

$(O)/sys_null.o:	sys_null.c
	$(SLOW)	

DO_AS=$(CC) $(CFLAGS)  -x assembler-with-cpp -o $@ -c $<

#Assembly stuff
$(O)/d_copy.o :	d_copy.s
	$(DO_AS)

$(O)/sys_dosa.o :	sys_dosa.s
	$(DO_AS)

$(O)/r_edgea.o :	r_edgea.s
	$(DO_AS)

$(O)/surf8.o :	surf8.s
	$(DO_AS)

$(O)/surf16.o :	surf16.s
	$(DO_AS)

$(O)/math.o :	math.s
	$(DO_AS)

$(O)/d_polysa.o :	d_polysa.s
	$(DO_AS)

$(O)/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@


#############################################################
#
#############################################################
