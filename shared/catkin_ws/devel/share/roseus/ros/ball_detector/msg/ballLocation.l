;; Auto-generated. Do not edit!


(when (boundp 'ball_detector::ballLocation)
  (if (not (find-package "BALL_DETECTOR"))
    (make-package "BALL_DETECTOR"))
  (shadow 'ballLocation (find-package "BALL_DETECTOR")))
(unless (find-package "BALL_DETECTOR::BALLLOCATION")
  (make-package "BALL_DETECTOR::BALLLOCATION"))

(in-package "ROS")
;;//! \htmlinclude ballLocation.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ball_detector::ballLocation
  :super ros::object
  :slots (_header _imageWidth _imageHeight _x _y _radius ))

(defmethod ball_detector::ballLocation
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:imageWidth __imageWidth) 0)
    ((:imageHeight __imageHeight) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:radius __radius) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _imageWidth (round __imageWidth))
   (setq _imageHeight (round __imageHeight))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _radius (float __radius))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:imageWidth
   (&optional __imageWidth)
   (if __imageWidth (setq _imageWidth __imageWidth)) _imageWidth)
  (:imageHeight
   (&optional __imageHeight)
   (if __imageHeight (setq _imageHeight __imageHeight)) _imageHeight)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:radius
   (&optional __radius)
   (if __radius (setq _radius __radius)) _radius)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _imageWidth
    4
    ;; uint32 _imageHeight
    4
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _radius
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _imageWidth
       (write-long _imageWidth s)
     ;; uint32 _imageHeight
       (write-long _imageHeight s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _radius
       (sys::poke _radius (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _imageWidth
     (setq _imageWidth (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _imageHeight
     (setq _imageHeight (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _radius
     (setq _radius (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get ball_detector::ballLocation :md5sum-) "046f798a75776068674c89e287314673")
(setf (get ball_detector::ballLocation :datatype-) "ball_detector/ballLocation")
(setf (get ball_detector::ballLocation :definition-)
      "Header header
#The iamge width and height in pixels
uint32 imageWidth
uint32 imageHeight

#The location of the ball center in x,y (width,height)
float64 x
float64 y
#The radius of the detected ball
float64 radius

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



(provide :ball_detector/ballLocation "046f798a75776068674c89e287314673")


