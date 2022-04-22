/* landmark.c  Daniel Scharstein  6/19/99 */

/* recognizes landmarks with horizontal self-similar pattern with
 * known scale factor in a pgm image
 *
 * implemented as procedure
 */

static char rcsid[] = "$Id: landmark.c 6071 2015-10-16 21:58:31Z carrick $";

/* #define IMAGE_CHECKALL */

#include <stdio.h>
#include <math.h>
/*#include "misc.h"*/
#include "image.h"
#include "digits.h"
#include "landmark.h"

/* defined in findlines.c */
landmarks findLines(FloatImage matchIm, GrayImage im1, int spacing);

/* defined in barcode.c */
landm decode(GrayImage im, int x1, int y1, int x2, int y2);

#define PLOT 1
#define PLOTBW 0

#define PLOTHEIGHT 100


#define YEL 0 /*0-yellow, 255-white*/    
#define DIM .5 /* dim factor */

static RGB white = {255, 255, 255};
static RGB black = {0, 0, 0};
static RGB red = {255, 0, 0};
/*static RGB green = {0, 255, 0};*/
/*static RGB blue = {0, 0, 255};*/
static RGB lgray = {180, 180, 180};



void plotline(GrayImage im1, int y, int minv, int maxv,
	      char *fname, int num, RGB color);

void plotlineF(FloatImage im1, int y, float minv, float maxv,
	       char *fname, int num, RGB color);

void plotlinebw(GrayImage im1, int y, int minv, int maxv,
		char *fname, int num, int plotheight,
		int window, int peakw, int smaxpos, float smax);

void plotlineFbw(FloatImage im1, int y, float minv, float maxv,
		 char *fname, int num, int plotheight,
		 int window, int peakw, int smaxpos, float smax);


/* linear interpolation ... only works with GCC? */
#define imRefInterp(Im, x, n) ({ \
	 int xx0 = (int)(x);    \
         int xx1 = xx0+1;       \
	 float xxd = (x) - xx0; \
	 (1.0 - xxd) * imRef((Im), xx0, (n)) \
             + xxd * imRef((Im), xx1, (n)); })

/* just rounding (at least twice as fast) */
#define imRefInterp1(Im, x, n) (imRef((Im), (int)((x)+.5), (n)))

#define MAXWIN 500


landmarks landmark(GrayImage im1, char *outImName, int verbose, int drawX) {
  return landmarkParams(im1, outImName, verbose, drawX,
			WINDOW_DEFAULT, PEAKW_DEFAULT, THRESHOLD_DEFAULT,
			FACTOR_DEFAULT,	 SPACING_DEFAULT, SKIP_DEFAULT, -1);
}


