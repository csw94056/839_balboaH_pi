
(cl:in-package :asdf)

(defsystem "landmark_self_sim-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "landmarkLocation" :depends-on ("_package_landmarkLocation"))
    (:file "_package_landmarkLocation" :depends-on ("_package"))
  ))