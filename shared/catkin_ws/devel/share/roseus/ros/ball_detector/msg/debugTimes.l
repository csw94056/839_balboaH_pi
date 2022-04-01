;; Auto-generated. Do not edit!


(when (boundp 'ball_detector::debugTimes)
  (if (not (find-package "BALL_DETECTOR"))
    (make-package "BALL_DETECTOR"))
  (shadow 'debugTimes (find-package "BALL_DETECTOR")))
(unless (find-package "BALL_DETECTOR::DEBUGTIMES")
  (make-package "BALL_DETECTOR::DEBUGTIMES"))

(in-package "ROS")
;;//! \htmlinclude debugTimes.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ball_detector::debugTimes
  :super ros::object
  :slots (_header _labels _times ))

(defmethod ball_detector::debugTimes
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:labels __labels) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:times __times) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _labels __labels)
   (setq _times __times)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:labels
   (&optional __labels)
   (if __labels (setq _labels __labels)) _labels)
  (:times
   (&optional __times)
   (if __times (setq _times __times)) _times)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string[] _labels
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _labels)) 4
    ;; float64[] _times
    (* 8    (length _times)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string[] _labels
     (write-long (length _labels) s)
     (dolist (elem _labels)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float64[] _times
     (write-long (length _times) s)
     (dotimes (i (length _times))
       (sys::poke (elt _times i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string[] _labels
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _labels (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _labels i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float64[] _times
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _times (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _times i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get ball_detector::debugTimes :md5sum-) "24f9f017187aacc6186ce1f2d40d694e")
(setf (get ball_detector::debugTimes :datatype-) "ball_detector/debugTimes")
(setf (get ball_detector::debugTimes :definition-)
      "Header header
#string identifying the corresponding element time 
string[] labels
#the execution time in seconds
float64[] times
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



(provide :ball_detector/debugTimes "24f9f017187aacc6186ce1f2d40d694e")


