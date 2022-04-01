;; Auto-generated. Do not edit!


(when (boundp 'ball_detector::ballDebug)
  (if (not (find-package "BALL_DETECTOR"))
    (make-package "BALL_DETECTOR"))
  (shadow 'ballDebug (find-package "BALL_DETECTOR")))
(unless (find-package "BALL_DETECTOR::BALLDEBUG")
  (make-package "BALL_DETECTOR::BALLDEBUG"))

(in-package "ROS")
;;//! \htmlinclude ballDebug.msg.html


(defclass ball_detector::ballDebug
  :super ros::object
  :slots (_sendDebugImages _sendDebugTimes ))

(defmethod ball_detector::ballDebug
  (:init
   (&key
    ((:sendDebugImages __sendDebugImages) nil)
    ((:sendDebugTimes __sendDebugTimes) nil)
    )
   (send-super :init)
   (setq _sendDebugImages __sendDebugImages)
   (setq _sendDebugTimes __sendDebugTimes)
   self)
  (:sendDebugImages
   (&optional __sendDebugImages)
   (if __sendDebugImages (setq _sendDebugImages __sendDebugImages)) _sendDebugImages)
  (:sendDebugTimes
   (&optional __sendDebugTimes)
   (if __sendDebugTimes (setq _sendDebugTimes __sendDebugTimes)) _sendDebugTimes)
  (:serialization-length
   ()
   (+
    ;; bool _sendDebugImages
    1
    ;; bool _sendDebugTimes
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _sendDebugImages
       (if _sendDebugImages (write-byte -1 s) (write-byte 0 s))
     ;; bool _sendDebugTimes
       (if _sendDebugTimes (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _sendDebugImages
     (setq _sendDebugImages (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _sendDebugTimes
     (setq _sendDebugTimes (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ball_detector::ballDebug :md5sum-) "f0dbcd340db400b8721875b15029f990")
(setf (get ball_detector::ballDebug :datatype-) "ball_detector/ballDebug")
(setf (get ball_detector::ballDebug :definition-)
      "bool sendDebugImages
bool sendDebugTimes 

")



(provide :ball_detector/ballDebug "f0dbcd340db400b8721875b15029f990")


