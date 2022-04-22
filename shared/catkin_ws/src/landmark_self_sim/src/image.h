/* image.h      ver 1.00
 * This file is to make compatible with the previous versons of image 
 * libraries 
 * written by Dianel Scharstein and Huan Ding
 * 6/21/99 */

#include <getopt.h>
#include "mcimg.h"			    

typedef unsigned short ImageType;
/* The image types */
#define	IMAGE_GRAY	((ImageType) (1 <<  0))
#define	IMAGE_FLOAT	((ImageType) (1 <<  1))
#define	IMAGE_RGB	((ImageType) (1 <<  2))
#define	IMAGE_BINARY	((ImageType) (1 <<  4))
#define IMAGE_ANY       (IMAGE_GRAY|IMAGE_FLOAT|IMAGE_RGB|IMAGE_BINARY)


#define imNew(i,x,y) ((i)==IMAGE_GRAY ? (void *)newGrayImage((x),(y)) : \
          ((i)==IMAGE_RGB ? (void *)newRGBImage((x),(y)) : \
          ((i)==IMAGE_BINARY ? (void *)newBinaryImage((x),(y)):\
          ((i)==IMAGE_FLOAT ? (void *)newFloatImage((x),(y)): NULL))))
#define imLoad(i,n) ((i)==IMAGE_GRAY ? (void *)loadGrayImage(n) : \
                    ((i)==IMAGE_RGB ? (void *)loadRGBImage(n):\
                    ((i)==IMAGE_BINARY ? (void *)loadBinaryImage(n):\
                    ((i)==IMAGE_FLOAT ? (void *)loadFloatImage(n):NULL))))
#define imLoadF(i,n) ((i)==IMAGE_GRAY ? (void *)loadGrayImageF(n) : \
                     ((i)==IMAGE_RGB ? (void *)loadRGBImageF(n):\
                     ((i)==IMAGE_BINARY ? (void *)loadBinaryImageF(n):\
                     ((i)==IMAGE_FLOAT ? (void *)loadFloatImageF(n): NULL))))
#define imSave(i,n) (imGetType(i)==_GRAY ? saveGrayImage((GrayImage)(i),(n)):\
   (imGetType(i)==_RGB ? saveRGBImage((RGBImage)(i),(n)) : \
   (imGetType(i)==_BINARY ? saveBinaryImage((BinaryImage)(i),(n)) : \
   (imGetType(i)==_FLOAT ? saveFloatImage((FloatImage)(i),(n)): -1))))
#define imSaveF(i,n) (imGetType(i)==_GRAY?saveGrayImageF((GrayImage)(i),(n)):\
   (imGetType(i)==_RGB ? saveRGBImageF((RGBImage)(i),(n)) : \
   (imGetType(i)==_BINARY ? saveBinaryImageF((BinaryImage)(i),(n)) : \
   (imGetType(i)==_FLOAT ? saveFloatImageF((FloatImage)(i),(n)): -1))))

 
