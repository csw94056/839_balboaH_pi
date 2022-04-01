; Auto-generated. Do not edit!


(cl:in-package balboa_core-msg)


;//! \htmlinclude lineSensor.msg.html

(cl:defclass <lineSensor> (roslisp-msg-protocol:ros-message)
  ((row_i
    :reader row_i
    :initarg :row_i
    :type cl:fixnum
    :initform 0)
   (num_coln
    :reader num_coln
    :initarg :num_coln
    :type cl:fixnum
    :initform 0)
   (num_row
    :reader num_row
    :initarg :num_row
    :type cl:fixnum
    :initform 0)
   (sensor0
    :reader sensor0
    :initarg :sensor0
    :type cl:fixnum
    :initform 0)
   (sensor1
    :reader sensor1
    :initarg :sensor1
    :type cl:fixnum
    :initform 0)
   (sensor2
    :reader sensor2
    :initarg :sensor2
    :type cl:fixnum
    :initform 0)
   (sensor3
    :reader sensor3
    :initarg :sensor3
    :type cl:fixnum
    :initform 0)
   (sensor4
    :reader sensor4
    :initarg :sensor4
    :type cl:fixnum
    :initform 0))
)

(cl:defclass lineSensor (<lineSensor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lineSensor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lineSensor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name balboa_core-msg:<lineSensor> is deprecated: use balboa_core-msg:lineSensor instead.")))

(cl:ensure-generic-function 'row_i-val :lambda-list '(m))
(cl:defmethod row_i-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:row_i-val is deprecated.  Use balboa_core-msg:row_i instead.")
  (row_i m))

(cl:ensure-generic-function 'num_coln-val :lambda-list '(m))
(cl:defmethod num_coln-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:num_coln-val is deprecated.  Use balboa_core-msg:num_coln instead.")
  (num_coln m))

(cl:ensure-generic-function 'num_row-val :lambda-list '(m))
(cl:defmethod num_row-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:num_row-val is deprecated.  Use balboa_core-msg:num_row instead.")
  (num_row m))

(cl:ensure-generic-function 'sensor0-val :lambda-list '(m))
(cl:defmethod sensor0-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:sensor0-val is deprecated.  Use balboa_core-msg:sensor0 instead.")
  (sensor0 m))

(cl:ensure-generic-function 'sensor1-val :lambda-list '(m))
(cl:defmethod sensor1-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:sensor1-val is deprecated.  Use balboa_core-msg:sensor1 instead.")
  (sensor1 m))

(cl:ensure-generic-function 'sensor2-val :lambda-list '(m))
(cl:defmethod sensor2-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:sensor2-val is deprecated.  Use balboa_core-msg:sensor2 instead.")
  (sensor2 m))

(cl:ensure-generic-function 'sensor3-val :lambda-list '(m))
(cl:defmethod sensor3-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:sensor3-val is deprecated.  Use balboa_core-msg:sensor3 instead.")
  (sensor3 m))

(cl:ensure-generic-function 'sensor4-val :lambda-list '(m))
(cl:defmethod sensor4-val ((m <lineSensor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader balboa_core-msg:sensor4-val is deprecated.  Use balboa_core-msg:sensor4 instead.")
  (sensor4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lineSensor>) ostream)
  "Serializes a message object of type '<lineSensor>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'row_i)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_coln)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_row)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor4)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor4)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lineSensor>) istream)
  "Deserializes a message object of type '<lineSensor>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'row_i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_coln)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_row)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor0)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor0)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor4)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sensor4)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lineSensor>)))
  "Returns string type for a message object of type '<lineSensor>"
  "balboa_core/lineSensor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lineSensor)))
  "Returns string type for a message object of type 'lineSensor"
  "balboa_core/lineSensor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lineSensor>)))
  "Returns md5sum for a message object of type '<lineSensor>"
  "d21aa9e782a1fd0adaef4e4628723bc4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lineSensor)))
  "Returns md5sum for a message object of type 'lineSensor"
  "d21aa9e782a1fd0adaef4e4628723bc4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lineSensor>)))
  "Returns full string definition for message of type '<lineSensor>"
  (cl:format cl:nil "uint8 row_i~%uint8 num_coln~%uint8 num_row~%uint16 sensor0~%uint16 sensor1~%uint16 sensor2~%uint16 sensor3~%uint16 sensor4~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lineSensor)))
  "Returns full string definition for message of type 'lineSensor"
  (cl:format cl:nil "uint8 row_i~%uint8 num_coln~%uint8 num_row~%uint16 sensor0~%uint16 sensor1~%uint16 sensor2~%uint16 sensor3~%uint16 sensor4~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lineSensor>))
  (cl:+ 0
     1
     1
     1
     2
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lineSensor>))
  "Converts a ROS message object to a list"
  (cl:list 'lineSensor
    (cl:cons ':row_i (row_i msg))
    (cl:cons ':num_coln (num_coln msg))
    (cl:cons ':num_row (num_row msg))
    (cl:cons ':sensor0 (sensor0 msg))
    (cl:cons ':sensor1 (sensor1 msg))
    (cl:cons ':sensor2 (sensor2 msg))
    (cl:cons ':sensor3 (sensor3 msg))
    (cl:cons ':sensor4 (sensor4 msg))
))
