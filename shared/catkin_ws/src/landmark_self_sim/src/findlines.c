
/* findlines.c
 *
 * written by Sorin
 *
 * called by landmark.c
 */

static char rcsid[] = "$Id: findlines.c 6071 2015-10-16 21:58:31Z carrick $";


// #define IMAGE_CHECKALL

#include <stdio.h>
#include <math.h>
/*#include "misc.h"*/
#include "image.h"
#include "landmark.h"
#include "findlines.h"

#define imRefSafe(w, h, i, x, y) imRef((i), MIN((w)-1, MAX(0, (x))), MIN((h)-1,MAX(0, (y))))


    /* for n,  for x,  find "lines" up to 45 deg in matchIm
       for each line, call decode
       decode returns landm structure
       collect all those in landmark array


       it needs to call landm x = decode(im1, xt, yt, xb, yb);
    */
#define VERBOSE 0
#define SAVE_FILES 0

#define INFINITY 9999
#define MINSIZE 22
#define MAXTIGHT 1
#define ADJ_SMALL 10
#define ADJ_BIG   30



float sinu,cosu;
fpoint origin_new;


//prototypes
homogen SSM(int length, ipoint* lsm);

int interp(GrayImage a1, float hx, float hy);

int geti(GrayImage im1,int x,int y){
  return ((int)interp(im1, mapi(x,y).x, mapi(x,y).y));}

int getd(GrayImage im1,int x,int y){
  return ((int)interp(im1, mapd(x,y).x, mapd(x,y).y));}

fpoint mapi(int x, int y){
  fpoint theReturned;
  theReturned.x=origin_new.x+cosu*(x-origin_new.x)+sinu*(origin_new.y-y);
  theReturned.y=origin_new.y+sinu*(x-origin_new.x)-cosu*(origin_new.y-y);
  return(theReturned);}

fpoint mapd(int x, int y){
  fpoint theReturned;
  theReturned.x=origin_new.x+cosu*(x-origin_new.x)-sinu*(origin_new.y-y);
  theReturned.y=origin_new.y-sinu*(x-origin_new.x)-cosu*(origin_new.y-y);
  return(theReturned);}

int interp(GrayImage a1, float hx, float hy){
  float d1, d2, d3, d4;
  int width = imGetWidth(a1);
  int height = imGetHeight(a1);     
  if ((hx <= (width - 1)) && (hx >= 0)&&(hy >= 0) && (hy <= (height - 1))){
    if ((hx == (int) hx)&&(hy == (int) hy))
      return(imRefSafe(width, height, a1, (int) hx, (int) hy));
    else{
      d1 = 1/( sqrt(((hx - (int)(hx))*(hx- (int)(hx))) +
		      ((hy - (int)(hy))*(hy- (int)(hy)))));
      d2 = 1/( sqrt(((hx - (int)(hx))*(hx- (int)(hx))) +
		    ((- hy + 1+ (int)(hy))*(- hy + 1 + (int)(hy)))));
      d3 = 1/( sqrt(((- hx + 1 + (int)(hx))*(- hx +1 + (int)(hx))) +
		    ((hy - (int)(hy))*(hy- (int)(hy)))));
      d4 = 1/( sqrt(((- hx + 1 + (int)(hx))*(- hx + 1 + (int)(hx))) +
		      ((- hy + 1 + (int)(hy))*(- hy + 1 + (int)(hy)))));
      return((int)((d1 * imRefSafe(width, height, a1, (int)(hx), (int)(hy)) + 
	      d2 * imRefSafe(width, height, a1, (int)(hx), 1 + (int)(hy))+
	      d3 * imRefSafe(width, height, a1, 1 + (int)(hx), (int)(hy))+
	      d4 * imRefSafe(width, height, a1, 1 + (int)(hx), 1 + (int)(hy)))/
	     (d1 + d2 + d3 + d4)));}}
  else 
    return (0);}