landmarks landmarkParams(GrayImage im1, char *outImName,
			 int verbose, int drawX, int window, int peakw,
			 int threshold, double factor,  int spacing,
			 int skip,  int ycoord) {
  int width, height;
  int y0, yinc, y, x, z, i;
  landm lam;
  landmarks lamarr;
  int nlines, n;
  float p, sp;
  float smin;
  int smaxpos;
  float smax;
  FloatImage avgIm, sumIm, matchIm;
  RGBImage outim = NULL;
  int writeOutIm = (outImName != NULL);
  

  int ip[MAXWIN], isp[MAXWIN];
  float fp0[MAXWIN], fp1[MAXWIN], fsp0[MAXWIN], fsp1[MAXWIN];
  
  int avglines = 1;
  
  width = imGetWidth(im1); height = imGetHeight(im1);
  
  if (ycoord >= 0) { /* single line */
    y0 = MAX(avglines/2, MIN(height-1-avglines/2, ycoord));
    yinc = height+1;
  } else {
    y0 = MAX(spacing, avglines) / 2;
    yinc = spacing;
  }
  nlines = (height - 1 - y0) / yinc + 1;

  p = 1 - 1.0/factor;
  sp = sqrt(p);

  if (verbose) {
      fprintf(stderr, "image size: %d x %d\n", width, height);
      fprintf(stderr,
	      "factor = %g, avglines = %d, spacing = %d, lines = %d\n",
	      factor, avglines, spacing, nlines);
      fprintf(stderr,
     "window = %d, threshold = %d, peak width = %d, skip = %d\n",
	      window, threshold, peakw, skip);
    }

  avgIm = (FloatImage)imNew(IMAGE_FLOAT, width, nlines);
  assert(avgIm);
  sumIm = (FloatImage)imNew(IMAGE_FLOAT, width, nlines);
  assert(sumIm);
  matchIm = (FloatImage)imNew(IMAGE_FLOAT, width, nlines);
  assert(matchIm);


  /* precompute weights */
  assert(window<MAXWIN);
  for (x=0; x<window; x++) {
    float xsp = sp*x;  /* scale by sqrt(p) (mismatch) */
    float xp  = p*x;   /* scale by p (match) */
    int ixsp = (int) xsp;
    int ixp = (int) xp;
    float dsp = xsp-ixsp;
    float dp = xp-ixp;
    isp[x] = ixsp;
    fsp0[x] = 1.0 - dsp;
    fsp1[x] = dsp;
    ip[x] = ixp;
    fp0[x] = 1.0 - dp;
    fp1[x] = dp;
  }

  
  smax = -100;
  smaxpos = 0;
  smin = 100;
  for (n=0, y=y0; y < height; n++, y+=yinc) {
    
    assert(n < nlines);

    for (x=0; x<width; x++) {
      if (avglines==1)
	imRef(avgIm, x, n) = imRef(im1, x, y);
      else {
	float av = 0;
	int k0 = MAX(0, y-avglines/2);
	int k1 = MIN(height-1, k0+avglines);
	int k;
	for (k=k0; k<k1; k++)
	  av += imRef(im1, x, k);
	av = av/avglines;
	imRef(avgIm, x, n) = av;
      }
      imRef(matchIm, x, n) = 0.0; /* no match */
    }

#define PRECOMPUTE 1 /* use precomputed values -- twice as fast */

    /* try to make faster */

    for (x=0; x<width; x++) {
      float s = 0;
      float s1 = 0;
      float s2 = 0;
      int zmax = MIN(x+1, window);
      for (z=skip; z<zmax; z++) {
	int x0 = x-z;
	float v0 = imRef(avgIm, x0, n); /* original image */
	float v1, v2;
	if (PRECOMPUTE) {
	  int x1 = x-isp[z];
	  int x2 = x-ip[z];
	  v1 = fsp0[z]*imRef(avgIm, x1, n)+fsp1[z]*imRef(avgIm, x1-1, n);
	  v2 = fp0[z] *imRef(avgIm, x2, n)+fp1[z] *imRef(avgIm, x2-1, n);
	} else { /* not used */
	  float x1 = x - sp*z;  /* scale by sqrt(p) (mismatch) */
	  float x2 = x - p*z;  /* scale by p (match) */
	  v1 = imRefInterp(avgIm, x1, n); /* scaled image */
	  v2 = imRefInterp(avgIm, x2, n); /* scaled image */
	}
	s1 += ABS(v0 - v1);
	s2 += ABS(v0 - v2);
	if (x == 480 && 0)
	  fprintf(stderr,
      "z=%2d  v0=%3d  v1=%3d  v2=%3d  dsp=%3d  dp=%3d  m=%3d\n",
		  z, (int)v0, (int)v1, (int)v2,
		  (int)ABS(v0-v1), (int)ABS(v0-v2),
		  (int)(ABS(v0-v1) - ABS(v0-v2)));

      }
      s = (s1 - s2) / MAX(zmax-skip, 1);
      imRef(sumIm, x, n) = s;
      if (s > smax) {
	smax = s;
	smaxpos = x;
      }
      smin = MIN(s, smin);
    }
    if (PLOT && ycoord >= 0) {
      if (PLOTBW) {
	plotlinebw(im1, y, 0, 255, "plot.line", y, 50, window, peakw,
		   smaxpos, smax);
	plotlineFbw(sumIm, n, -255, 255, "plot.match", y, 100, window,
		    peakw, smaxpos, smax);
      } else {
	plotline(im1, y, 0, 255, "plot.line", y, black);
	/*plotlineF(avgIm, n, 0, 255, "plot.avg", y, blue);*/
	plotlineF(sumIm, n, -255, 255, "plot.match", y, red);
      }
    }
  }
  imFree(avgIm);
  
  if (verbose && 0)
    fprintf(stderr, "smin=%g, smax=%g (%g)\n", smin, smax, smax/255.0);

  if (writeOutIm) {
    outim = (RGBImage)imNew(IMAGE_RGB, width, height);
    assert(outim);
    for (y=0; y<height; y++) {
      for (x=0; x<width; x++) {
	int v = (int)(DIM*imRef(im1, x, y)); /* make it dimmer */
	RGB gray = {v, v, v};
	imRef(outim, x, y) = gray;
      }
    }
  }
    
  /* find peaks */
    
  for (n=0; n<nlines; n++) {
    /* fprintf(stderr, "y %3d   n %2d\n", y, n);*/
    for (x=peakw; x<width-peakw; x++) {
      float sv = imRef(sumIm, x, n);
/*	float tt = MIN(sv/2, sv-threshold);*/
      float tt = sv-threshold;
      float svl = imRef(sumIm, x-1, n);
      float svr = imRef(sumIm, x+1, n);
      float svll = imRef(sumIm, x-peakw, n);
      float svrr = imRef(sumIm, x+peakw, n);
      if ((sv > threshold) && (sv > svl) && (sv >= svr)
	  && (tt > svll) && (tt > svrr)) {
	imRef(matchIm, x, n) = sv;

	if (writeOutIm && drawX) {
	  int v = MAX(0, MIN(255, (int)(255.0*sv/smax)));
	  RGB col = {255, MAX(v, YEL), YEL};
	  int k;
	  y = y0 + n*yinc;
	  for (k=1; k<4; k++) {
	    imRef(outim, MAX(0, x-k), MAX(0, y-k)) = col;
	    imRef(outim, MAX(0, x-k), MIN(height-1, y+k)) = col;
	    imRef(outim, MIN(width-1, x+k), MAX(0, y-k)) = col;
	    imRef(outim, MIN(width-1, x+k), MIN(height-1, y+k)) = col;
	  }
	}	  
      }
    }
  }

  imFree(sumIm);


  /* for n,  for x,  find "lines" up to 45 deg in matchIm
     for each line, call decode
     decode returns landm structure
     collect all those in landmark array
  */


  lamarr = findLines(matchIm, im1, spacing);
  imFree(matchIm);
    
  /*  fprintf(stderr, "NUMBER = %d\n", lamarr.count);*/
  for (i=0; i<lamarr.count; i++) {
    RGB yellow = {255, 255, 0};
    int k;
    lam = lamarr.lm[i];
    if (lam.code>-2) {
      if (writeOutIm) {
	putnumberRGB(lam.code, outim, MAX(0, lam.xtop-2-DIGIT_WIDTH *
                    (lam.code>99 ? 3 : (lam.code>9 ? 2 : 1))),
		     lam.ytop, white);


       
	for (k=-5; k<=5; k++) {
	  int mm = MIN(MIN(lam.xtop, lam.ytop), MIN(lam.xbottom, lam.ybottom));
	  int MMx = MAX(lam.xtop, lam.xbottom);
	  int MMy = MAX(lam.ytop, lam.ybottom);
	  if (mm>=0 && MMx<width && MMy < height) {
   imRef(outim, MAX(0, MIN(width-1, lam.xtop+k)), lam.ytop) = yellow;
   imRef(outim, lam.xtop, MAX(0, MIN(height-1, lam.ytop+k))) = yellow;
   imRef(outim, MAX(0, MIN(width-1, lam.xbottom+k)), lam.ybottom) = yellow;
   imRef(outim, lam.xbottom, MAX(0, MIN(height-1, lam.ybottom+k))) = yellow;
	  }
	}
      }
      if (verbose)
	fprintf(stderr, "found at %3d,%3d to %d,%d - code = %d\n",
		lam.xtop, lam.ytop, lam.xbottom, lam.ybottom, lam.code);
    }
  }

  if (writeOutIm) {
    if (imSave(outim, outImName) < 0) {
      fprintf(stderr, "can't save image\n"); exit(1); }
    if (verbose)
      fprintf(stderr, "saving image %s\n", outImName);
    imFree(outim);
  }
  
  assert(rcsid); /* to avoid warning message */
  
  return lamarr;
}

