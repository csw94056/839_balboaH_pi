/****************************************************************************
*
*   Copyright (c) 2011 Carrick Detweiler
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
******************************************************************************/

#include <ros/ros.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

extern "C" {
  //#define	IMAGE_CHECKALL
#include "image.h"
#include "landmark.h"
}

namespace enc = sensor_msgs::image_encodings;

class LandmarkDetector{
public:
  LandmarkDetector();
  ~LandmarkDetector(){
  }
private:
  void imageCb(const sensor_msgs::ImageConstPtr& msg);

  ros::NodeHandle nh;
  image_transport::ImageTransport it;
  image_transport::Subscriber image_sub_;

  //Publishers for output image
  image_transport::Publisher outImg_pub_;

  ros::Publisher landmark_pub_;

};

LandmarkDetector::LandmarkDetector()
  :it(nh)
  {
    image_sub_ = it.subscribe("image", 1, &LandmarkDetector::imageCb, this);

    //Debug image publisher
    outImg_pub_ = it.advertise("landmark/outImg",1);
    //Landmark position publisher
    landmark_pub_ = nh.advertise<landmark_self_sim::landmarkLocation>("landmarkLocation",1);
  }

/**
 * Convert an opencv image into an mcimg GrayImage.  Note, this
 * allocates a new image, which must be freed with imFree!
 **/
GrayImage cvToGrayImage(cv::Mat img){
  //Use opencv to conver to gray
  cv::Mat grayImg;
  cv::cvtColor(img,grayImg,CV_RGB2GRAY);  
  //Create a gray mcimg of the correct size
  //fprintf(stderr,"cols: %d, rows: %d\n",grayImg.cols,grayImg.rows);
  GrayImage retImg = newGrayImage(grayImg.cols,grayImg.rows);

  for(int i=0; i<grayImg.rows; i++){
    for(int j=0; j<grayImg.cols; j++){
      imRef(retImg,j,i) = grayImg.at<uchar>(i,j);
    }
  }
        
  return retImg;
}


void LandmarkDetector::imageCb(const sensor_msgs::ImageConstPtr& msg){
  cv_bridge::CvImagePtr cv_ptr;
  try{
    cv_ptr = cv_bridge::toCvCopy(msg, enc::RGB8);
  }catch (cv_bridge::Exception& e){
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  //Get a the image just as a Mat
  cv::Mat colorImg = cv_ptr->image;//.clone();

  GrayImage im1;
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
  peakw = (peakperc * window) / 100 + PEAKW_ADD;

  //Get the mcimg formated image
  im1 = cvToGrayImage(colorImg);
  lamarr = landmarkParams(im1, NULL, //"out.match.ppm", 
                          verbose, drawX,
                          window, peakw, threshold,
                          factor, spacing, skip, ycoord);
  //Free the image
  imFree(im1);

  //Create a smaller image that we will mark up
  #define SCALE_FACTOR 1.0
  cv::Mat smlImg = cv::Mat();
  cv::resize(colorImg,smlImg,cv::Size(),SCALE_FACTOR,SCALE_FACTOR,
             cv::INTER_NEAREST);

  for (int i=0; i<lamarr.count; i++) {
    landm lam = lamarr.lm[i];
    ROS_INFO("Landmark at %3d,%3d to %d,%d - code = %d\n",
             lam.xtop, lam.ytop, lam.xbottom, lam.ybottom, lam.code);

    landmark_self_sim::landmarkLocation landmarkLoc;
    landmarkLoc.header.stamp = ros::Time::now();
    //Copy over the fields
    landmarkLoc.xtop = lam.xtop;
    landmarkLoc.ytop = lam.ytop;
    landmarkLoc.xbottom = lam.xbottom;
    landmarkLoc.ybottom = lam.ybottom;
    landmarkLoc.code = lam.code;
    //Compute the distance
    landmarkLoc.height = sqrt((lam.xtop-lam.xbottom)*(lam.xtop-lam.xbottom) 
                              +(lam.ytop-lam.ybottom)*(lam.ytop-lam.ybottom) );
    //Publish it
    landmark_pub_.publish(landmarkLoc);

    //Now add the marks to the image to indicate the detected frame
#define PLUS_SIZE 4
#define PLUS_COLOR cv::Scalar(0,255,0,0)
    cv::line(smlImg,
             cv::Point(lam.xtop*SCALE_FACTOR+PLUS_SIZE,lam.ytop*SCALE_FACTOR),
             cv::Point(lam.xtop*SCALE_FACTOR-PLUS_SIZE,lam.ytop*SCALE_FACTOR),
             PLUS_COLOR,1);
    cv::line(smlImg,
             cv::Point(lam.xtop*SCALE_FACTOR,lam.ytop*SCALE_FACTOR+PLUS_SIZE),
             cv::Point(lam.xtop*SCALE_FACTOR,lam.ytop*SCALE_FACTOR-PLUS_SIZE),
             PLUS_COLOR,1);
    cv::line(smlImg,
             cv::Point(lam.xbottom*SCALE_FACTOR+PLUS_SIZE,lam.ybottom*SCALE_FACTOR),
             cv::Point(lam.xbottom*SCALE_FACTOR-PLUS_SIZE,lam.ybottom*SCALE_FACTOR),
             PLUS_COLOR,1);
    cv::line(smlImg,
             cv::Point(lam.xbottom*SCALE_FACTOR,lam.ybottom*SCALE_FACTOR+PLUS_SIZE),
             cv::Point(lam.xbottom*SCALE_FACTOR,lam.ybottom*SCALE_FACTOR-PLUS_SIZE),
             PLUS_COLOR,1);
    stringstream ss;
    ss << lam.code;
    cv::putText(smlImg,ss.str(),
                cv::Point(lam.xbottom*SCALE_FACTOR-PLUS_SIZE*5,lam.ybottom*SCALE_FACTOR-PLUS_SIZE),
                cv::FONT_HERSHEY_SIMPLEX,SCALE_FACTOR,PLUS_COLOR);
  }

  //Send some images out
  //cv_ptr->image = colorImg;
  cv_ptr->image = smlImg;
  cv_ptr->encoding = enc::RGB8;
  outImg_pub_.publish(cv_ptr->toImageMsg());
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "landmark_detector");
  LandmarkDetector bd;
  ros::spin();
  return 0;
}
