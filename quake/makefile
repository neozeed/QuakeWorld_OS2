################################################################
#
# $Id:$
#
# $Log:$
#
CC=  gcc  # gcc or g++
STRIP=  strip  # gcc or g++

CFLAGS= -O2
LDFLAGS= 
LIBS= -lbsd -lsocket -lgraph

# subdirectory for objects
O=os2

# not too sophisticated dependency
OBJS=                           \
$(O)/cd_null.o  \
$(O)/d_edge.o \
$(O)/d_part.o \
$(O)/host.o \
$(O)/r_aclip.o  \
$(O)/r_vars.o   \
$(O)/chase.o    \
$(O)/d_fill.o   \
$(O)/host_cmd.o \
$(O)/r_alias.o  \
$(O)/sbar.o     \
$(O)/cl_demo.o  \
$(O)/d_init.o   \
$(O)/keys.o     \
$(O)/r_bsp.o    \
$(O)/screen.o   \
$(O)/cl_input.o \
$(O)/d_modech.o \
$(O)/mathlib.o  \
$(O)/R_DRAW.o   \
$(O)/sv_main.o \
$(O)/cl_main.o  \
$(O)/menu.o     \
$(O)/r_edge.o   \
$(O)/sv_move.o  \
$(O)/cl_parse.o \
$(O)/d_polyse.o \
$(O)/model.o    \
$(O)/r_efrag.o  \
$(O)/sv_phys.o  \
$(O)/cl_tent.o  \
$(O)/d_scan.o   \
$(O)/net_loop.o \
$(O)/r_light.o  \
$(O)/sv_user.o  \
$(O)/cmd.o      \
$(O)/d_sky.o    \
$(O)/net_main.o \
$(O)/r_main.o   \
$(O)/view.o     \
$(O)/common.o   \
$(O)/d_sprite.o \
$(O)/net_vcr.o  \
$(O)/r_misc.o   \
$(O)/wad.o      \
$(O)/d_surf.o   \
$(O)/r_part.o   \
$(O)/world.o    \
$(O)/console.o  \
$(O)/d_vars.o   \
$(O)/pr_cmds.o  \
$(O)/r_sky.o    \
$(O)/zone.o     \
$(O)/crc.o      \
$(O)/d_zpoint.o \
$(O)/pr_edict.o \
$(O)/r_sprite.o \
$(O)/cvar.o     \
$(O)/draw.o     \
$(O)/pr_exec.o  \
$(O)/r_surf.o   \
$(O)/net_bsd.o  \
$(O)/net_udp.o  \
$(O)/net_dgrm.o \
$(O)/snd_null.o \
$(O)/in_os2.o   \
$(O)/kbd_os2.o   \
$(O)/vid_os2.o  \
$(O)/nonintel.o

all:     quake.exe

clean:
	rm -f *.o *~ *.flc
	rm -f quake.exe
	rm -f dquake.exe
	rm -f dos/*.o

quake.exe:      $(OBJS) $(O)/sys_os2.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(O)/sys_os2.o \
	-o dquake.exe $(LIBS)
	emxbind -e -f dquake.exe
	del quake.exe
	copy dquake.exe quake.exe
	$(STRIP) quake.exe


DO_AS=$(CC) $(CFLAGS)  -x assembler-with-cpp -o $@ -c $<

#       -o $(O)/dosdoom $(LIBS)
$(O)/d_copy.o : d_copy.s
	$(DO_AS)

$(O)/sys_dosa.o :       sys_dosa.s
	$(DO_AS)

$(O)/Dosasm.o : dosasm.s
	$(DO_AS)

$(O)/D_DRAW.o : d_draw.s
	$(DO_AS)

$(O)/D_DRAW16.o : D_draw16.s
	$(DO_AS)

$(O)/D_PARTA.o : D_PARTA.s
	$(DO_AS)

$(O)/D_POLYSA.o : d_polysa.s
	$(DO_AS)

$(O)/D_SCANA.o : d_scana.s
	$(DO_AS)

$(O)/D_SPR8.o : d_spr8.s
	$(DO_AS)

$(O)/D_VARSA.o : d_varsa.s
	$(DO_AS)

$(O)/MATH.o : math.s
	$(DO_AS)

$(O)/R_ACLIPA.o : r_aclipa.s
	$(DO_AS)

$(O)/R_ALIASA.o : r_aliasa.s
	$(DO_AS)

$(O)/R_DRAWA.o : R_DRAWA.s
	$(DO_AS)

$(O)/R_EDGEA.o : r_edgea.s
	$(DO_AS)

$(O)/R_VARSA.o : r_varsa.s
	$(DO_AS)

$(O)/SND_MIXA.o : snd_mixa.s
	$(DO_AS)

$(O)/SURF16.o : surf16.s
	$(DO_AS)

$(O)/SURF8.o : surf8.s
	$(DO_AS)

$(O)/WORLDA.o : worlda.s
	$(DO_AS)

$(O)/%.o:       %.c
	$(CC) $(CFLAGS) -c $< -o $@


#############################################################
#
#############################################################
