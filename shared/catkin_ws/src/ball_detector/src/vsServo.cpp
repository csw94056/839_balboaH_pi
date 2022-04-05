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

class VSServo{
public:
    visualServo();
    
private:
    ros::NodeHandle n;
    ros::Subscriber circle_sub = n.Subscrie("ballLocation", 1, &VSServo::ballLocation_callback, this);
}

VSServo::visualServo() {

}