; Auto-generated. Do not edit!


(cl:in-package ball_detector-msg)


;//! \htmlinclude ballDebug.msg.html

(cl:defclass <ballDebug> (roslisp-msg-protocol:ros-message)
  ((sendDebugImages
    :reader sendDebugImages
    :initarg :sendDebugImages
    :type cl:boolean
    :initform cl:nil)
   (sendDebugTimes
    :reader sendDebugTimes
    :initarg :sendDebugTimes
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ballDebug (<ballDebug>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ballDebug>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ballDebug)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detector-msg:<ballDebug> is deprecated: use ball_detector-msg:ballDebug instead.")))

(cl:ensure-generic-function 'sendDebugImages-val :lambda-list '(m))
(cl:defmethod sendDebugImages-val ((m <ballDebug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detector-msg:sendDebugImages-val is deprecated.  Use ball_detector-msg:sendDebugImages instead.")
  (sendDebugImages m))

(cl:ensure-generic-function 'sendDebugTimes-val :lambda-list '(m))
(cl:defmethod sendDebugTimes-val ((m <ballDebug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detector-msg:sendDebugTimes-val is deprecated.  Use ball_detector-msg:sendDebugTimes instead.")
  (sendDebugTimes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ballDebug>) ostream)
  "Serializes a message object of type '<ballDebug>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'sendDebugImages) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'sendDebugTimes) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ballDebug>) istream)
  "Deserializes a message object of type '<ballDebug>"
    (cl:setf (cl:slot-value msg 'sendDebugImages) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'sendDebugTimes) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ballDebug>)))
  "Returns string type for a message object of type '<ballDebug>"
  "ball_detector/ballDebug")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ballDebug)))
  "Returns string type for a message object of type 'ballDebug"
  "ball_detector/ballDebug")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ballDebug>)))
  "Returns md5sum for a message object of type '<ballDebug>"
  "f0dbcd340db400b8721875b15029f990")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ballDebug)))
  "Returns md5sum for a message object of type 'ballDebug"
  "f0dbcd340db400b8721875b15029f990")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ballDebug>)))
  "Returns full string definition for message of type '<ballDebug>"
  (cl:format cl:nil "bool sendDebugImages~%bool sendDebugTimes ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ballDebug)))
  "Returns full string definition for message of type 'ballDebug"
  (cl:format cl:nil "bool sendDebugImages~%bool sendDebugTimes ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ballDebug>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ballDebug>))
  "Converts a ROS message object to a list"
  (cl:list 'ballDebug
    (cl:cons ':sendDebugImages (sendDebugImages msg))
    (cl:cons ':sendDebugTimes (sendDebugTimes msg))
))
