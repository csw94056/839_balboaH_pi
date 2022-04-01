// Auto-generated. Do not edit!

// (in-package ball_detector.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ballDebug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sendDebugImages = null;
      this.sendDebugTimes = null;
    }
    else {
      if (initObj.hasOwnProperty('sendDebugImages')) {
        this.sendDebugImages = initObj.sendDebugImages
      }
      else {
        this.sendDebugImages = false;
      }
      if (initObj.hasOwnProperty('sendDebugTimes')) {
        this.sendDebugTimes = initObj.sendDebugTimes
      }
      else {
        this.sendDebugTimes = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ballDebug
    // Serialize message field [sendDebugImages]
    bufferOffset = _serializer.bool(obj.sendDebugImages, buffer, bufferOffset);
    // Serialize message field [sendDebugTimes]
    bufferOffset = _serializer.bool(obj.sendDebugTimes, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ballDebug
    let len;
    let data = new ballDebug(null);
    // Deserialize message field [sendDebugImages]
    data.sendDebugImages = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [sendDebugTimes]
    data.sendDebugTimes = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ball_detector/ballDebug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f0dbcd340db400b8721875b15029f990';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool sendDebugImages
    bool sendDebugTimes 
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ballDebug(null);
    if (msg.sendDebugImages !== undefined) {
      resolved.sendDebugImages = msg.sendDebugImages;
    }
    else {
      resolved.sendDebugImages = false
    }

    if (msg.sendDebugTimes !== undefined) {
      resolved.sendDebugTimes = msg.sendDebugTimes;
    }
    else {
      resolved.sendDebugTimes = false
    }

    return resolved;
    }
};

module.exports = ballDebug;
