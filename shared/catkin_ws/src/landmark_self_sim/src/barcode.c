
/* barcode.c
 *
 * written by Sorin
 *
 * new version from 3/8/99
 *
 * provides function decode()
 *
 * called by landmark.c
 */

static char rcsid[] = "$Id: barcode.c 6071 2015-10-16 21:58:31Z carrick $";

/* #define IMAGE_CHECKALL */

#include <stdio.h>
#include <math.h>
/*#include "misc.h"*/
#include "image.h"
#include "landmark.h"
#include "findlines.h"


#define VERBOSE 0
#define START_RANGE_DEFAULT 7

#define MINSIZE 20
#define NUMBITS 11

landm decode(GrayImage im, int x1, int y1, int x2, int y2){
    //  int width = imGetWidth(im);
  int height = imGetHeight(im);//the height of the immage
  int width = imGetWidth(im);//the height of the immage
  int x;//the starting x coordinate
  int i = 0,j = 0;//contours
  int black = 257, white = -1;//used to measure how many items are black and white
  int sum1 = 0, sum2 = 0;
  int max = 0,cut = 1;
  int wrong=0, check=0;
  int range,k, fact;
  int startrange;
  int start, end;
  int vec[NUMBITS];
  int position1, position2;
  long total=0;
  int xlim=0;
  float val, closest=100;
  int code =0, godown=-5, ylimup=0, ylimdown=0, ytextdown=0, ytextup=0;
  float power=-2;//small if think endpoints are correct, big otherwise

  landm result;
  fpoint pt;
  
  if (y2-y1 < MINSIZE) {
      result.code = -2;
      return result;//if image is too small
  }
  
  fact = (y2-y1)/NUMBITS;//fact is the size of a bit
  startrange = fact/START_RANGE_DEFAULT;  

  if (x1<x2)// get a common x value
    x = x1;
  else
    x = x2;
  if (x+startrange+fact>width){//the barcode is hardly visible
      result.code = -2;
      return result;
  }
  //this code determines the limit of barcode on the right
  max=0;
  sum2=0;
  for (j=0;j<fact;j++){
    sum2=sum2 + geti(im,x+startrange,y1+j);}//initialization sum up-down
  for (i=startrange;i<MIN(2*fact,width-x-1);i++){//go to the right two bits
    sum1=sum2;
    sum2=0;
    for (j=0;j<fact;j++){
      sum2 = sum2 + geti(im,x+i+1,y1+j);}
    if ((sum2-sum1)>max){//if difference is big, i.e. end of barcode, set xlim 
      max = sum2-sum1;
      xlim = x+i+2;}}
 
  //this code finds a better approximation for the endpoints y1 and y2,
  //using the right hand side, that is the barcode

  //this finds the upper limit
  godown=(int)power*fact;
  max = 0;
  sum2=0;
  for (j=0;j<xlim-x;j++){
    sum2=sum2 + geti(im,x+j,MIN(y1-godown,height-1));}		/*** changed */
  for (i=godown;i<(int)(-power*fact);i++){
    sum1=sum2;
    sum2=0;
    if ((y1-i-1>=0)&&(y1-i-1<height)){//not outside of the image
      for (j=0;j<xlim-x;j++){
	sum2 = sum2 + geti(im,x+j,y1-i-1);}
      if ((sum2-sum1)>max){
	max = sum2-sum1;
	ylimup = y1-i-1;}}}
  //this finds the lower limit
  max=0;
  sum2=0;
  for (j=0;j<xlim-x;j++){
    sum2=sum2 + geti(im,x+j,MIN(y2-godown,height-1));}		/*** changed */
  for (i=godown;i<(int)(-power*fact);i++){
    sum1=sum2;
    sum2=0;
    if ((y2-i-1>=0)&&(y2-i-1<height)){
      for (j=0;j<xlim-x;j++){
	sum2 = sum2 + geti(im,x+j,y2-i-1);}
     // fprintf(stderr,"%d: %d\n",MIN(height-1, y2-i-1), sum2);
      if ((sum1-sum2)>max){
	max = sum1-sum2;
	ylimdown = y2-i-1;}}}

  //this code finds a better approximation for the endpoints y1 and y2,
  //using the left hand side, that is the sinusoidal texture

  //this finds the upper texture limit
  max =0;
  sum2=0;
  for (j=0;j>-fact;j--){
    sum2=sum2 + geti(im,x+j,MIN(y1-godown,height-1));}		/*** changed */
  for (i=godown;i<(int)(-power*fact);i++){
    sum1=sum2;
    sum2=0;
    if ((y1-i-1>=0)&&(y1-i-1<height)){
      for (j=0;j>-fact;j--){
	sum2 = sum2 + geti(im,x+j,y1-i-1);}
      // fprintf(stderr,"Texture: %d: %d\n",y1-i-1, sum2);
      if ((sum2-sum1)>max){
	max = sum2-sum1;
	ytextup = y1-i-1;}}}

  //this finds the lower texture limit
  max=0;
  sum2=0;
  for (j=0;j>-fact;j--){
    sum2=sum2 + geti(im,x+j,MIN(y2-godown,height-1));}		/*** changed */
  for (i=godown;i<(int)(-power*fact);i++){
    sum1=sum2;
    sum2=0;
    if ((y2-i-1>=0)&&(y2-i-1<height)){
      for (j=0;j>-fact;j--){
	sum2 = sum2 + geti(im,x+j,y2-i-1);}
      if ((sum1-sum2)>max){
	max = sum1-sum2;
	ytextdown = y2-i-1;}}}

  
   
  if (VERBOSE) {
    fprintf(stderr,"\n From %d,%d to %d,%d\n ",x1,y1,x2,y2);
    fprintf(stderr,"Limit: x = %d, y_up = %d y_textup = %d y_down = %d ytextdown = %d\n", xlim, ylimup,ytextup, ylimdown, ytextdown);
  }
  
  //     y1=(ylimup+ytextup)/2;
  //     y2=(ylimdown+ytextdown)/2;

  //so we get the limits given by the left hand side, the texture
  //  y1= ylimup;
  y1= ytextup;
  //  y2= ylimdown;
  y2= ytextdown;

  pt = mapi(x1, y1);
  result.xtop = pt.x;
  result.ytop = pt.y;
  pt = mapi(x2, y2);
  result.xbottom = pt.x;
  result.ybottom = pt.y;
  
  range = ROUND((cut-1)*(xlim -x)/(2.0*cut)); 
  start = x+range;
  end = xlim-range;// how much we go to the right from left
  if (VERBOSE)
    fprintf(stderr, "start %d end %d\n", start, end);
  range = end - start;
  position2=y1-1;
  for (i=1; i<=NUMBITS; i++){
    position1 = position2+1;
    position2 = y1 + ROUND((y2-y1)*i/(float)NUMBITS);
    total=0;
    j = y1 + ROUND((y2-y1)*(i-.5)/((float)NUMBITS));
    if (VERBOSE)
      fprintf(stderr, "%d:pos %d  ", i, j);
    for (k=start; k<end; k++){
      total = total + geti(im,k, j);}
    vec[i-1]=ROUND(total/((float)(end-start)));
    if (VERBOSE)
      fprintf(stderr, "%d:%d\n",i, vec[i-1]);
   }
  if (VERBOSE)
    fprintf(stderr, "\n");
  
  for (i=0; i<NUMBITS; i++){
    if (vec[i]<black){
      black = vec[i];}
    if (vec[i]>white){
      white = vec[i];}}
  if (VERBOSE)
    fprintf(stderr, "black = %d, white = %d, mid=%d\n", black, white,
	    (black+white)/2);
  for (i=0; i<NUMBITS; i++){
    val = 1.0*(vec[i]-black)/(white-black);
    if (ABS(val-0.5)<closest){
      closest = ABS(val-0.5);
      wrong = i;}
    if ((vec[i]-black)<(white-vec[i])) {
      if (VERBOSE)
	fprintf(stderr, "%d:%d B  ", i, vec[i]);
      vec[i]=1;
    } else {
        if (VERBOSE)
	  fprintf(stderr, "%d:%d W  ", i, vec[i]);
	vec[i]=0;
    }
  }
  if (VERBOSE) {
    fprintf(stderr, "\n");
    fprintf(stderr,"Barcode: ");
    for (i=0; i<NUMBITS; i++){
      fprintf(stderr, "%d", vec[i]);}
    fprintf(stderr,"\n");
  }
  check =0;
  for (i=1; i<NUMBITS-2; i++){
    if (vec[i]==1)
      check = 1-check;}
  
  if (check!=vec[NUMBITS-2]){
    result.code = -1;
    return result ;/* don't correct for now */
    if (VERBOSE)
      fprintf(stderr,"error adjustment at i = %d\n",wrong);
    vec[wrong]=1-vec[wrong];
  }

  if (vec[0]==0 || vec[NUMBITS-1]==0) {
      result.code = -1;
      return result;
  }
  
  for (i=1; i<NUMBITS-2;i++){
    code =(code*2)+vec[i];}

  result.code = code;
  return result;
}