#define VERBOSE 1

void plotline(GrayImage im1, int y, int minv, int maxv,
	      char *fname, int num, RGB color)
{
  int width = imGetWidth(im1);
  RGBImage plot = (RGBImage)imNew(IMAGE_RGB, width, PLOTHEIGHT);
  int x, k, v, vold;
  char plotname[80];
 
  assert(plot);
  vold =(int)(((float)imRef(im1, 0, y) - minv)*PLOTHEIGHT/(maxv-minv));
  vold=MIN(PLOTHEIGHT-1, MAX(0, vold));
  for (x=0; x<width; x++) {
    for (k=0; k<PLOTHEIGHT; k++)
      imRef(plot, x, k) = white;
      
    v=(int)(((float)imRef(im1, x, y) - minv)*PLOTHEIGHT/(maxv-minv));
    if (vold < v)
      for (k=vold; k<=v && k<PLOTHEIGHT; k++)
	imRef(plot, x, PLOTHEIGHT-1-k) = color;
    else
      for (k=vold; k>=v && k>=0; k--)
	imRef(plot, x, PLOTHEIGHT-1-k) = color;
    vold=MIN(PLOTHEIGHT-1, MAX(0, v));
  }
  sprintf(plotname, "%s.%d.ppm", fname, num);
  if (imSave(plot, plotname) < 0) {
    fprintf(stderr, "can't save image\n"); exit(1); }
  if (VERBOSE)
    fprintf(stderr, "saving image %s\n", plotname);
  
  imFree(plot);
}

