typedef struct intpoint {
  int x;
  int y;
} ipoint;

typedef struct floatpoint {
  float x;
  float y;
} fpoint;


typedef struct homogeneous2D {
  double _1;
  double _2;
  double _3;
} homogen;

fpoint mapi(int x, int y);
fpoint mapd(int x, int y);
landm decode(GrayImage im, int x1, int y1, int x2, int y2);
int geti(GrayImage im1,int x,int y);
int getd(GrayImage im1,int x,int y);
