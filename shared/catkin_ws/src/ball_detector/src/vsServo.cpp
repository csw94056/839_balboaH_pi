#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3.h>

#include <ball_detector/ballLocation.h>
#include <ball_detector/ballDebug.h>
#include <ball_detector/debugTimes.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/matx.hpp>

#include <vector>
using namespace std;

class SVServo{
  ros::NodeHandle n;
  ros::Subscriber debug_img1_sub = n.subscribe("balldebug/img1", 1, &SVServo::debug_img1_callback, this);
  
}