void plotlineF(FloatImage im1, int y, float minv, float maxv,
	       char *fname, int num, RGB color)
{
  int width = imGetWidth(im1);
  RGBImage plot = (RGBImage)imNew(IMAGE_RGB, width, PLOTHEIGHT);
  int x, k, v, vold;
  float val;
  char plotname[80];
 
  assert(plot);
  vold = (int)((imRef(im1, 0, y) - minv)*PLOTHEIGHT/(maxv-minv));
  vold=MIN(PLOTHEIGHT-1, MAX(0, vold));
  for (x=0; x<width; x++) {
    for (k=0; k<PLOTHEIGHT; k++)
      imRef(plot, x, k) = white;

    if (minv<0 && maxv > 0) /* draw zero line */
      imRef(plot, x, (int)(-minv*PLOTHEIGHT/(maxv-minv))) = lgray;
    
    val = imRef(im1, x, y);
    v = (int)((val - minv)*PLOTHEIGHT/(maxv-minv));
    if (vold < v)
      for (k=vold; k<=v && k<PLOTHEIGHT; k++)
	imRef(plot, x, PLOTHEIGHT-1-k) = color;
    else
      for (k=vold; k>=v && k>=0; k--)
	imRef(plot, x, PLOTHEIGHT-1-k) = color;
    vold=MIN(PLOTHEIGHT-1, MAX(0, v));
  }
  sprintf(plotname, "%s.%d.ppm", fname, num);
  if (imSave(plot, plotname) < 0) {
    fprintf(stderr, "can't save image\n"); exit(1); }
  if (VERBOSE)
    fprintf(stderr, "saving image %s\n", plotname);
  
  imFree(plot);
}


/* same in black / white */

#define GRAY 170
#define LINES 1

