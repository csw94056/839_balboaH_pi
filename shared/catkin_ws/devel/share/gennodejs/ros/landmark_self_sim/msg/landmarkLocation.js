// Auto-generated. Do not edit!

// (in-package landmark_self_sim.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class landmarkLocation {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.xtop = null;
      this.ytop = null;
      this.xbottom = null;
      this.ybottom = null;
      this.height = null;
      this.code = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('xtop')) {
        this.xtop = initObj.xtop
      }
      else {
        this.xtop = 0;
      }
      if (initObj.hasOwnProperty('ytop')) {
        this.ytop = initObj.ytop
      }
      else {
        this.ytop = 0;
      }
      if (initObj.hasOwnProperty('xbottom')) {
        this.xbottom = initObj.xbottom
      }
      else {
        this.xbottom = 0;
      }
      if (initObj.hasOwnProperty('ybottom')) {
        this.ybottom = initObj.ybottom
      }
      else {
        this.ybottom = 0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0.0;
      }
      if (initObj.hasOwnProperty('code')) {
        this.code = initObj.code
      }
      else {
        this.code = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type landmarkLocation
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [xtop]
    bufferOffset = _serializer.int32(obj.xtop, buffer, bufferOffset);
    // Serialize message field [ytop]
    bufferOffset = _serializer.int32(obj.ytop, buffer, bufferOffset);
    // Serialize message field [xbottom]
    bufferOffset = _serializer.int32(obj.xbottom, buffer, bufferOffset);
    // Serialize message field [ybottom]
    bufferOffset = _serializer.int32(obj.ybottom, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.float64(obj.height, buffer, bufferOffset);
    // Serialize message field [code]
    bufferOffset = _serializer.int32(obj.code, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type landmarkLocation
    let len;
    let data = new landmarkLocation(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [xtop]
    data.xtop = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ytop]
    data.ytop = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [xbottom]
    data.xbottom = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ybottom]
    data.ybottom = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [code]
    data.code = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'landmark_self_sim/landmarkLocation';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5fff4f104cc29dd1741797346a6aa89e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    # The x,y location of the top and bottom point of the detected landmark.
    int32 xtop
    int32 ytop
    int32 xbottom
    int32 ybottom
    
    # Height of the landmark as computed as the distance between the top
    # and bottom points.
    float64 height
    
    # The landmark code id number which should can range from 0 to 255.  If
    # this is -1 then it means the code was not correctly read (and the
    # above points may not be accurate).
    int32 code
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new landmarkLocation(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.xtop !== undefined) {
      resolved.xtop = msg.xtop;
    }
    else {
      resolved.xtop = 0
    }

    if (msg.ytop !== undefined) {
      resolved.ytop = msg.ytop;
    }
    else {
      resolved.ytop = 0
    }

    if (msg.xbottom !== undefined) {
      resolved.xbottom = msg.xbottom;
    }
    else {
      resolved.xbottom = 0
    }

    if (msg.ybottom !== undefined) {
      resolved.ybottom = msg.ybottom;
    }
    else {
      resolved.ybottom = 0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0.0
    }

    if (msg.code !== undefined) {
      resolved.code = msg.code;
    }
    else {
      resolved.code = 0
    }

    return resolved;
    }
};

module.exports = landmarkLocation;
