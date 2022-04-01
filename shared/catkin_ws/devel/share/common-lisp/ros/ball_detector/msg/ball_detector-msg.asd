
(cl:in-package :asdf)

(defsystem "ball_detector-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ballDebug" :depends-on ("_package_ballDebug"))
    (:file "_package_ballDebug" :depends-on ("_package"))
    (:file "ballLocation" :depends-on ("_package_ballLocation"))
    (:file "_package_ballLocation" :depends-on ("_package"))
    (:file "debugTimes" :depends-on ("_package_debugTimes"))
    (:file "_package_debugTimes" :depends-on ("_package"))
  ))