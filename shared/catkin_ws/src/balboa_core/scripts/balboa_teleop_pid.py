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
    # This node receives PID-controlled motorSpeed messages and publishes them to motorSpeeds

  
  def handleDistancePID(self, balboaMotorSpeeds):
    print("left: %s, right %s" % (balboaMotorSpeeds.left, balboaMotorSpeeds.right))
    self.msPub.publish(balboaMotorSpeeds)
    
  def handleAngularVelPID(self, balboaMotorSpeeds):
    print("left: %s, right %s" % (balboaMotorSpeeds.left, balboaMotorSpeeds.right))
    self.msPub.publish(balboaMotorSpeeds)

  def __init__(self):
    rospy.init_node('balboa_teleop')

    self.msPub = rospy.Publisher('motorSpeeds', balboaMotorSpeeds, queue_size=10)
    self.sub_distancePID = rospy.Subscriber('distancePID', balboaMotorSpeeds, self.handleDistancePID)
    self.sub_angularVelPID = rospy.Subscriber('angularVelPID', balboaMotorSpeeds, self.handleAngularVelPID)

  def main_loop(self):
    '''main loop get a packet from the port and parse it and publish it'''
    r = rospy.Rate(200)

    # Publish each byte as it comes in
    while not rospy.is_shutdown():  

      r.sleep()
      

if __name__ == '__main__':
  a = TheNode()
  a.main_loop()