void frame(GrayImage im1, int lines, int window, int peakw,
	   int smaxpos, float smax)	   
{
  int w = imGetWidth(im1);
  int h = imGetHeight(im1);
  int x, y;
  
  for (y=0; y<h; y++)
    for (x=0; x<w; x++)
      imRef(im1, x, y) = 255;

  for (y=0; y<h; y++) {
    imRef(im1, 0, y) = GRAY;
    imRef(im1, w-1, y) = GRAY;
    if (lines && LINES) {
      imRef(im1, smaxpos, y) = GRAY;
      imRef(im1, smaxpos-window, y) = GRAY;
    }
  }

  if (lines && LINES) {
    int y0 = h/2;
    int ym = h/2-smax*h/(2*255);
    int y2 = (y0+ym)/2;
/*    int y2 = h/2-(smax-threshold)*h/(2*255);*/
    int xl = smaxpos-(int)(2*peakw);
    int xr = smaxpos+(int)(2*peakw);
    int xl2 = smaxpos-(int)(peakw);
    int xr2 = smaxpos+(int)(peakw);

    for (y=y0; y>ym; y--) {
      imRef(im1, xl, y) = GRAY; imRef(im1, xr, y) = GRAY; }
    for (x=xl; x<=xr; x++)
      imRef(im1, x, ym) = GRAY;
    for (y=y2; y>ym; y--) {
      imRef(im1, xl2, y) = GRAY; imRef(im1, xr2, y) = GRAY; }
    for (x=xl; x<=xl2; x++)
      imRef(im1, x, y2) = GRAY;
    for (x=xr2; x<=xr; x++)
      imRef(im1, x, y2) = GRAY;
  }
  
  for (x=0; x<w; x++) {
    imRef(im1, x, 0) = GRAY;
    imRef(im1, x, h-1) = GRAY;
  }
}

void plotlinebw(GrayImage im1, int y, int minv, int maxv,
		char *fname, int num, int plotheight,
		int window, int peakw, int smaxpos, float smax)
{
  int width = imGetWidth(im1);
  GrayImage plot = (GrayImage)imNew(IMAGE_GRAY, width, plotheight);
  int x, k, v, vold;
  char plotname[80];

  assert(plot);

  frame(plot, 0, window, peakw, smaxpos, smax);
  
  vold =(int)(((float)imRef(im1, 0, y) - minv)*plotheight/(maxv-minv));
  vold=MIN(plotheight-1, MAX(0, vold));
  for (x=0; x<width; x++) {

    v=(int)(((float)imRef(im1, x, y) - minv)*plotheight/(maxv-minv));
    if (vold < v)
      for (k=vold; k<=v && k<plotheight; k++)
	imRef(plot, x, plotheight-1-k) = 0;
    else
      for (k=vold; k>=v && k>=0; k--)
	imRef(plot, x, plotheight-1-k) = 0;
    vold=MIN(plotheight-1, MAX(0, v));
  }
  sprintf(plotname, "%s.%d.pgm", fname, num);
  if (imSave(plot, plotname) < 0) {
    fprintf(stderr, "can't save image\n"); exit(1); }
  if (VERBOSE)
    fprintf(stderr, "saving image %s\n", plotname);
  
  imFree(plot);
}

void plotlineFbw(FloatImage im1, int y, float minv, float maxv,
		 char *fname, int num, int plotheight,
		 int window, int peakw, int smaxpos, float smax)
{
  int width = imGetWidth(im1);
  GrayImage plot = (GrayImage)imNew(IMAGE_GRAY, width, plotheight);
  int x, k, v, vold;
  float val;
  char plotname[80];
 
  assert(plot);

  frame(plot, 0, window, peakw, smaxpos, smax);
  
  vold = (int)((imRef(im1, 0, y) - minv)*plotheight/(maxv-minv));
  vold=MIN(plotheight-1, MAX(0, vold));
  for (x=0; x<width; x++) {

    if (minv<0 && maxv > 0) /* draw zero line */
      imRef(plot, x, (int)(-minv*plotheight/(maxv-minv))) = GRAY;
    
    val = imRef(im1, x, y);
    v = (int)((val - minv)*plotheight/(maxv-minv));
    if (vold < v)
      for (k=vold; k<=v && k<plotheight; k++)
	imRef(plot, x, plotheight-1-k) = 0;
    else
      for (k=vold; k>=v && k>=0; k--)
	imRef(plot, x, plotheight-1-k) = 0;
    vold=MIN(plotheight-1, MAX(0, v));
  }
  sprintf(plotname, "%s.%d.pgm", fname, num);
  if (imSave(plot, plotname) < 0) {
    fprintf(stderr, "can't save image\n"); exit(1); }
  if (VERBOSE)
    fprintf(stderr, "saving image %s\n", plotname);
  
  imFree(plot);
}