homogen SSM(int n, ipoint* lsm) {

  double sum_xi = 0;
  double sum_yi = 0;
  double sum_tti = 0;
  double sum_tiyi = 0;

  double x_mean;
  homogen theReturned;

  int swap = 0; /* I'll set it to 1 if I swap the x and the y*/
  float m; /* the slope */
  double aa,bb;
  int i=0;

  m = ( lsm[0].x == lsm[n-1].x ) ? INFINITY : ABS( ((float)(lsm[0].y-lsm[n-1].y))/((float)(lsm[0].x - lsm[n-1].x)) );
  swap = ( m>1 ) ? 1 : 0;
  if (VERBOSE){
    if (swap)
      fprintf(stderr,"Swapping,  m = %f !\n",m);
    else
      fprintf(stderr,"Not swapping,  m = %f !\n",m);}

  if (swap){
    for (i=0; i<n; i++){
      int tmp;
      tmp  = lsm[i].x;
      lsm[i].x = lsm[i].y;
      lsm[i].y = tmp;}} /*end for*/
  

  for (i=0; i<n; i++){
    if (VERBOSE){
      fprintf(stderr,"In SSM: i=%d, (%d,%d) \
swap=%d\n",i,lsm[i].x,lsm[i].y, swap);}
    sum_xi += (double)lsm[i].x;
    sum_yi += (double)lsm[i].y;} /* end for*/

  x_mean = sum_xi/n;

  /*now I can compute the ti*/
  for (i=0; i<n; i++){
    sum_tti += ((lsm[i].x - x_mean)*(lsm[i].x - x_mean));
    sum_tiyi+= (lsm[i].x-x_mean)*lsm[i].y;}

  
  bb = sum_tiyi/sum_tti;
  aa = (sum_yi - sum_xi*bb)/n;
  /* remember y(x) = aa+bb*x, and we have to convert to the homogenous
   coordinates, ax+by+c=0 */

  theReturned._1 = bb;
  theReturned._2 = -1; /*!!!*/
  theReturned._3 = aa;


  /* if swap, we'll swap the a and the b*/
  if (swap){
    double tmp;
    tmp = theReturned._1;
    theReturned._1 = theReturned._2;
    theReturned._2 = tmp;}

  if (theReturned._1 < 0) {
      theReturned._1 = - theReturned._1;
      theReturned._2 = - theReturned._2;
      theReturned._3 = - theReturned._3;
  }

  if (swap){ /* SWAP BACK!!! */
    for (i=0; i<n; i++){
      int tmp;
      tmp  = lsm[i].x;
      lsm[i].x = lsm[i].y;
      lsm[i].y = tmp;}} /*end for*/
  
  if (VERBOSE)
    fprintf(stderr,"In SSM: a=%g, b=%g, c=%g! \n\n",
	    theReturned._1, theReturned._2,
	    theReturned._3 );
  return theReturned;} /* end SSM*/







