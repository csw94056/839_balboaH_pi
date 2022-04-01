#include <ros/ros.h>
#include <balboa_core/lineSensor.h>
#include <balboa_core/balboaLL.h>
#include <balboa_core/balboaMotorSpeeds.h>
#include <iostream>

// const char ascii_list_70[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";
//@%#*+=-:,.
const char ascii_list_10[] = {'N', '@', '%', '#', '*', '+', '=', '-', ':', ',', '.'};
const int length = 250;
const unsigned char NUM_OF_SENSOR = 5;
std::vector<std::vector<unsigned int>> map(NUM_OF_SENSOR);

class mapping {
    private:
        ros::NodeHandle n;
        // create ROS subscribers and publisher
        ros::Subscriber sub_line = n.subscribe("lineSensorMap", 10, &mapping::lineSensor_callback, this);
        unsigned char prev_row_i = 255;
        unsigned char coln_i = 0;
        unsigned char num_coln_received = 0;
        // if mov_dir = 0, then the robot is moving right
        // if mov_dir = 1, then the robot is moving left
        bool mov_dir = 0;
    public:
        unsigned char i, j;

        mapping() {
            
        }

        void lineSensor_callback(const balboa_core::lineSensor& line_data) {
            if(prev_row_i == 255) {
                for(unsigned char i = 0; i < NUM_OF_SENSOR; i++) {
                    map[i].resize(line_data.num_coln);
                }
            }

            if(prev_row_i != line_data.row_i) {
                prev_row_i = line_data.row_i;
                if(line_data.row_i % 2 == 0) {
                    // even numbered row => the robot moving right
                    mov_dir = 0;
                    coln_i = 0;
                }
                else {
                    // odd numbered row => the robot moving left
                    mov_dir = 1;
                    coln_i = line_data.num_coln;
                }
                num_coln_received = 0;
            }
            //std::cout << "num_coln_received: " << num_coln_received;
            //std::cout << "line_data.num_coln: " << line_data.num_coln;
            //std::cout << "coln_i: " << coln_i;

            // store rf sensor [0-4] data to matrix
//            map[0][coln_i] = (char)(line_data.sensor0 / length);
//            map[1][coln_i] = (char)(line_data.sensor1 / length);
//            map[2][coln_i] = (char)(line_data.sensor2 / length);
//            map[3][coln_i] = (char)(line_data.sensor3 / length);
//            map[4][coln_i] = (char)(line_data.sensor4 / length);
            
            if(line_data.row_i % 2 == 0) {
                map[0][coln_i] = line_data.sensor0;
                map[1][coln_i] = line_data.sensor1;
                map[2][coln_i] = line_data.sensor2;
                map[3][coln_i] = line_data.sensor3;
                map[4][coln_i] = line_data.sensor4;
            } else {
                map[4][coln_i] = line_data.sensor0;
                map[3][coln_i] = line_data.sensor1;
                map[2][coln_i] = line_data.sensor2;
                map[1][coln_i] = line_data.sensor3;
                map[0][coln_i] = line_data.sensor4;
            }

            if(!mov_dir) {
                // even numbered row => the robot moving right
                coln_i += 1;
            }
            else {
                // odd numbered row => the robot moving left
                coln_i -= 1;
            }
            

            if(num_coln_received == line_data.num_coln - 1) {
                for(i = 0; i < NUM_OF_SENSOR; i++ ) {
                    for(j = 0; j < line_data.num_coln; j++) {
                        printf("%c", ascii_list_10[(char)(map[i][j]/length)]);
                    }
                    std::cout << std::endl;
                }
            }
            
            

            
            // 2500 == no rf signal received back to sensor
            //
            // std::cout << line_data.sensor0 << "_";
            // std::cout << line_data.sensor1 << "_";
            // std::cout << line_data.sensor2 << "_";
            // std::cout << line_data.sensor3 << "_";
            // std::cout << line_data.sensor4 << "_";
            // std::cout << std::endl;
            // std::cout << ascii_list_10[(char)(line_data.sensor0 / length)];
            // std::cout << ascii_list_10[(char)(line_data.sensor1 / length)];
            // std::cout << ascii_list_10[(char)(line_data.sensor2 / length)];
            // std::cout << ascii_list_10[(char)(line_data.sensor3 / length)];
            // std::cout << ascii_list_10[(char)(line_data.sensor4 / length)];
            // std::cout << std::endl << std::endl;

            if(num_coln_received == line_data.num_coln -1 && line_data.row_i == line_data.num_row - 1) {
                prev_row_i = 255;
                num_coln_received = 0;
            }
            else num_coln_received += 1;
        }
};

int main(int argc, char ** argv) {
    ros::init(argc, argv, "mapping");
    mapping map;
    // std::cout << "\"hello!" << std::endl;
    // for (unsigned int i = 0; i < sizeof(ascii_list_10)/sizeof(ascii_list_10[0]); i++) {
    //     std::cout << "i: " << i << "val: " << ascii_list_10[i] << std::endl;
    // }
    ros::spin();
    return 0;
}
