;; Auto-generated. Do not edit!


(when (boundp 'balboa_core::lineSensor)
  (if (not (find-package "BALBOA_CORE"))
    (make-package "BALBOA_CORE"))
  (shadow 'lineSensor (find-package "BALBOA_CORE")))
(unless (find-package "BALBOA_CORE::LINESENSOR")
  (make-package "BALBOA_CORE::LINESENSOR"))

(in-package "ROS")
;;//! \htmlinclude lineSensor.msg.html


(defclass balboa_core::lineSensor
  :super ros::object
  :slots (_row_i _num_coln _num_row _sensor0 _sensor1 _sensor2 _sensor3 _sensor4 ))

(defmethod balboa_core::lineSensor
  (:init
   (&key
    ((:row_i __row_i) 0)
    ((:num_coln __num_coln) 0)
    ((:num_row __num_row) 0)
    ((:sensor0 __sensor0) 0)
    ((:sensor1 __sensor1) 0)
    ((:sensor2 __sensor2) 0)
    ((:sensor3 __sensor3) 0)
    ((:sensor4 __sensor4) 0)
    )
   (send-super :init)
   (setq _row_i (round __row_i))
   (setq _num_coln (round __num_coln))
   (setq _num_row (round __num_row))
   (setq _sensor0 (round __sensor0))
   (setq _sensor1 (round __sensor1))
   (setq _sensor2 (round __sensor2))
   (setq _sensor3 (round __sensor3))
   (setq _sensor4 (round __sensor4))
   self)
  (:row_i
   (&optional __row_i)
   (if __row_i (setq _row_i __row_i)) _row_i)
  (:num_coln
   (&optional __num_coln)
   (if __num_coln (setq _num_coln __num_coln)) _num_coln)
  (:num_row
   (&optional __num_row)
   (if __num_row (setq _num_row __num_row)) _num_row)
  (:sensor0
   (&optional __sensor0)
   (if __sensor0 (setq _sensor0 __sensor0)) _sensor0)
  (:sensor1
   (&optional __sensor1)
   (if __sensor1 (setq _sensor1 __sensor1)) _sensor1)
  (:sensor2
   (&optional __sensor2)
   (if __sensor2 (setq _sensor2 __sensor2)) _sensor2)
  (:sensor3
   (&optional __sensor3)
   (if __sensor3 (setq _sensor3 __sensor3)) _sensor3)
  (:sensor4
   (&optional __sensor4)
   (if __sensor4 (setq _sensor4 __sensor4)) _sensor4)
  (:serialization-length
   ()
   (+
    ;; uint8 _row_i
    1
    ;; uint8 _num_coln
    1
    ;; uint8 _num_row
    1
    ;; uint16 _sensor0
    2
    ;; uint16 _sensor1
    2
    ;; uint16 _sensor2
    2
    ;; uint16 _sensor3
    2
    ;; uint16 _sensor4
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _row_i
       (write-byte _row_i s)
     ;; uint8 _num_coln
       (write-byte _num_coln s)
     ;; uint8 _num_row
       (write-byte _num_row s)
     ;; uint16 _sensor0
       (write-word _sensor0 s)
     ;; uint16 _sensor1
       (write-word _sensor1 s)
     ;; uint16 _sensor2
       (write-word _sensor2 s)
     ;; uint16 _sensor3
       (write-word _sensor3 s)
     ;; uint16 _sensor4
       (write-word _sensor4 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _row_i
     (setq _row_i (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _num_coln
     (setq _num_coln (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _num_row
     (setq _num_row (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _sensor0
     (setq _sensor0 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _sensor1
     (setq _sensor1 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _sensor2
     (setq _sensor2 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _sensor3
     (setq _sensor3 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _sensor4
     (setq _sensor4 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get balboa_core::lineSensor :md5sum-) "d21aa9e782a1fd0adaef4e4628723bc4")
(setf (get balboa_core::lineSensor :datatype-) "balboa_core/lineSensor")
(setf (get balboa_core::lineSensor :definition-)
      "uint8 row_i
uint8 num_coln
uint8 num_row
uint16 sensor0
uint16 sensor1
uint16 sensor2
uint16 sensor3
uint16 sensor4
")



(provide :balboa_core/lineSensor "d21aa9e782a1fd0adaef4e4628723bc4")


