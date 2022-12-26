/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// vid_null.c -- null video driver to aid porting efforts

#include "quakedef.h"
#include "d_local.h"

#include <graph.h>
#define INCL_VIO
#define INCL_KBD
#include <os2.h>

VIOMODEINFO graph_mode;
VIOPHYSBUF phys;

viddef_t	vid;				// global video state

#define	BASEWIDTH	320
#define	BASEHEIGHT	200

byte	vid_buffer[BASEWIDTH*BASEHEIGHT];
short	zbuffer[BASEWIDTH*BASEHEIGHT];
byte	surfcache[256*1024];

unsigned short	d_8to16table[256];
unsigned	d_8to24table[256];

void	VID_SetPalette (unsigned char *palette)
{
int i;
int shiftcomponents;
char jpal[768];
/***
for(i=0;i<768;i++)
	{
	jpal[i]=palette[i];
	if(jpal[i]>63)
		jpal[i]=62;	//the OS/2 book says that nothing should excede 63...
	}
g_vgapal(jpal,0,255,1);***/
shiftcomponents=2;
_outp8(0x3c8,0);
for(i=0;i<768;i++)
	_outp8(0x3c9,palette[i]>>shiftcomponents);
}

void	VID_ShiftPalette (unsigned char *palette)
{
VID_SetPalette(palette);
}

void	VID_Init (unsigned char *palette)
{
	int pnum,chunk;
	byte *cache;
	int cachesize;
	int status;

	vid.maxwarpwidth = vid.width = vid.conwidth = BASEWIDTH;
	vid.maxwarpheight = vid.height = vid.conheight = BASEHEIGHT;
	vid.aspect = 1.0;
	vid.numpages = 1;
	vid.colormap = host_colormap;
	vid.fullbright = 256 - LittleLong (*((int *)vid.colormap + 2048));
	vid.buffer = vid.conbuffer = vid_buffer;
	vid.rowbytes = vid.conrowbytes = BASEWIDTH;
	vid.direct = 0;

	chunk=vid.width * vid.height * sizeof(d_pzbuffer);
	cachesize = D_SurfaceCacheForRes (vid.width,vid.height);
	chunk+=cachesize;
	
	d_pzbuffer = Hunk_HighAllocName(chunk,"video");
	if(d_pzbuffer==NULL)
		Sys_Error("Not enough memory for video mode\n");
	cache = (byte*)d_pzbuffer+vid.width*vid.height*sizeof(*d_pzbuffer);

	D_InitCaches(cache,cachesize);

//	old and SLOW.
//	g_mode(G_MODE_VGA_L);
	graph_mode.cb=13;
	graph_mode.fbType=3;
	graph_mode.color=8;		//bits depth
	graph_mode.col=40;		//text mode
	graph_mode.row=25;
	graph_mode.hres=320;	//graphics resolutions
	graph_mode.vres=200;
	graph_mode.fmt_ID=0;
	graph_mode.attrib=1;
	status=VioSetMode(&graph_mode,0);
	if(status!=0)
	{
	Sys_Error("error with VIOSETMODE\n");
	}	
	phys.pBuf=(PBYTE)0xa0000;
	phys.cb=0x10000;
	status=VioGetPhysBuf(&phys,0);
	if(status!=0)
	{
	Sys_Error("error with VioGetPhysBuf\n");
	}
}

void	VID_Shutdown (void)
{
g_mode(G_MODE_OFF);
}

void	VID_Update (vrect_t *rects)
{
int yofs;
int n,i,x,y;
unsigned char * graph_phys;

graph_phys=MAKEP(phys.asel[0],0);

/*yofs=0;
	for(y=0;y<200;y++)
	{
	for(x=0;x<320;x++)
		{
		g_set(x,y,vid_buffer[yofs]);
		yofs++;
		}
	}
*/
memcpy(graph_phys,vid_buffer,320*200);
}

/*
================
D_BeginDirectRect
================
*/
void D_BeginDirectRect (int x, int y, byte *pbitmap, int width, int height)
{
//printf("D_BeginDirectRect x%d y%d width%d height%d",x,y,width,height);
}


/*
================
D_EndDirectRect
================
*/
void D_EndDirectRect (int x, int y, int width, int height)
{
//printf("D_EndDirectRect %d %d %d %d\n",x,y,width,height);
}


//JASON
/*** its a macro on Quake
void VID_LockBuffer(void)
{
g_lock();
}

void VID_UnlockBuffer(void)
{
g_unlock();
}
****/

void VID_HandlePause (qboolean pause)
{
}
