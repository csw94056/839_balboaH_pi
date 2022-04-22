/* findlm.c  Daniel Scharstein  6/16/99 */

/* driver for landmark program
 */

static char rcsid[] = "$Id: findlm.c 6071 2015-10-16 21:58:31Z carrick $";

#include <stdio.h>
#include <math.h>
#include "image.h"
#include "landmark.h"


static char usage[] = "\n\
usage: %s [options] img.pgm\n\
\n\
  search for landmark in img.pgm\n\
\n\
        OPTIONS							DEFAULTS\n\
	-f factor	self-similarity factor			%g\n\
	-s spacing	spacing of scanlines to search		%d\n\
	-w window	size of search window		        %d\n\
	-t threshold	threshold for match			%d\n\
	-p peak width	max peakw at .5 max (percent of window) %d\n\
	-h hold 	number of pixels to skip		%d\n\
	-y ycoord	search single scanline at ycoord	-\n\
	-x		draw X at match (line otherwise)	 \n\
	-v		verbose					 \n\
\n\
    good params for -f 2:  -t 40, -p 6 \n\
    ok params for -f 4:  -t 20, -p 6 \n\
";

int main(int argc, char **argv)
{
  int o, i;
  GrayImage im1;
  char *im1name;
  landmarks lamarr;
  
  double factor = FACTOR_DEFAULT;
  int spacing = SPACING_DEFAULT;
  int window = WINDOW_DEFAULT;
  int threshold = THRESHOLD_DEFAULT;
  int peakperc = PEAKW_PERCENT;
  int skip = SKIP_DEFAULT;
  int ycoord = -1;
  int drawX = 0;
  int verbose = 0;
  int peakw;
  
  while ((o = getopt(argc, argv, "f:s:w:t:p:h:y:xv")) != -1)
    switch (o) {
    case 'f': factor = atof(optarg); break;
    case 's': spacing = atoi(optarg); break;
    case 'w': window = atoi(optarg); break;
    case 't': threshold = atoi(optarg); break;
    case 'p': peakperc = atoi(optarg); break;
    case 'h': skip = atoi(optarg); break;
    case 'y': ycoord = atoi(optarg); /* fall through to drawX=1 */
    case 'x': drawX = 1; break;
    case 'v': verbose = 1; break;
    default:
      fprintf(stderr, "Unrecognized option %c\n", o);
    }

  if (optind >= argc) {
    fprintf(stderr, usage, argv[0], FACTOR_DEFAULT,
	    SPACING_DEFAULT, WINDOW_DEFAULT, THRESHOLD_DEFAULT,
	    PEAKW_DEFAULT, SKIP_DEFAULT);
    exit(1);
  }

  im1name = argv[optind];
  
  im1 = (GrayImage)imLoad(IMAGE_GRAY, im1name);
  if (im1 == (GrayImage)NULL) {
    fprintf(stderr, "can't load image %s\n", im1name); exit(1); }

  peakw = (peakperc * window) / 100 + PEAKW_ADD;


  lamarr = landmarkParams(im1, "out.match.ppm", verbose, drawX,
			     window, peakw, threshold,
			     factor, spacing, skip, ycoord);

  for (i=0; i<lamarr.count; i++) {
    landm lam = lamarr.lm[i];
    fprintf(stderr, "found at %3d,%3d to %d,%d - code = %d\n",
	    lam.xtop, lam.ytop, lam.xbottom, lam.ybottom, lam.code);
  }

  assert(rcsid); /* to avoid warning message */
  return(0);
}
