// Auto-generated. Do not edit!

// (in-package balboa_core.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class lineSensor {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.row_i = null;
      this.num_coln = null;
      this.num_row = null;
      this.sensor0 = null;
      this.sensor1 = null;
      this.sensor2 = null;
      this.sensor3 = null;
      this.sensor4 = null;
    }
    else {
      if (initObj.hasOwnProperty('row_i')) {
        this.row_i = initObj.row_i
      }
      else {
        this.row_i = 0;
      }
      if (initObj.hasOwnProperty('num_coln')) {
        this.num_coln = initObj.num_coln
      }
      else {
        this.num_coln = 0;
      }
      if (initObj.hasOwnProperty('num_row')) {
        this.num_row = initObj.num_row
      }
      else {
        this.num_row = 0;
      }
      if (initObj.hasOwnProperty('sensor0')) {
        this.sensor0 = initObj.sensor0
      }
      else {
        this.sensor0 = 0;
      }
      if (initObj.hasOwnProperty('sensor1')) {
        this.sensor1 = initObj.sensor1
      }
      else {
        this.sensor1 = 0;
      }
      if (initObj.hasOwnProperty('sensor2')) {
        this.sensor2 = initObj.sensor2
      }
      else {
        this.sensor2 = 0;
      }
      if (initObj.hasOwnProperty('sensor3')) {
        this.sensor3 = initObj.sensor3
      }
      else {
        this.sensor3 = 0;
      }
      if (initObj.hasOwnProperty('sensor4')) {
        this.sensor4 = initObj.sensor4
      }
      else {
        this.sensor4 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lineSensor
    // Serialize message field [row_i]
    bufferOffset = _serializer.uint8(obj.row_i, buffer, bufferOffset);
    // Serialize message field [num_coln]
    bufferOffset = _serializer.uint8(obj.num_coln, buffer, bufferOffset);
    // Serialize message field [num_row]
    bufferOffset = _serializer.uint8(obj.num_row, buffer, bufferOffset);
    // Serialize message field [sensor0]
    bufferOffset = _serializer.uint16(obj.sensor0, buffer, bufferOffset);
    // Serialize message field [sensor1]
    bufferOffset = _serializer.uint16(obj.sensor1, buffer, bufferOffset);
    // Serialize message field [sensor2]
    bufferOffset = _serializer.uint16(obj.sensor2, buffer, bufferOffset);
    // Serialize message field [sensor3]
    bufferOffset = _serializer.uint16(obj.sensor3, buffer, bufferOffset);
    // Serialize message field [sensor4]
    bufferOffset = _serializer.uint16(obj.sensor4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lineSensor
    let len;
    let data = new lineSensor(null);
    // Deserialize message field [row_i]
    data.row_i = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [num_coln]
    data.num_coln = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [num_row]
    data.num_row = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sensor0]
    data.sensor0 = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [sensor1]
    data.sensor1 = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [sensor2]
    data.sensor2 = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [sensor3]
    data.sensor3 = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [sensor4]
    data.sensor4 = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'balboa_core/lineSensor';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd21aa9e782a1fd0adaef4e4628723bc4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 row_i
    uint8 num_coln
    uint8 num_row
    uint16 sensor0
    uint16 sensor1
    uint16 sensor2
    uint16 sensor3
    uint16 sensor4
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lineSensor(null);
    if (msg.row_i !== undefined) {
      resolved.row_i = msg.row_i;
    }
    else {
      resolved.row_i = 0
    }

    if (msg.num_coln !== undefined) {
      resolved.num_coln = msg.num_coln;
    }
    else {
      resolved.num_coln = 0
    }

    if (msg.num_row !== undefined) {
      resolved.num_row = msg.num_row;
    }
    else {
      resolved.num_row = 0
    }

    if (msg.sensor0 !== undefined) {
      resolved.sensor0 = msg.sensor0;
    }
    else {
      resolved.sensor0 = 0
    }

    if (msg.sensor1 !== undefined) {
      resolved.sensor1 = msg.sensor1;
    }
    else {
      resolved.sensor1 = 0
    }

    if (msg.sensor2 !== undefined) {
      resolved.sensor2 = msg.sensor2;
    }
    else {
      resolved.sensor2 = 0
    }

    if (msg.sensor3 !== undefined) {
      resolved.sensor3 = msg.sensor3;
    }
    else {
      resolved.sensor3 = 0
    }

    if (msg.sensor4 !== undefined) {
      resolved.sensor4 = msg.sensor4;
    }
    else {
      resolved.sensor4 = 0
    }

    return resolved;
    }
};

module.exports = lineSensor;
