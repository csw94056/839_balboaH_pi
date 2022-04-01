;; Auto-generated. Do not edit!


(when (boundp 'balboa_core::balboaMotorSpeeds)
  (if (not (find-package "BALBOA_CORE"))
    (make-package "BALBOA_CORE"))
  (shadow 'balboaMotorSpeeds (find-package "BALBOA_CORE")))
(unless (find-package "BALBOA_CORE::BALBOAMOTORSPEEDS")
  (make-package "BALBOA_CORE::BALBOAMOTORSPEEDS"))

(in-package "ROS")
;;//! \htmlinclude balboaMotorSpeeds.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass balboa_core::balboaMotorSpeeds
  :super ros::object
  :slots (_header _left _right ))

(defmethod balboa_core::balboaMotorSpeeds
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:left __left) 0)
    ((:right __right) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _left (round __left))
   (setq _right (round __right))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:left
   (&optional __left)
   (if __left (setq _left __left)) _left)
  (:right
   (&optional __right)
   (if __right (setq _right __right)) _right)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int8 _left
    1
    ;; int8 _right
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int8 _left
       (write-byte _left s)
     ;; int8 _right
       (write-byte _right s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int8 _left
     (setq _left (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _left 127) (setq _left (- _left 256)))
   ;; int8 _right
     (setq _right (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _right 127) (setq _right (- _right 256)))
   ;;
   self)
  )

(setf (get balboa_core::balboaMotorSpeeds :md5sum-) "81401375253b01074df288a02d8d49bf")
(setf (get balboa_core::balboaMotorSpeeds :datatype-) "balboa_core/balboaMotorSpeeds")
(setf (get balboa_core::balboaMotorSpeeds :definition-)
      "Header header

int8 left
int8 right


================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :balboa_core/balboaMotorSpeeds "81401375253b01074df288a02d8d49bf")


