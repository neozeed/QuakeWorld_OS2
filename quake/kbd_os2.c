#include "quakedef.h"
#include "kbd_os2.h"

static void set_scantokey(void);

/* direct keyboard I/O routines were copied from 0verkill ... */

#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_DOSMONITORS
#define INCL_KBD
#include <os2.h>

//#define KBD_BUFFER_SIZE 256  /* size of buffer for incoming keys */
#define KBD_BUFFER_SIZE 256  /* size of buffer for incoming keys */


#define OS2_ALIGN(var) (_THUNK_PTR_STRUCT_OK(&var##1) ? &var##1 : &var##2)

HMONITOR os2_hmon = -1;

struct os2_key_packet {
	USHORT mon_flag;
	UCHAR chr;
	UCHAR scan;
	UCHAR dbcs;
	UCHAR dbcs_shift;
	USHORT shift_state;
	ULONG ms;
	USHORT dd_flag;
};

struct os2_buffer {
	USHORT cb;
	struct os2_key_packet packet;
	char pad[20];
};

struct os2_key_packet *os2_key;
struct os2_buffer *os2_in;
struct os2_buffer *os2_out;

int os2_read_mon(unsigned char *data, int len)
{
	static int prefix = 0;
	int bytes_read = 0;
	int r;
	USHORT count = sizeof(struct os2_key_packet);
	while (bytes_read < len) {
		int scan;
		r = DosMonRead((void *)os2_in, IO_NOWAIT, (void *)os2_key, &count);
		if (r == ERROR_MON_BUFFER_EMPTY) break;
		if (r) {
			fprintf(stderr, "DosMonRead: %d\n", r);
			sleep(1);
			break;
		}
		/*fprintf(stderr, "monflag: %04x, scan %02x, shift %04x\n", os2_key->mon_flag, os2_key->scan, os2_key->shift_state);*/
		scan = os2_key->mon_flag >> 8;
		/*fprintf(stderr, "scan: %02x\n", scan); fflush(stderr);*/
		if (scan == 0xE0) {
			prefix = 1;
			c:continue;
		}
		if (scan == 0xE1) {
			prefix = 2;
			continue;
		}
		if (prefix == 1) {
			prefix = 0;
			switch (scan & 0x7f) {
			case 29:	scan = (scan & 0x80) | 97; break;
			case 71:	scan = (scan & 0x80) | 102; break;
			case 72:	scan = (scan & 0x80) | 103; break;
			case 73:	scan = (scan & 0x80) | 104; break;
			case 75:	scan = (scan & 0x80) | 105; break;
			case 77:	scan = (scan & 0x80) | 106; break;
			case 79:	scan = (scan & 0x80) | 107; break;
			case 80:	scan = (scan & 0x80) | 108; break;
			case 81:	scan = (scan & 0x80) | 109; break;
			case 82:	scan = (scan & 0x80) | 110; break;
			case 83:	scan = (scan & 0x80) | 111; break;
			/* !!! FIXME: pause */
			default:	
		/*fprintf(stderr, "scan: %02x\n", scan); fflush(stderr);*/
					goto c;
			}
		}
		if (prefix == 3) {
			prefix = 0;
			continue;
		}
		if (prefix == 2) {
			prefix = 0;
			switch (scan & 0x7f) {
			case 29:	scan = (scan & 0x80) | 101; prefix = 3; break;
			default:	
		/*fprintf(stderr, "scan: %02x\n", scan); fflush(stderr);*/
					goto c;
			}
		}
		/*Con_Printf("%d\n", scan);*/
		data[bytes_read++] = scan;
	}
	return bytes_read;
}

void init_os2_keyboard(void)
{
	static struct os2_key_packet os2_key1, os2_key2;
	static struct os2_buffer os2_in1, os2_in2, os2_out1, os2_out2;
	int r;
	set_scantokey();
	if ((r = DosMonOpen("KBD$", &os2_hmon))) Sys_Error("DosMonOpen: %d\n", r);
	os2_key = OS2_ALIGN(os2_key);
	os2_in = OS2_ALIGN(os2_in);
	os2_out = OS2_ALIGN(os2_out);
	os2_in->cb = sizeof(struct os2_buffer) - sizeof(USHORT);
	os2_out->cb = sizeof(struct os2_buffer) - sizeof(USHORT);
	if ((r = DosMonReg(os2_hmon, (void *)os2_in, (void *)os2_out, MONITOR_END, -1))) {
		if (r == ERROR_MONITORS_NOT_SUPPORTED) {
			Sys_Error("VIO window not supported");
		} else {
			Sys_Error("DosMonReg: %d\n", r);
		}
	}
}

void shutdown_os2_keyboard(void)
{
	if (os2_hmon != (HMONITOR)-1) DosMonClose(os2_hmon);
	os2_hmon = -1;
}

static unsigned char scantokey[128];

