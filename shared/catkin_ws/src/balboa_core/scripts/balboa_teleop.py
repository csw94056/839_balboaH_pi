#!/usr/bin/env python
import struct
import serial
import sys
import rospy
from std_msgs.msg import UInt8
from geometry_msgs.msg import Twist
from balboa_core.msg import balboaLL
from balboa_core.msg import balboaMotorSpeeds

class TheNode(object):
  '''Class to communicate with the balboa robot. Carrick Detweiler 2020'''


  # Karissa Jelonek and Sung Woo Choi
  # This node receives teleop commands from the keyboard and
  # publishes them to motorSpeeds

  # Callback Function for handling messages received from keyboard
  def handleSetTurtleTeleopKey(self, teleop_msg):
    self.receivedMsg = True
    x = teleop_msg.linear.x
    z = teleop_msg.angular.z
    msg = balboaMotorSpeeds()
    print(self.stop_flag_timer)
    if x > 0:
        msg.left = 15
        msg.right = 15
    elif x < 0:
        msg.left = -15
        msg.right = -15
    elif z > 0:
        msg.left = -5
        msg.right = 5
    elif z < 0:
        msg.left = 5
        msg.right = -5
    self.pub.publish(msg)
    self.stop_flag_timer = 0
    
    
    

  def __init__(self):
    self.receivedMsg = False
    rospy.init_node('balboa_teleop')

    self.pub = rospy.Publisher("motorSpeeds", balboaMotorSpeeds, queue_size=100)
    self.sub = rospy.Subscriber("turtle1/cmd_vel", Twist, self.handleSetTurtleTeleopKey)
    
    #timer to stop robot after keys are released
    self.stop_flag_timer = 0
    


  def main_loop(self):
    '''main loop get a packet from the port and parse it and publish it'''
    r = rospy.Rate(200)

    while not rospy.is_shutdown():
      # each increment is 1/200 hz = 5 ms
      self.stop_flag_timer += 1
      
      # Stop robot when keys are released
      if self.receivedMsg == True:
          if self.stop_flag_timer >= 50:
            self.stop_flag_timer = 0
            msgStop = balboaMotorSpeeds()
            msgStop.left = 0
            msgStop.right = 0
            self.pub.publish(msgStop)

      
      r.sleep()
      

if __name__ == '__main__':
  a = TheNode()
  a.main_loop()


