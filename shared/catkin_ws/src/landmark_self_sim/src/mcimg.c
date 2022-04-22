/* mcimg.c *
 * providing fuctions for images *
 * by Dianel Scharstein and Huan Ding */
   
#include "mcimg.h"

static char errStr[100];
void mcerr(char *why, char *msg, int line, char *file,int die) {
  fprintf(stderr, "\n%s:   %s\n", why, msg);
  fprintf(stderr, "%*s    In line %d of %s\n", strlen(why), "", line, file);
  if (die) exit(0);
}

void skip_comment(FILE *fp){
  char c;
  while ((c=getc(fp))=='#')
    while(getc(fp)!='\n');
  ungetc(c,fp);
}
void skip_space(FILE *fp){
  char c;
  do{
    c=getc(fp);
  }while(c=='\n'||c==' '||c=='\t'||c=='\r'); 
  ungetc(c,fp);
}

/* GrayImage functions */
GrayImage _newGrayImage(int width,int height,int assert){
  GrayImage img;
  register int x;

  if(width<=0||height<=0){
    if(!assert)  return ((GrayImage)NULL);
    sprintf(errStr,"Image bounds check failure: %d >0, %d>0",width,height);
    assertfail(errStr);
    
  }
  img=(GrayImage)malloc(sizeof(struct GrayImStruct));
  img->data=(uchar**)malloc(height*sizeof(uchar *));
  *img->data = (uchar*)calloc(width*height,sizeof(uchar));
  if (img->data == NULL||*img->data==NULL) {
    free(img);
    if(!assert)   return ((GrayImage)NULL);
    sprintf(errStr,"Not enough memory");
    assertfail(errStr);
  }
  for (x=0;x<height;x++){
    img->data[x]=&((*img->data)[x*width]);
  }
    
  img->type=_GRAY;
  img->width=width;
  img->height=height;
  return (img);	      
}

GrayImage _loadGrayImageF(FILE *fp,int assert){
  GrayImage img;
  int width,height,tmp;
  char c;

  if(getc(fp)!='P'||getc(fp)!='5'){
    if(!assert)   exit(-1);
    sprintf(errStr,"Wrong format.");
    assertfail(errStr);
  }
  skip_space(fp);
  skip_comment(fp);
  skip_space(fp);
  fscanf(fp,"%d",&width);
  skip_space(fp);
  fscanf(fp,"%d",&height);
  img=newGrayImage(width,height);
  skip_space(fp);
  fscanf(fp,"%d",&tmp);
  if((c=getc(fp))!='\n')
    ungetc(c,fp);
  fread(*(img->data),sizeof(uchar),width*height,fp);
  return img;
}

GrayImage _loadGrayImage(char *filename,int assert){
  FILE *fp;
  GrayImage img;
  if((fp=fopen(filename,"r"))==(FILE*)NULL){
    if(!assert) exit(-1);
    sprintf(errStr,"Error opening input file %s",filename);
    assertfail(errStr);
  } 
  img=_loadGrayImageF(fp,assert);
  fclose(fp);
  return img;
}

int _saveGrayImageF(GrayImage img, FILE *fp,int assert){
  fprintf(fp,"P5\n%d %d\n%d\n",img->width,img->height,255);
  if((int)fwrite(*img->data,sizeof(uchar),img->width*img->height,fp)!=img->width*img->height){
    if(!assert)  return(-1);
    sprintf(errStr,"Error writing output file");
    assertfail(errStr);
  }
  return 0;
}

int _saveGrayImage(GrayImage img, char *filename,int assert){
  FILE *fp;
  int result;
  if (filename==NULL)
    fp=stdout;
  else if((fp=fopen(filename,"w"))==(FILE*)NULL){
    if(!assert)  exit(-1);
    sprintf(errStr,"Error opening output file %s",filename);
    assertfail(errStr);
  }
  result=_saveGrayImageF(img,fp,assert);
  fclose(fp);
  return result;
}

