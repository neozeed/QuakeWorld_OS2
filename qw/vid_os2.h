#include <sys/hw.h>

void vid_os2_shutdown(void);
void *vid_os2_set_g_mode(void);
#define outportb _outp8
#define inportb _inp8
#define dos_outportb outportb

int vid_os2_can_update(void);
void vid_os2_wait_update(void);
void vid_os2_end_update(void);
