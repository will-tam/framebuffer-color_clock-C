# Framebuffer Color Clock (C version)

A colored clock just in test of framebuffer library.
I confess this test/exercice idea comes from "Le Vortex" [https://www.youtube.com/@LeVortexARTE/videos](https://www.youtube.com/@LeVortexARTE/videos) and their clock.

**/!\ Assume FB is in 32bpp mode. /!\\**


## The best way to test :
- Create a Linux virtual machine (VM) with an X server.
- In console mode:
  - Check and configure network between VM and your physical machine (PM).
  - install, configure and run the ssh server.
  - Log off or not, but the VM still active.
- Open a terminal on your PM.
  - Open a ssh connection with the VM.
  - Install and configure the C development kit (gcc + make + lib in debug/dev).
  - Install git.
  - Clone this repository.
  - Go to the newly created directory.
  - Just type ```make```.
  - If all is ok, the VM console shows you nice arts, while the ssh terminal shows some information.

Of course, you can try directly in your PM (in TTY1 for example - CTRL-ALT-F1 if you use X interface). 
**BUT if something wrong, prepare to reboot your PM**.

## Great thanks to
- **HSL and HSV color** :
  - [https://en.wikipedia.org/wiki/HSL_and_HSV](https://en.wikipedia.org/wiki/HSL_and_HSV)
  - [https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/](https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/)

- **Framebuffer** :
  - [https://github.com/roddehugo/linuxfb?tab=readme-ov-file](https://github.com/roddehugo/linuxfb?tab=readme-ov-file)
  - [https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer](https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer)
  - [https://github.com/DirectFB/directfb/tree/master/systems/fbdev](https://github.com/DirectFB/directfb/tree/master/systems/fbdev)

- **Key events** :
  - [https://www.flipcode.com/archives/_kbhit_for_Linux.shtml](https://www.flipcode.com/archives/_kbhit_for_Linux.shtml)

- **Line and circle algorithmes** :
  - [https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
  - [https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d'Andres](https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d'Andres)
  - [https://gist.github.com/bert/1085538](https://gist.github.com/bert/1085538)

- **Tranforming HSV color format into GB color format** :
  - [https://www.rapidtables.com/convert/color/hsv-to-rgb.html](https://www.rapidtables.com/convert/color/hsv-to-rgb.html)
  - [https://en.wikipedia.org/w/index.php?title=HSL_and_HSV](https://en.wikipedia.org/w/index.php?title=HSL_and_HSV)


# ENJOY
