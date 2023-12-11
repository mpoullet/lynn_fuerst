/* graph.h */
#include <graphics.h>

#define	_lineto			lineto
#define	_moveto			moveto
#define 	_GCLEARSCREEN
#define 	_clearscreen 	clrscr
#define	_setvideomode  detectgraph(&gdriver,&gmode);if(gdriver==EGA||gdriver==EGA64||gdriver==EGAMONO||gdriver==VGA){gdriver=CGA;gmode=CGAC0;}
#define	_MRES16COLOR	initgraph(&gdriver,&gmode, "")
#define  _MAXRESMODE    gmode=CGAHI,initgraph(&gdriver,&gmode, "")
#define	_DEFAULTMODE	restorecrtmode()

int gdriver, gmode, errorcode;
