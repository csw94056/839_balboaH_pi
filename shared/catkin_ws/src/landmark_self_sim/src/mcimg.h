/* mcimg.h ver 1.00
 * Header file for images 
 * author: Dianel Scharsten and Huan Ding 
 * 6/21/99 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "misc.h"

typedef unsigned char uchar;
typedef enum {
  _GRAY,
  _RGB,
  _BINARY,
  _FLOAT,
} McImType;
typedef struct {uchar r,g,b;} RGB;
typedef struct GrayImStruct {
  McImType type;
  int width,height;
  uchar **data;
} * GrayImage;
typedef struct RGBImStruct{
  McImType type;
  int width,height;
  RGB **data;
}* RGBImage;
typedef struct BinaryImStruct{
  McImType type;
  int width,height;
  uchar **data;
} *BinaryImage;
typedef struct FloatImStruct{
  McImType type;
  int width,height;
  float **data;
} *FloatImage;

#define imGetWidth(i) ((i)->width)
#define imGetHeight(i) ((i)->height)
#define imGetType(i) ((i)->type)

#define imFree(i) { free(*(i)->data);free((i)->data);free(i);}

void mcerr(char *why, char *msg, int line, char *file,int die);
#define assertfail(msg)  mcerr("Assert failure", (msg), __LINE__, __FILE__,1)
#define	eassert(x)	(!(x) ? (assertfail("!(" #x ")"), 0) : 0)

#ifndef	IMAGE_CHECKALL
#define imRef(i, x, y) ((i)->data[y][x])
#else
static char imStr[100];
#define	imRef(i, x, y)	(eassert(i != NULL), \
 ((x) < 0 || (y) < 0 || (x) >= imGetWidth(i) || (y) >= imGetHeight(i) ? \
 ({sprintf(imStr, "Image bounds check failure: " \
 "0 <= %d < %d, 0 <= %d < %d", (x), imGetWidth(i), (y), imGetHeight(i)); \
			       assertfail(imStr);}), \
  ((i)->data[0][0]) : ((i)->data[y][x])))
#endif

#ifndef IMAGE_CHECKALL
#define newGrayImage(w,d) _newGrayImage(w,d,0)
#define loadGrayImage(n) _loadGrayImage(n,0)
#define loadGrayImageF(n) _loadGrayImageF(n,0)
#define saveGrayImage(i,n) _saveGrayImage(i,n,0)
#define saveGrayImageF(i,n) _saveGrayImageF(i,n,0)

#define newRGBImage(w,d) _newRGBImage(w,d,0)
#define loadRGBImage(n) _loadRGBImage(n,0)
#define loadRGBImageF(n) _loadRGBImageF(n,0)
#define saveRGBImage(i,n) _saveRGBImage(i,n,0)
#define saveRGBImageF(i,n) _saveRGBImageF(i,n,0)

#define newBinaryImage(w,d) _newBinaryImage(w,d,0)
#define loadBinaryImage(n) _loadBinaryImage(n,0)
#define loadBinaryImageF(n) _loadBinaryImageF(n,0)
#define saveBinaryImage(i,n) _saveBinaryImage(i,n,0)
#define saveBinaryImageF(i,n) _saveBinaryImageF(i,n,0)

#define newFloatImage(w,d) _newFloatImage(w,d,0)
#define loadFloatImage(n) _loadFloatImage(n,0)
#define loadFloatImageF(n) _loadFloatImageF(n,0)
#define saveFloatImage(i,n) _saveFloatImage(i,n,0)
#define saveFloatImageF(i,n) _saveFloatImageF(i,n,0)
#else 
#define newGrayImage(w,d) _newGrayImage(w,d,1)
#define loadGrayImage(n) _loadGrayImage(n,1)
#define loadGrayImageF(n) _loadGrayImageF(n,1)
#define saveGrayImage(i,n) _saveGrayImage(i,n,1)
#define saveGrayImageF(i,n) _saveGrayImageF(i,n,1)

#define newRGBImage(w,d) _newRGBImage(w,d,1)
#define loadRGBImage(n) _loadRGBImage(n,1)
#define loadRGBImageF(n) _loadRGBImageF(n,1)
#define saveRGBImage(i,n) _saveRGBImage(i,n,1)
#define saveRGBImageF(i,n) _saveRGBImageF(i,n,1)

#define newBinaryImage(w,d) _newBinaryImage(w,d,1)
#define loadBinaryImage(n) _loadBinaryImage(n,1)
#define loadBinaryImageF(n) _loadBinaryImageF(n,1)
#define saveBinaryImage(i,n) _saveBinaryImage(i,n,1)
#define saveBinaryImageF(i,n) _saveBinaryImageF(i,n,1)

#define newFloatImage(w,d) _newFloatImage(w,d,1)
#define loadFloatImage(n) _loadFloatImage(n,1)
#define loadFloatImageF(n) _loadFloatImageF(n,1)
#define saveFloatImage(i,n) _saveFloatImage(i,n,1)
#define saveFloatImageF(i,n) _saveFloatImageF(i,n,1)
#endif

GrayImage _newGrayImage(int width, int height, int assert);
GrayImage _loadGrayImage(char *filename,int assert);
GrayImage _loadGrayImageF(FILE *fp,int assert);
int _saveGrayImage(GrayImage img, char *filename,int assert);
int _saveGrayImageF(GrayImage img, FILE *fp,int assert);

RGBImage _newRGBImage(int width,int height,int assert);
RGBImage _loadRGBImage(char *filename,int assert);
RGBImage _loadRGBImageF(FILE *fp,int assert);
int _saveRGBImage(RGBImage img,char *filename,int assert);
int _saveRGBImageF(RGBImage img, FILE *fp,int assert);

BinaryImage _newBinaryImage(int width, int height,int assert);
BinaryImage _loadBinaryImage(char *filename,int assert);
BinaryImage _loadBinaryImageF(FILE *fp,int assert);
int _saveBinaryImage(BinaryImage img, char *filename,int assert);
int _saveBinaryImageF(BinaryImage img, FILE *fp,int assert);

FloatImage _newFloatImage(int width,int height,int assert);
FloatImage _loadFloatImage(char *filename,int assert);
FloatImage _loadFloatImageF(FILE *fp,int assert);
int _saveFloatImage(FloatImage img,char *filename,int assert);
int _saveFloatImageF(FloatImage img, FILE *fp,int assert);