/* RGBImage function*/
RGBImage _newRGBImage(int width,int height,int assert){
  RGBImage img;
  register int x;

  if(width<=0||height<=0){
    if(!assert) return ((RGBImage)NULL);
    sprintf(errStr,"Image bounds check failure: %d >0, %d>0",width,height);
    assertfail(errStr);
  }
  img=(RGBImage)malloc(sizeof(struct RGBImStruct));
  img->data=(RGB**)malloc(height*sizeof(RGB *));
  *img->data = (RGB*)calloc(width*height,sizeof(RGB));
  if (img->data==NULL||*img->data==NULL) {
    free(img);
    if(!assert) return ((RGBImage)NULL);
    sprintf(errStr,"Not enough memory");
    assertfail(errStr);
  }
  for (x=0;x<height;x++){
    img->data[x]=&((*img->data)[x*width]);
  }
    
  img->type=_RGB;
  img->width=width;
  img->height=height;
  return (img);
}
RGBImage _loadRGBImageF(FILE *fp,int assert){
  RGBImage img;
  int width,height,tmp;
  char c;

  if(getc(fp)!='P'||getc(fp)!='6'){
    if(!assert) exit(-1);
    sprintf(errStr,"Wrong format.");
    assertfail(errStr);
  }
  skip_space(fp);
  skip_comment(fp);
  skip_space(fp);
  fscanf(fp,"%d",&width);
  skip_space(fp);
  fscanf(fp,"%d",&height);
  img=newRGBImage(width,height);
  skip_space(fp);
  fscanf(fp,"%d",&tmp);
  if((c=getc(fp))!='\n')
    ungetc(c,fp);
  fread(*(img->data),sizeof(RGB),width*height,fp);
  return img;
}
RGBImage _loadRGBImage(char *filename,int assert){
  FILE *fp;
  RGBImage img;
  if((fp=fopen(filename,"r"))==(FILE*)NULL){
    if(!assert) exit(-1);
    sprintf(errStr,"Error opening input file %s",filename);
    assertfail(errStr);
  } 
  img=_loadRGBImageF(fp,assert);
  fclose(fp);
  return img;
}

int _saveRGBImageF(RGBImage img, FILE *fp,int assert){
  fprintf(fp,"P6\n%d %d\n%d\n",img->width,img->height,255);
  if((int)fwrite(*img->data,sizeof(RGB),img->width*img->height,fp)!=img->width*img->height){
    if(!assert) return(-1);
    sprintf(errStr,"Error writing output file");
    assertfail(errStr);
  }
  return 0;
}

int _saveRGBImage(RGBImage img, char *filename,int assert){
  FILE *fp;
  int result;
  if (filename==NULL)
    fp=stdout;
  else if((fp=fopen(filename,"w"))==(FILE*)NULL){
     if(!assert) exit(-1);
     sprintf(errStr,"Error opening output file %s",filename);
     assertfail(errStr);
  }
  result= _saveRGBImageF(img,fp,assert);
  fclose(fp);
  return result;
}

/* BinaryImage function */
BinaryImage _newBinaryImage(int width,int height,int assert){
  BinaryImage img;
  register int x;

  if(width<=0||height<=0){
    if(!assert)   return ((BinaryImage)NULL);
    sprintf(errStr,"Image bounds check failure: %d >0, %d>0",width,height);
    assertfail(errStr);
   }
  img=(BinaryImage)malloc(sizeof(struct BinaryImStruct));
  img->data=(uchar**)malloc(height*sizeof(uchar *));
  *img->data = (uchar*)calloc(width*height,sizeof(uchar));
  if (img->data == NULL||*img->data==NULL) {
    free(img);
    if(!assert) return ((BinaryImage)NULL);
    sprintf(errStr,"Not enough memory");
    assertfail(errStr);    
  }
  for (x=0;x<height;x++){
    img->data[x]=&((*img->data)[x*width]);
  }
    
  img->type=_BINARY;
  img->width=width;
  img->height=height;
  return (img);	      
}
BinaryImage _loadBinaryImageF(FILE *fp,int assert){
  BinaryImage img;
  int width,height,tmp,zwidth;
  register int x,y;
  char c;
  uchar *data;

  if(getc(fp)!='P'||getc(fp)!='4'){
    if(!assert) exit(-1);
    sprintf(errStr,"Wrong format.");
    assertfail(errStr);
  }
  skip_space(fp);
  skip_comment(fp);
  skip_space(fp);
  fscanf(fp,"%d",&width);
  skip_space(fp);
  fscanf(fp,"%d",&height);
  skip_space(fp);
  img=newBinaryImage(width,height);
  if((c=getc(fp))!='\n')
    ungetc(c,fp);
  zwidth=(width+7)/8;
  tmp=zwidth*height;
  if((data=malloc(tmp*sizeof(uchar)))==NULL){
     if(!assert) exit(-1);
     sprintf(errStr,"Not enough memory");
     assertfail(errStr);
  }
  fread(data,sizeof(uchar),tmp,fp);
  for(y=0;y<img->height;y++){
    uchar* dataptr=img->data[y];
    int zpos=y*zwidth;
    for(x=0;x<img->width;x++){
      int x1=x/8;
      int x2=7+x1*8-x;
      c=data[zpos+x1];
      c>>=x2;
      dataptr[x]=c&1;
    }
  }
  free(data);
  return img;
}
BinaryImage _loadBinaryImage(char *filename,int assert){
  FILE *fp;
  BinaryImage img;
  if((fp=fopen(filename,"r"))==(FILE*)NULL){
    if(!assert)  exit(-1);
    sprintf(errStr,"Error opening input file %s",filename);
    assertfail(errStr);
  } 
  img= (_loadBinaryImageF(fp,assert));
  fclose(fp);
  return img;
}

