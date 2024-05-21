/*
Thanks to --> See README.md ^^

(c) GPL v3 - FREE to use or modify, but don't show this to an IT manager-like, THANKS back all of you.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>                /* General terminal interface: tcgetattr, tcsetattr, tcflush. */
#include <unistd.h>                 /* Synchronous I/O multiplexing: select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO. */
#include <time.h>

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "fbtools.h"
#include "color_clock.h"
#include "clock.h"


/******* Functions *******/
int _kbhit(int mode) {
  /*
    Wait for a key pressed.
    Parameters : int mode = 0 => reset to canonical mode; 
                            1 = init and stop canonical mode; 
                            2 = just wait for a key.
    Return : with mode = 2, return how many time a key has been pressed.
  */

    static struct termios term; /* Get and set  terminal attributes, line control, get and set baud rate. */
    static const int STDIN = 0;

    int bytesWaiting;

    if (mode == 0)
    {
      term.c_lflag |= ICANON;
      tcsetattr(STDIN, TCSANOW, &term);
      setbuf(stdin, NULL);
      return 0;
    }

    if (mode == 1)
    {
      /* Use termios to turn off line buffering */
      tcgetattr(STDIN, &term);
      term.c_lflag &= ~ICANON;
      tcsetattr(STDIN, TCSANOW, &term);
      setbuf(stdin, NULL);
      return 0;
    }

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


int main()
{
  struct framebuffer *fbp;

  int ch;                 /* A key pressed. */

  clock_t firsttick;      /* First tick beggining FPS counter */

  
  _kbhit(1);

  fbp = initfb();
  if (!fbp)
  {
    perror("Can't start cause this last error ");
    _kbhit(0);
    return 1;
  }

  printf("framebuffer struct ptr addr : %p\n",fbp);
  printf("VRAM framebuffer ptr addr : %p\n", fbp->vramfbp);
  printf("Double buffer ptr addr : %p\n", fbp->dbp);

  printf("(x; y) res = %d X %d, %d bpp\n", fbp->vinfo.xres, fbp->vinfo.yres, fbp->vinfo.bits_per_pixel);
  printf("(x; y) virtual res = %d X %d, %d bpp\n", fbp->vinfo.xres_virtual, fbp->vinfo.yres_virtual, fbp->vinfo.bits_per_pixel);
  printf("screensize = %ld\n", fbp->screensize);
  printf("line_length = %d\n", fbp->finfo.line_length);
  printf("rotate = %d\n", fbp->vinfo.rotate);
  printf("activate = %d\n", fbp->vinfo.activate);
  printf("pixclock = %d\n", fbp->vinfo.pixclock);
  printf("hsync_len = %d\n", fbp->vinfo.hsync_len);
  printf("vsync_len = %d\n", fbp->vinfo.vsync_len);
  printf("sync = %d\n", fbp->vinfo.sync);

  printf("\n");

  /* Main loop */
  printf("\nESC to exit ...\n\n");

  printf("fbp->vinfo.activate = %d\n",fbp->vinfo.activate);

  clockinit(fbp);

  while (1)
  {
    while (!_kbhit(2))
    {
      firsttick = clock();

      /* Clear screen. */
      memset(fbp->dbp, 0, fbp->screensize);
      
      clockupdate(fbp);

      /* Flip buffer to framebuffer */
      memcpy(fbp->vramfbp, fbp->dbp, fbp->screensize);

      while (clock() - firsttick < FREQUENCY){ /* Wait until 1/FPS s */}

    }
    ch = getchar();
    if (ch == 27) { break; }    /* ESC => go out. */
  } 

  if (closefb(fbp) == -1)
  {
    perror("Coundn't close /dev/fb0 ");
  }
  else
  {
    printf("/dev/fb0 closed.\n");
  }

  _kbhit(0);

  return 0;
}