landmarks findLines(FloatImage matchIm, GrayImage im1, int spacing) {
   int xl=0, yl=0;
   int x=0, y=0;
   landmarks result;
   int width, height, rheight;
   GrayImage match_bin;
   GrayImage tr_bin;
   ipoint *boundary;
   int length_boundary=0;
   int next_match=-1;
   homogen line;
   float tight=0;
   int i=0;
   int adj_big,adj_small;
   
   result.count=0;
   width = imGetWidth(im1);
   height = imGetHeight(im1);
   rheight = imGetHeight(matchIm);
   boundary = (ipoint*)malloc((width+rheight)*sizeof(ipoint));

   match_bin=(GrayImage)imNew(IMAGE_GRAY,width, rheight);
   tr_bin=(GrayImage)imNew(IMAGE_GRAY,width, height);
 
   //we transform the float image into a binary ne
   for (x=0;x<width;x++){
     for (y=0;y<rheight;y++){
       if (imRefSafe(width, rheight, matchIm,x,y)!=0){
	 imRefSafe(width, rheight, match_bin,x,y)=1;}
       else{
	 imRefSafe(width, rheight, match_bin,x,y)=0;}}}

   
   
   for (yl=0;yl<rheight-1;yl++){
     for (xl=0;xl<width;xl++){
	 y=yl;
	 x=xl;
	 tight = 0;
	 length_boundary = 0;
       if (imRefSafe(width, rheight, match_bin,x,y)==1){//a boundary is starting here
	 if (VERBOSE)
	   fprintf(stderr, "starting at %d, %d\n", x, y);
	 boundary[0].x=x;//record the x-value in boundary array
	 boundary[0].y=y;//record the y-value in boundary array
	 length_boundary++;//increase the length of the boundary
	 imRefSafe(width, rheight, match_bin,x,y)=255;//this match is deleted
	 do {
	   int xend = MIN(width,x+spacing+1);
	   x=MAX(x-spacing,0);
	   next_match=-1;
	   y=y+1;//go to next line
	   while ((x<xend)&&(imRefSafe(width, rheight, match_bin,x, y)!=1))
	     x++;
	   if (imRefSafe(width, rheight, match_bin,x, y)==1){
	     next_match=0;//a mach was found on the next line
	     boundary[length_boundary].x=x;
	     boundary[length_boundary].y=y;
	     length_boundary++;
	     imRefSafe(width, rheight, match_bin,x,y)=255;
	   }}
	 while 
	   ((y<rheight-1)&&(next_match==0));
	 if (length_boundary>MINSIZE/spacing){
	   if (VERBOSE)
	     fprintf(stderr, "long enough\n");
	   line=SSM(length_boundary,boundary);
	   if (VERBOSE)
	     fprintf(stderr,"In SSM: a=%g, b=%g, c=%g\n",
		     line._1,
		     line._2,
		     line._3);	     
	   for (i=0;i<length_boundary;i++){
	     float xx = -(line._3+line._2*boundary[i].y)/line._1;
	     float dd = ABS(boundary[i].x-xx);
	     if (VERBOSE)
	       fprintf(stderr, "x = %d, y=%d, line=%g, dist[%d] = %g\n",
		       boundary[i].x,boundary[i].y, xx, i, dd);
	     tight+= dd;
	   }
	   tight/=length_boundary;
	   if (VERBOSE)
	     fprintf(stderr, "tight = %g\n", tight);
	   if (tight<MAXTIGHT){
	     if (VERBOSE)
	       fprintf(stderr, "tight enough\n");
	     sinu=(line._2/sqrt(spacing*spacing*line._1*line._1+line._2*line._2));
	     cosu=(spacing*line._1/sqrt(spacing*spacing*line._1*line._1+line._2*line._2));
	     origin_new.x=(-1.0*(line._3+line._2*boundary[0].y)/line._1-1.0*(line._3+line._2*boundary[length_boundary-1].y)/line._1)/2.0;
	     origin_new.y=boundary[0].y*spacing+spacing/2+(boundary[length_boundary-1].y-boundary[0].y)*spacing/2.0;
	     

	   
	     if (VERBOSE)
	       fprintf(stderr,"In SSM: a=%g, b=%g, c=%g, sinu=%f, cosu=%f o.x=%d o.y=%d\n\n",
		     line._1,
		     line._2,
		     line._3,
		     sinu,
		     cosu,
		     (int)(origin_new.x),
		     (int)(origin_new.y));

	     if (sinu>0){
	       adj_small=ADJ_SMALL;
	       adj_big=ADJ_BIG;}
	     else{
	       adj_small=ADJ_BIG;
	       adj_big=ADJ_SMALL;}
	     
	  
	     if (VERBOSE) {
	       fprintf(stderr,"First x=%g ; y=%g\n",
		       mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).x,
		       mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).y
		       +sinu*adj_small);
	       fprintf(stderr,"Second x=%g ; y=%g\n",
		       mapd(boundary[length_boundary-1].x,
			   boundary[length_boundary-1].y*spacing+spacing/2).x,
		       mapd(boundary[length_boundary-1].x,
			    boundary[length_boundary-1].y*spacing
			    +spacing/2).y+sinu*adj_big);
	     
	       fprintf(stderr,"unadjusted First x=%g ; y=%g\n",
		       mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).x,
		      mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).y);
	       fprintf(stderr,"undajusted Second x=%g ; y=%g\n",
		       mapd(boundary[length_boundary-1].x,
			   boundary[length_boundary-1].y*spacing+spacing/2).x,
		       mapd(boundary[length_boundary-1].x,
			  boundary[length_boundary-1].y*spacing+spacing/2).y);
	     }

	     result.lm[result.count]=decode(im1,
		     mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).x,
		     mapd(boundary[0].x, boundary[0].y*spacing+spacing/2).y
					    +sinu*adj_small,
		     mapd(boundary[length_boundary-1].x,
			  boundary[length_boundary-1].y*spacing+spacing/2).x,
		     mapd(boundary[length_boundary-1].x,
			  boundary[length_boundary-1].y*spacing+spacing/2).y
					    +sinu*adj_big);

					    
	     result.count++;
	   
	   
	   }}
	 else {
	   if (VERBOSE)
	     fprintf(stderr, "not long enough (%d)\n", length_boundary);
	 }
	     
       }}}

   if (SAVE_FILES) {
     for (x=0;x<width;x++){
       for (y=0;y<height;y++){
	 imRef(tr_bin,x,y)=interp(im1,mapi(x,y).x, mapi(x,y).y);}}
   

     imSave(match_bin,"test.pgm");
     imSave(tr_bin,"tr.pgm");
   }
   /*   result.count = 0;*/
   
   return result;
}
