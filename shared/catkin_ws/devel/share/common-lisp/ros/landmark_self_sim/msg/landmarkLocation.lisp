; Auto-generated. Do not edit!


(cl:in-package landmark_self_sim-msg)


;//! \htmlinclude landmarkLocation.msg.html

(cl:defclass <landmarkLocation> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (xtop
    :reader xtop
    :initarg :xtop
    :type cl:integer
    :initform 0)
   (ytop
    :reader ytop
    :initarg :ytop
    :type cl:integer
    :initform 0)
   (xbottom
    :reader xbottom
    :initarg :xbottom
    :type cl:integer
    :initform 0)
   (ybottom
    :reader ybottom
    :initarg :ybottom
    :type cl:integer
    :initform 0)
   (height
    :reader height
    :initarg :height
    :type cl:float
    :initform 0.0)
   (code
    :reader code
    :initarg :code
    :type cl:integer
    :initform 0))
)

(cl:defclass landmarkLocation (<landmarkLocation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <landmarkLocation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'landmarkLocation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name landmark_self_sim-msg:<landmarkLocation> is deprecated: use landmark_self_sim-msg:landmarkLocation instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:header-val is deprecated.  Use landmark_self_sim-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'xtop-val :lambda-list '(m))
(cl:defmethod xtop-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:xtop-val is deprecated.  Use landmark_self_sim-msg:xtop instead.")
  (xtop m))

(cl:ensure-generic-function 'ytop-val :lambda-list '(m))
(cl:defmethod ytop-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:ytop-val is deprecated.  Use landmark_self_sim-msg:ytop instead.")
  (ytop m))

(cl:ensure-generic-function 'xbottom-val :lambda-list '(m))
(cl:defmethod xbottom-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:xbottom-val is deprecated.  Use landmark_self_sim-msg:xbottom instead.")
  (xbottom m))

(cl:ensure-generic-function 'ybottom-val :lambda-list '(m))
(cl:defmethod ybottom-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:ybottom-val is deprecated.  Use landmark_self_sim-msg:ybottom instead.")
  (ybottom m))

(cl:ensure-generic-function 'height-val :lambda-list '(m))
(cl:defmethod height-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:height-val is deprecated.  Use landmark_self_sim-msg:height instead.")
  (height m))

(cl:ensure-generic-function 'code-val :lambda-list '(m))
(cl:defmethod code-val ((m <landmarkLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader landmark_self_sim-msg:code-val is deprecated.  Use landmark_self_sim-msg:code instead.")
  (code m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <landmarkLocation>) ostream)
  "Serializes a message object of type '<landmarkLocation>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'xtop)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ytop)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'xbottom)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ybottom)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'height))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <landmarkLocation>) istream)
  "Deserializes a message object of type '<landmarkLocation>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'xtop) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ytop) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'xbottom) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ybottom) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'height) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'code) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<landmarkLocation>)))
  "Returns string type for a message object of type '<landmarkLocation>"
  "landmark_self_sim/landmarkLocation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'landmarkLocation)))
  "Returns string type for a message object of type 'landmarkLocation"
  "landmark_self_sim/landmarkLocation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<landmarkLocation>)))
  "Returns md5sum for a message object of type '<landmarkLocation>"
  "5fff4f104cc29dd1741797346a6aa89e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'landmarkLocation)))
  "Returns md5sum for a message object of type 'landmarkLocation"
  "5fff4f104cc29dd1741797346a6aa89e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<landmarkLocation>)))
  "Returns full string definition for message of type '<landmarkLocation>"
  (cl:format cl:nil "Header header~%~%# The x,y location of the top and bottom point of the detected landmark.~%int32 xtop~%int32 ytop~%int32 xbottom~%int32 ybottom~%~%# Height of the landmark as computed as the distance between the top~%# and bottom points.~%float64 height~%~%# The landmark code id number which should can range from 0 to 255.  If~%# this is -1 then it means the code was not correctly read (and the~%# above points may not be accurate).~%int32 code~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'landmarkLocation)))
  "Returns full string definition for message of type 'landmarkLocation"
  (cl:format cl:nil "Header header~%~%# The x,y location of the top and bottom point of the detected landmark.~%int32 xtop~%int32 ytop~%int32 xbottom~%int32 ybottom~%~%# Height of the landmark as computed as the distance between the top~%# and bottom points.~%float64 height~%~%# The landmark code id number which should can range from 0 to 255.  If~%# this is -1 then it means the code was not correctly read (and the~%# above points may not be accurate).~%int32 code~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <landmarkLocation>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <landmarkLocation>))
  "Converts a ROS message object to a list"
  (cl:list 'landmarkLocation
    (cl:cons ':header (header msg))
    (cl:cons ':xtop (xtop msg))
    (cl:cons ':ytop (ytop msg))
    (cl:cons ':xbottom (xbottom msg))
    (cl:cons ':ybottom (ybottom msg))
    (cl:cons ':height (height msg))
    (cl:cons ':code (code msg))
))