void Sys_SendKeyEvents(void)
{
	char buf[KBD_BUFFER_SIZE];
	int i;
	if (os2_hmon == (HMONITOR)-1) return;
	while ((i = os2_read_mon(buf, KBD_BUFFER_SIZE))) {
		int j;
		for (j = 0; j < i; j++)
			Key_Event(scantokey[buf[j] & 0x7f], !(buf[j] & 0x80));
	}
}

static void set_scantokey(void)
{
	int i;
	for (i=0 ; i<128 ; i++)
		scantokey[i] = ' ';

	scantokey[  1] = K_ESCAPE;
	scantokey[  2] = '1';
	scantokey[  3] = '2';
	scantokey[  4] = '3';
	scantokey[  5] = '4';
	scantokey[  6] = '5';
	scantokey[  7] = '6';
	scantokey[  8] = '7';
	scantokey[  9] = '8';
	scantokey[ 10] = '9';
	scantokey[ 11] = '0';
	scantokey[ 12] = '-';
	scantokey[ 13] = '=';
	scantokey[ 14] = K_BACKSPACE;
	scantokey[ 15] = K_TAB;
	scantokey[ 16] = 'q';       
	scantokey[ 17] = 'w';       
	scantokey[ 18] = 'e';       
	scantokey[ 19] = 'r';       
	scantokey[ 20] = 't';       
	scantokey[ 21] = 'y';       
	scantokey[ 22] = 'u';       
	scantokey[ 23] = 'i';       
	scantokey[ 24] = 'o';       
	scantokey[ 25] = 'p';       
	scantokey[ 26] = '[';
	scantokey[ 27] = ']';
	scantokey[ 28] = K_ENTER;
	scantokey[ 29] = K_CTRL; //left
	scantokey[ 30] = 'a';
	scantokey[ 31] = 's';       
	scantokey[ 32] = 'd';       
	scantokey[ 33] = 'f';       
	scantokey[ 34] = 'g';       
	scantokey[ 35] = 'h';       
	scantokey[ 36] = 'j';       
	scantokey[ 37] = 'k';       
	scantokey[ 38] = 'l';       
	scantokey[ 39] = ';';
	scantokey[ 40] = '\'';
	scantokey[ 41] = '`';
	scantokey[ 42] = K_SHIFT; //left
	scantokey[ 43] = '\\';
	scantokey[ 44] = 'z';       
	scantokey[ 45] = 'x';  
	scantokey[ 46] = 'c';
	scantokey[ 47] = 'v';       
	scantokey[ 48] = 'b';
	scantokey[ 49] = 'n';       
	scantokey[ 50] = 'm';       
	scantokey[ 51] = ',';
	scantokey[ 52] = '.';
	scantokey[ 53] = '/';
	scantokey[ 54] = K_SHIFT; //right
	scantokey[ 55] = '*'; //keypad
	scantokey[ 56] = K_ALT; //left
	scantokey[ 57] = ' ';
	// 58 caps lock
	scantokey[ 59] = K_F1;
	scantokey[ 60] = K_F2;
	scantokey[ 61] = K_F3;
	scantokey[ 62] = K_F4;
	scantokey[ 63] = K_F5;
	scantokey[ 64] = K_F6;
	scantokey[ 65] = K_F7;
	scantokey[ 66] = K_F8;
	scantokey[ 67] = K_F9;
	scantokey[ 68] = K_F10;
	// 69 numlock
	// 70 scrollock
	scantokey[ 71] = K_HOME;
	scantokey[ 72] = K_UPARROW;
	scantokey[ 73] = K_PGUP;
	scantokey[ 74] = '-';
	scantokey[ 75] = K_LEFTARROW;
	scantokey[ 76] = '5';
	scantokey[ 77] = K_RIGHTARROW;
	scantokey[ 79] = K_END;
	scantokey[ 78] = '+';
	scantokey[ 80] = K_DOWNARROW;
	scantokey[ 81] = K_PGDN;
	scantokey[ 82] = K_INS;
	scantokey[ 83] = K_DEL;
	// 84 to 86 not used
	scantokey[ 87] = K_F11;
	scantokey[ 88] = K_F12;
	// 89 to 95 not used
	scantokey[ 96] = K_ENTER; //keypad enter
	scantokey[ 97] = K_CTRL; //right
	scantokey[ 98] = '/';
	scantokey[ 99] = K_F12; // print screen, bind to screenshot by default
	scantokey[100] = K_ALT; // right

	scantokey[101] = K_PAUSE; // break
	scantokey[102] = K_HOME;
	scantokey[103] = K_UPARROW;
	scantokey[104] = K_PGUP;
	scantokey[105] = K_LEFTARROW;
	scantokey[106] = K_RIGHTARROW;
	scantokey[107] = K_END;
	scantokey[108] = K_DOWNARROW;
	scantokey[109] = K_PGDN;
	scantokey[110] = K_INS;
	scantokey[111] = K_DEL;

	scantokey[119] = K_PAUSE;
}
