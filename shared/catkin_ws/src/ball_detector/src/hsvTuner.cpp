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

namespace enc = sensor_msgs::image_encodings;

class HSVTuner {
	private:
		int lowh = 0;
		int lows = 0;
		int lowv = 0;
		int highh = 255;
		int highs = 255;
		int highv = 255;
		int avgh = 0;
		int values = 0;
		int avgs = 0;
		int avgv = 0;

		ros::NodeHandle n;
		ros::Subscriber debug_img1_sub = n.subscribe("balldebug/img3", 1, &HSVTuner::debug_img3_callback, this);
		ros::Publisher update_low_pub = n.advertise<geometry_msgs::Vector3>("thresh/low", 1);
		ros::Publisher update_high_pub = n.advertise<geometry_msgs::Vector3>("thresh/high", 1);

	public:
		void debug_img3_callback(const sensor_msgs::ImageConstPtr& msg) {
			static cv_bridge::CvImagePtr cv_const_ptr;
			try {
				cv_const_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
			}
			catch (cv_bridge::Exception& e)
			{
				ROS_ERROR("cv_brridge exception: %s", e.what());
				return;
			}
			cv::Mat m = cv_const_ptr->image;
			//cv::imshow("Image window", cv_const_ptr->image);
			cv::waitKey(3);
			values = 0;
			avgh = 0;
			avgs = 0;
			avgv = 0;
			//get the hsv value of each pixel
			for(int i = 0; i < m.rows; i++) {
				for(int j = 0; j < m.cols; j++) {
					cv::Vec3b hsv = m.at<cv::Vec3b>(i, j);
					//check if s > 50 / pixel is not white
					if(hsv.val[1] > 50) {
						//get average hsv of non-white pixels
						values += 1;
						avgh += hsv.val[0];
						avgs += hsv.val[1];
						avgv += hsv.val[2];
						//printf("%d ", hsv.val[0]);
						//printf("%d ", hsv.val[1]);
						//printf("%d \n",hsv.val[2]);
					}
				}
			}
			//publish new low and high threshold values
			geometry_msgs::Vector3 lowhsv;
			geometry_msgs::Vector3 highhsv;
			if(avgh/values - 5 < 0) {
				lowhsv.x = 0;
			}
			else {
				lowhsv.x = avgh/values - 5;
			}
			if(avgs/values - 50 < 0) {
				lowhsv.y = 0;
			}
			else {
				lowhsv.y = avgs/values - 50;
			}
			if(avgv/values - 50 < 0) {
				lowhsv.z = 0;
			}
			else {
				lowhsv.z = avgv/values - 50;
			}
			if(avgh/values + 5 > 255) {
				highhsv.x  = 255;
			}
			else {
				highhsv.x = avgh/values + 5;
			}
			highhsv.y = highs;
			highhsv.z = highv;
			update_low_pub.publish(lowhsv);
			update_high_pub.publish(highhsv);
		}


};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "hsvTuner");
	HSVTuner hsvt;
	ros::spin();
	return 0;

}






