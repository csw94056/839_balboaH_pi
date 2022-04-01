
(cl:in-package :asdf)

(defsystem "balboa_core-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "balboaLL" :depends-on ("_package_balboaLL"))
    (:file "_package_balboaLL" :depends-on ("_package"))
    (:file "balboaMotorSpeeds" :depends-on ("_package_balboaMotorSpeeds"))
    (:file "_package_balboaMotorSpeeds" :depends-on ("_package"))
    (:file "lineSensor" :depends-on ("_package_lineSensor"))
    (:file "_package_lineSensor" :depends-on ("_package"))
  ))