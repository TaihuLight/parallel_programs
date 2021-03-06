/* Sequential Mandelbrot program */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define     X_RESN  800       /* x resolution */
#define     Y_RESN  800       /* y resolution */


int main ()
{
    Window      win;                            /* initialization for a window */
    unsigned
    int         width, height,                  /* window size */
                x, y,                           /* window position */
                border_width,                   /*border width in pixels */
                display_width, display_height,  /* size of screen */
                screen;                         /* which screen */

    char        *window_name = "Mandelbrot Set", *display_name = NULL;
    GC          gc;
    unsigned
    long        valuemask = 0;
    XGCValues   values;
    Display     *display;
    XSizeHints  size_hints;
    Pixmap      bitmap;
    XPoint      points[800];
    FILE        *fp, *fopen ();
    char        str[100];
    
    XSetWindowAttributes attr[1];
//********************
  Colormap screen_colormap;
  XColor red,brown,black,yellow,orange,violet,blue,green,my_color;
  Status rc;

//**************************
    /* Mandlebrot variables */
    int i, j, k;

    /* Open file containing data */
    FILE * input_file;

    input_file = fopen("mandelbrot_data.txt","r");
    if(input_file == NULL) {
        printf("Error opening file \n");
        return -1;
    } 
      
    /* connect to Xserver */

    if (  (display = XOpenDisplay (display_name)) == NULL ) {
        fprintf (stderr, "drawon: cannot connect to X server %s\n",
            XDisplayName (display_name) );
        exit (-1);
    }
    
    /* get screen size */

    screen = DefaultScreen (display);
    display_width = DisplayWidth (display, screen);
    display_height = DisplayHeight (display, screen);

    /* set window size */

    width = X_RESN;
    height = Y_RESN;

    /* set window position */

    x = 0;
    y = 0;

    /* create opaque window */

    border_width = 4;
    win = XCreateSimpleWindow (display, RootWindow (display, screen),
                x, y, width, height, border_width, 
                BlackPixel (display, screen), WhitePixel (display, screen));

    size_hints.flags = USPosition|USSize;
    size_hints.x = x;
    size_hints.y = y;
    size_hints.width = width;
    size_hints.height = height;
    size_hints.min_width = 300;
    size_hints.min_height = 300;
    
    XSetNormalHints (display, win, &size_hints);
    XStoreName(display, win, window_name);

    /* create graphics context */

    gc = XCreateGC (display, win, valuemask, &values);

    XSetBackground (display, gc, WhitePixel (display, screen));
    XSetForeground (display, gc, BlackPixel (display, screen));
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);

    attr[0].backing_store = Always;
    attr[0].backing_planes = 1;
    attr[0].backing_pixel = BlackPixel(display, screen);

    XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);

    XMapWindow (display, win);
    XSync(display, 0);
    
    /* Read in points and draw them */
//*****************
  screen_colormap = DefaultColormap(display, DefaultScreen(display));

  XAllocNamedColor(display, screen_colormap, "green", &green, &green);  
  XAllocNamedColor(display, screen_colormap, "yellow", &yellow, &yellow);  
  XAllocNamedColor(display, screen_colormap, "orange", &orange, &orange);
  XAllocNamedColor(display, screen_colormap, "red", &red, &red);
  XAllocNamedColor(display, screen_colormap, "brown", &brown, &brown);  
  XAllocNamedColor(display, screen_colormap, "violet", &black, &violet);
  XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue);
  XAllocNamedColor(display, screen_colormap, "black", &black, &black);
   

//****************

    for(i=0; i < X_RESN; i++) 
		for(j=0; j < Y_RESN; j++) 
		{

		   fscanf(input_file,"%d\n",&k);
		   
		   switch (k%8){
		   case 0: 
		   my_color=green;
		   break;
		   case 1: 
		   my_color=yellow;
		   break;
		   case 2: 
		   my_color=orange;
		   break;
		   case 3: 
		   my_color=red;
		   break;
		   case 4: 
		   my_color=brown;
		   break;
		   case 5: 
		   my_color=violet;
		   break;
		   case 6: 
		   my_color=blue;
		   break;

		   case 7: my_color=black;
		   }
		   XSetForeground(display, gc, my_color.pixel);
		   XDrawPoint (display, win, gc, j, i);
		}

    fclose(input_file);
   
    XFlush (display);
    sleep (30);

    /* Program Finished */
    return 0;
}