int _saveBinaryImageF(BinaryImage img, FILE *fp,int assert){
  uchar *data;
  int tmp,zwidth;
  register int x,y;

  zwidth=(img->width+7)/8;
  tmp=zwidth*img->height;
  if((data=calloc(tmp,sizeof(uchar)))==NULL){
     if(!assert) exit(-1);
     sprintf(errStr,"Not enough memory");
     assertfail(errStr);
  }

  for(y=0;y<img->height;y++){
    uchar* dataptr=img->data[y];
    int zpos= zwidth*y;
    for(x=0;x<img->width;x++){
      int x1=x/8;
      int x2=7+x1*8-x;
      uchar c=dataptr[x];
      c<<=x2;
      data[zpos+x1]|=c;
    }
  }   
    
  fprintf(fp,"P4\n%d %d\n",img->width,img->height);
  if((int)fwrite(data,sizeof(uchar),tmp,fp)!=tmp){
    if(!assert) return(-1);
    sprintf(errStr,"Error writing output file");
    assertfail(errStr);
  }
  free(data);
  return 0;
}

int _saveBinaryImage(BinaryImage img, char *filename,int assert){
  FILE *fp;
  int result;
  if (filename==NULL)
    fp=stdout;
  else if((fp=fopen(filename,"w"))==(FILE*)NULL){
     if(!assert) exit(-1);
     sprintf(errStr,"Error opening output file %s",filename);
     assertfail(errStr);
  }
  result= _saveBinaryImageF(img,fp,assert);
  fclose(fp);
  return result;
}

/* FloatImage function */
FloatImage _newFloatImage(int width,int height,int assert){
  FloatImage img;
  register int x;

  if(width<=0||height<=0){
     if(!assert) return ((FloatImage)NULL);
     sprintf(errStr,"Image bounds check failure: %d >0, %d>0",width,height);
     assertfail(errStr);
   }
  img=(FloatImage)malloc(sizeof(struct FloatImStruct));
  img->data=(float**)malloc(height*sizeof(float *));
  *img->data = (float*)calloc(width*height,sizeof(float));
  if (img->data == NULL||*img->data==NULL) {
    free(img);
    if(!assert) return ((FloatImage)NULL);
    sprintf(errStr,"Not enough memory");
    assertfail(errStr);
  }
  for (x=0;x<height;x++){
    img->data[x]=&((*img->data)[x*width]);
  }
    
  img->type=_FLOAT;
  img->width=width;
  img->height=height;
  return (img);	      
}


FloatImage _loadFloatImageF(FILE *fp,int assert){
  FloatImage img;
  int width,height;
  char c;

  if(getc(fp)!='Q'||getc(fp)!='1'){
    if(!assert) exit(-1);
    sprintf(errStr,"Wrong format.");
    assertfail(errStr);
  }
  skip_space(fp);
  skip_comment(fp);
  skip_space(fp);
  fscanf(fp,"%d",&width);
  skip_space(fp);
  fscanf(fp,"%d",&height);
  img=newFloatImage(width,height);
  if((c=getc(fp))!='\n')
    ungetc(c,fp);
  fread(*(img->data),sizeof(float),width*height,fp);
  return img;
}

FloatImage _loadFloatImage(char *filename,int assert){
  FILE *fp;
  FloatImage img;
  if((fp=fopen(filename,"r"))==(FILE*)NULL){
    if(!assert) exit(-1);
    sprintf(errStr,"Error opening input file %s",filename);
    assertfail(errStr);
  } 
  img=_loadFloatImageF(fp,assert);
  fclose(fp);
  return img;
}

int _saveFloatImageF(FloatImage img, FILE *fp,int assert){
  fprintf(fp,"Q1\n%d %d\n",img->width,img->height);
  if((int)fwrite(*img->data,sizeof(float),img->width*img->height,fp)!=img->width*img->height){
    if(!assert) return(-1);
    sprintf(errStr,"Error writing output file");
    assertfail(errStr);
  }
  return 0;
}

int _saveFloatImage(FloatImage img, char *filename,int assert){
  FILE *fp;
  int result;
  if (filename==NULL)
    fp=stdout;
  else if((fp=fopen(filename,"w"))==(FILE*)NULL){
    if(!assert) exit(-1);
    sprintf(errStr,"Error opening output file %s",filename);
    assertfail(errStr);
  }
  result= _saveFloatImageF(img,fp,assert);
  fclose(fp);
  return result;
}
