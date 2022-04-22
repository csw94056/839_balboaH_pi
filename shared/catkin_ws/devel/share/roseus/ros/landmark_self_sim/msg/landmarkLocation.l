;; Auto-generated. Do not edit!


(when (boundp 'landmark_self_sim::landmarkLocation)
  (if (not (find-package "LANDMARK_SELF_SIM"))
    (make-package "LANDMARK_SELF_SIM"))
  (shadow 'landmarkLocation (find-package "LANDMARK_SELF_SIM")))
(unless (find-package "LANDMARK_SELF_SIM::LANDMARKLOCATION")
  (make-package "LANDMARK_SELF_SIM::LANDMARKLOCATION"))

(in-package "ROS")
;;//! \htmlinclude landmarkLocation.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass landmark_self_sim::landmarkLocation
  :super ros::object
  :slots (_header _xtop _ytop _xbottom _ybottom _height _code ))

(defmethod landmark_self_sim::landmarkLocation
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:xtop __xtop) 0)
    ((:ytop __ytop) 0)
    ((:xbottom __xbottom) 0)
    ((:ybottom __ybottom) 0)
    ((:height __height) 0.0)
    ((:code __code) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _xtop (round __xtop))
   (setq _ytop (round __ytop))
   (setq _xbottom (round __xbottom))
   (setq _ybottom (round __ybottom))
   (setq _height (float __height))
   (setq _code (round __code))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:xtop
   (&optional __xtop)
   (if __xtop (setq _xtop __xtop)) _xtop)
  (:ytop
   (&optional __ytop)
   (if __ytop (setq _ytop __ytop)) _ytop)
  (:xbottom
   (&optional __xbottom)
   (if __xbottom (setq _xbottom __xbottom)) _xbottom)
  (:ybottom
   (&optional __ybottom)
   (if __ybottom (setq _ybottom __ybottom)) _ybottom)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:code
   (&optional __code)
   (if __code (setq _code __code)) _code)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _xtop
    4
    ;; int32 _ytop
    4
    ;; int32 _xbottom
    4
    ;; int32 _ybottom
    4
    ;; float64 _height
    8
    ;; int32 _code
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _xtop
       (write-long _xtop s)
     ;; int32 _ytop
       (write-long _ytop s)
     ;; int32 _xbottom
       (write-long _xbottom s)
     ;; int32 _ybottom
       (write-long _ybottom s)
     ;; float64 _height
       (sys::poke _height (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _code
       (write-long _code s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _xtop
     (setq _xtop (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ytop
     (setq _ytop (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _xbottom
     (setq _xbottom (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ybottom
     (setq _ybottom (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _height
     (setq _height (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _code
     (setq _code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get landmark_self_sim::landmarkLocation :md5sum-) "5fff4f104cc29dd1741797346a6aa89e")
(setf (get landmark_self_sim::landmarkLocation :datatype-) "landmark_self_sim/landmarkLocation")
(setf (get landmark_self_sim::landmarkLocation :definition-)
      "Header header

# The x,y location of the top and bottom point of the detected landmark.
int32 xtop
int32 ytop
int32 xbottom
int32 ybottom

# Height of the landmark as computed as the distance between the top
# and bottom points.
float64 height

# The landmark code id number which should can range from 0 to 255.  If
# this is -1 then it means the code was not correctly read (and the
# above points may not be accurate).
int32 code

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



(provide :landmark_self_sim/landmarkLocation "5fff4f104cc29dd1741797346a6aa89e")


