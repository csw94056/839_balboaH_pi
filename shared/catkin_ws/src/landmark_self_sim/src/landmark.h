
/* landmark.h  6/16/99   Daniel Scharstein
 */
   
typedef struct {
  int xtop;
  int ytop;
  int xbottom;
  int ybottom;
  int code;
} landm;

typedef struct {
  landm lm[100];
  int count;
} landmarks;

#define FACTOR_DEFAULT	   3.0
#define WINDOW_DEFAULT	   45
#define SPACING_DEFAULT	   6
#define THRESHOLD_DEFAULT  25
#define SKIP_DEFAULT       5

#define PEAKW_PERCENT	   10 /* peakw as percentage of window size */
#define PEAKW_ADD	   2  /* number to add to peakw */
#define PEAKW_DEFAULT      ((PEAKW_PERCENT*WINDOW_DEFAULT)/100 + PEAKW_ADD)

landmarks landmark(GrayImage im1, char *outImName, int verbose, int drawX);

landmarks landmarkParams(GrayImage im1, char *outImName,
			 int verbose, int drawX, int window, int peakw,
			 int threshold, double factor,  int spacing,
			 int skip,  int ycoord);
