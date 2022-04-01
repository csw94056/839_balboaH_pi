#!/usr/bin/env python
from os import kill
import struct
import serial
import sys
import rospy
from std_msgs.msg import UInt8
from std_msgs.msg import Int16
from geometry_msgs.msg import Twist
from balboa_core.msg import balboaLL
from balboa_core.msg import balboaMotorSpeeds

INF = 100000000000

class angularVelPIDNode(object):
    '''
       Sung Woo Choi and Karissa Jelonek
        
       Class node that sits between the angular position controller (anglePID) and
       balboa_serial node.
       The node controls angular position such that the balboa robot spins at constant
       angular velocity.
    '''
    
    def __init__(self):
        # Initiate ros node /balboa_angularvelpid
        rospy.init_node('balboa_angularvelpid')
        
        # Initiate Subscriber
        self.sub_BalboaLL = rospy.Subscriber('balboaLL', balboaLL, self.handleBalboaLL)
        self.sub_angularPID = rospy.Subscriber('angularPID', Int16, self.handleAngularPID)
        # Initiate Publisher
        self.pub_angularVelPID = rospy.Publisher('angularVelPID', balboaMotorSpeeds, queue_size=10)
        
        # Initiate angle parameters
        self.prev_angle = INF    
        # Initiate target values for pid_control()
        self.target_angle_rate = INF        
        # Initiate variables used for pid_control()
        self.prev_error_angle_rate = 0
        self.prev_angle_rate = INF
        self.integral_angle_rate = 0
        # ROS Parameter Server
        # set PID parameters to receive settings from launch file
        rospy.set_param('angleRateCtrl/P', 0.1)
        rospy.set_param('angleRateCtrl/I', 0.0)
        rospy.set_param('angleRateCtrl/D', 0.0)
        self.speed_limit = 45
        
    def handleBalboaLL(self, balboall_msg):
        # receive PID settings from launch file or command line via (rosparam set param_name value)
        self.Kp_angle_rate = rospy.get_param('angleRateCtrl/P')
        self.Ki_angle_rate = rospy.get_param('angleRateCtrl/I')
        self.Kd_angle_rate = rospy.get_param('angleRateCtrl/D')

        if self.target_angle_rate == INF:
            return
        if self.prev_angle == INF:
            self.prev_angle = balboall_msg.angleX / 1000
            return
            
        if self.prev_angle_rate == INF:
            current_angle = balboall_msg.angleX / 1000
            # previous angle rate = difference of current angle and previous angle over 1 iteration
            self.prev_angle_rate = (current_angle - self.prev_angle)
            self.prev_angle = current_angle
            return
        
        current_angle = balboall_msg.angleX / 1000
        current_angle_rate = (current_angle - self.prev_angle)
        
        # angularVelPID
        r_angle_rate, self.prev_error_angle_rate, self.integral_angle_rate = self.pid_control(self.Kp_angle_rate, self.Ki_angle_rate, self.Kd_angle_rate, self.target_angle_rate, current_angle_rate, self.prev_error_angle_rate, self.integral_angle_rate)
        
        if r_angle_rate > self.speed_limit:
            r_angle_rate = self.speed_limit
        if r_angle_rate < -self.speed_limit:
            r_angle_rate = -self.speed_limit
        # publish angleVelPID node message
        angularVelPID_msg = balboaMotorSpeeds()
        angularVelPID_msg.left = int(-r_angle_rate)
        angularVelPID_msg.right = int(r_angle_rate)
        self.pub_angularVelPID.publish(angularVelPID_msg)
        
        # store current parameters for next iteration
        self.prev_angle = current_angle
        self.prev_angle_rate = current_angle_rate
        
        
    def handleAngularPID(self, msg):
        # update target angular rate based on AngularPID
        if msg.data == 0:
            self.target_angle_rate = INF
        else:
            self.target_angle_rate = msg.data
        
        
    def pid_control(self, Kp, Ki, Kd, target, current_val, prev_error, integral):
        '''
            r = rotation
            e_current (e_i) = error of current time step
            e_prev (e_(i-1)) = error of previous time step
            a_t = target parameter
            a_i = current parameter 
            e_current = a_t(i) - a_i(i)
            e_prev = a_t(i-1) - a_i(i-1)
            integral(i) = integral(i-1) + (a_t - a_i)
            control: r = Kp*(a_t - a_i) + Kd*(e_current - e_prev) + Ki*integral
        '''
        error = target - current_val
        delta_error = error - prev_error
        integral += error
        r = Kp*error + Ki*integral + Kd*delta_error
        return r, error, integral

    def main_loop(self):
        rospy.sleep(0.1)
        rospy.spin()
            
if __name__ == '__main__':
    pid = angularVelPIDNode()
    pid.main_loop()
