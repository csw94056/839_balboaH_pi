Header header

# The x,y location of the top and bottom point of the detected landmark.
int32 xtop
int32 ytop
int32 xbottom
int32 ybottom

# Height of the landmark as computed as the distance between the top
# and bottom points.
float64 height

# The landmark code id number which should can range from 0 to 255.  If
# this is -1 then it means the code was not correctly read (and the
# above points may not be accurate).
int32 code
