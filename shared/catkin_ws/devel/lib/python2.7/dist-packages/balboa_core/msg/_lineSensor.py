# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from balboa_core/lineSensor.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class lineSensor(genpy.Message):
  _md5sum = "d21aa9e782a1fd0adaef4e4628723bc4"
  _type = "balboa_core/lineSensor"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 row_i
uint8 num_coln
uint8 num_row
uint16 sensor0
uint16 sensor1
uint16 sensor2
uint16 sensor3
uint16 sensor4"""
  __slots__ = ['row_i','num_coln','num_row','sensor0','sensor1','sensor2','sensor3','sensor4']
  _slot_types = ['uint8','uint8','uint8','uint16','uint16','uint16','uint16','uint16']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       row_i,num_coln,num_row,sensor0,sensor1,sensor2,sensor3,sensor4

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(lineSensor, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.row_i is None:
        self.row_i = 0
      if self.num_coln is None:
        self.num_coln = 0
      if self.num_row is None:
        self.num_row = 0
      if self.sensor0 is None:
        self.sensor0 = 0
      if self.sensor1 is None:
        self.sensor1 = 0
      if self.sensor2 is None:
        self.sensor2 = 0
      if self.sensor3 is None:
        self.sensor3 = 0
      if self.sensor4 is None:
        self.sensor4 = 0
    else:
      self.row_i = 0
      self.num_coln = 0
      self.num_row = 0
      self.sensor0 = 0
      self.sensor1 = 0
      self.sensor2 = 0
      self.sensor3 = 0
      self.sensor4 = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3B5H().pack(_x.row_i, _x.num_coln, _x.num_row, _x.sensor0, _x.sensor1, _x.sensor2, _x.sensor3, _x.sensor4))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 13
      (_x.row_i, _x.num_coln, _x.num_row, _x.sensor0, _x.sensor1, _x.sensor2, _x.sensor3, _x.sensor4,) = _get_struct_3B5H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3B5H().pack(_x.row_i, _x.num_coln, _x.num_row, _x.sensor0, _x.sensor1, _x.sensor2, _x.sensor3, _x.sensor4))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 13
      (_x.row_i, _x.num_coln, _x.num_row, _x.sensor0, _x.sensor1, _x.sensor2, _x.sensor3, _x.sensor4,) = _get_struct_3B5H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3B5H = None
def _get_struct_3B5H():
    global _struct_3B5H
    if _struct_3B5H is None:
        _struct_3B5H = struct.Struct("<3B5H")
    return _struct_3B5H
