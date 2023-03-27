_ByteOrder = function () {
  this.littleEndian = 0;
  this.bigEndian = 1;
}
exports.ByteOrder = new _ByteOrder();

_FileOpenDisposition = function () {
  this.openExisting = 0;
  this.openAlways = 1;
  this.createNew = 2;
  this.createAlways = 3;
  this.truncateExisting = 4;
}
exports.FileOpenDisposition = new _FileOpenDisposition();

_InputStreamOptions = function () {
  this.none = 0;
  this.partial = 1;
  this.readAhead = 2;
}
exports.InputStreamOptions = new _InputStreamOptions();

_UnicodeEncoding = function () {
  this.utf8 = 0;
  this.utf16LE = 1;
  this.utf16BE = 2;
}
exports.UnicodeEncoding = new _UnicodeEncoding();

Buffer = (function () {
  var cls = function Buffer() {
    this.length = new Number();
    this.capacity = new Number();
  };
  
var cls = function Buffer(capacity) {
      this.length = new Number();
      this.capacity = new Number();
};


  cls.createCopyFromMemoryBuffer = function createCopyFromMemoryBuffer(input) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="input" type="Object">A param.</param>
    /// <returns type="Buffer" />
    /// </signature>
    return new Buffer();
  }


  cls.createMemoryBufferOverIBuffer = function createMemoryBufferOverIBuffer(input) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="input" type="IBuffer">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.Buffer = Buffer;

DataReader = (function () {
  var cls = function DataReader() {
    this.unicodeEncoding = new UnicodeEncoding();
    this.inputStreamOptions = new InputStreamOptions();
    this.byteOrder = new ByteOrder();
    this.unconsumedBufferLength = new Number();
  };
  
var cls = function DataReader(inputStream) {
      this.unicodeEncoding = new UnicodeEncoding();
      this.inputStreamOptions = new InputStreamOptions();
      this.byteOrder = new ByteOrder();
      this.unconsumedBufferLength = new Number();
};


  cls.prototype.loadAsync = function loadAsync(count, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="count" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.readByte = function readByte() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readBytes = function () {
}

  cls.prototype.readBuffer = function readBuffer(length) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="length" type="Number">A param.</param>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.readBoolean = function readBoolean() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.readGuid = function readGuid() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.readInt16 = function readInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readInt32 = function readInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readInt64 = function readInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt16 = function readUInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt32 = function readUInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt64 = function readUInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readSingle = function readSingle() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readDouble = function readDouble() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readString = function readString(codeUnitCount) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="codeUnitCount" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.readDateTime = function readDateTime() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Date" />
    /// </signature>
    return new Date();
  }


  cls.prototype.readTimeSpan = function readTimeSpan() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.detachBuffer = function detachBuffer() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.detachStream = function detachStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  cls.prototype.close = function close() {
}


  cls.fromBuffer = function fromBuffer(buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <returns type="DataReader" />
    /// </signature>
    return new DataReader();
  }


  return cls;
}) ();
exports.DataReader = DataReader;

DataReaderLoadOperation = (function () {
  var cls = function DataReaderLoadOperation() {
    this.errorCode = new Number();
    this.id = new Number();
    this.status = new Number();
    this.completed = new Object();
  };
  

  cls.prototype.getResults = function getResults() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.cancel = function cancel() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.DataReaderLoadOperation = DataReaderLoadOperation;

DataWriter = (function () {
  var cls = function DataWriter() {
    this.unicodeEncoding = new UnicodeEncoding();
    this.byteOrder = new ByteOrder();
    this.unstoredBufferLength = new Number();
  };
  
var cls = function DataWriter(outputStream) {
      this.unicodeEncoding = new UnicodeEncoding();
      this.byteOrder = new ByteOrder();
      this.unstoredBufferLength = new Number();
};


  cls.prototype.storeAsync = function storeAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.writeByte = function writeByte(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBytes = function writeBytes(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBuffer = function writeBuffer(buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }

cls.prototype.writeBuffer = function writeBuffer(buffer, start, count) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="start" type="Number">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBoolean = function writeBoolean(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.writeGuid = function writeGuid(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt16 = function writeInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt32 = function writeInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt64 = function writeInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt16 = function writeUInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt32 = function writeUInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt64 = function writeUInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeSingle = function writeSingle(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeDouble = function writeDouble(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeDateTime = function writeDateTime(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Date">A param.</param>
    /// </signature>
  }


  cls.prototype.writeTimeSpan = function writeTimeSpan(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeString = function writeString(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.measureString = function measureString(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.detachBuffer = function detachBuffer() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.detachStream = function detachStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.DataWriter = DataWriter;

DataWriterStoreOperation = (function () {
  var cls = function DataWriterStoreOperation() {
    this.errorCode = new Number();
    this.id = new Number();
    this.status = new Number();
    this.completed = new Object();
  };
  

  cls.prototype.getResults = function getResults() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.cancel = function cancel() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.DataWriterStoreOperation = DataWriterStoreOperation;

FileInputStream = (function () {
  var cls = function FileInputStream() {
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.FileInputStream = FileInputStream;

FileOutputStream = (function () {
  var cls = function FileOutputStream() {
  };
  

  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.FileOutputStream = FileOutputStream;

FileRandomAccessStream = (function () {
  var cls = function FileRandomAccessStream() {
    this.size = new Number();
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getInputStreamAt = function getInputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  cls.prototype.seek = function seek(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.cloneStream = function cloneStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IRandomAccessStream" />
    /// </signature>
    return new IRandomAccessStream();
  }


  cls.prototype.close = function close() {
}


  cls.openAsync = function openAsync(filePath, accessMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="accessMode" type="Number">A param.</param>
    /// </signature>
  }

cls.openAsync = function openAsync(filePath, accessMode, sharingOptions, openDisposition, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="accessMode" type="Number">A param.</param>
    /// <param name="sharingOptions" type="Number">A param.</param>
    /// <param name="openDisposition" type="FileOpenDisposition">A param.</param>
    /// </signature>
  }



  cls.openTransactedWriteAsync = function openTransactedWriteAsync(filePath, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="filePath" type="String">A param.</param>
    /// </signature>
  }

cls.openTransactedWriteAsync = function openTransactedWriteAsync(filePath, openOptions, openDisposition, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="openOptions" type="Number">A param.</param>
    /// <param name="openDisposition" type="FileOpenDisposition">A param.</param>
    /// </signature>
  }



  cls.openForUserAsync = function openForUserAsync(user, filePath, accessMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="accessMode" type="Number">A param.</param>
    /// </signature>
  }

cls.openForUserAsync = function openForUserAsync(user, filePath, accessMode, sharingOptions, openDisposition, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="accessMode" type="Number">A param.</param>
    /// <param name="sharingOptions" type="Number">A param.</param>
    /// <param name="openDisposition" type="FileOpenDisposition">A param.</param>
    /// </signature>
  }



  cls.openTransactedWriteForUserAsync = function openTransactedWriteForUserAsync(user, filePath, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="filePath" type="String">A param.</param>
    /// </signature>
  }

cls.openTransactedWriteForUserAsync = function openTransactedWriteForUserAsync(user, filePath, openOptions, openDisposition, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="filePath" type="String">A param.</param>
    /// <param name="openOptions" type="Number">A param.</param>
    /// <param name="openDisposition" type="FileOpenDisposition">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.FileRandomAccessStream = FileRandomAccessStream;

IBuffer = (function () {
  var cls = function IBuffer() {
    this.capacity = new Number();
    this.length = new Number();
  };
  

  return cls;
}) ();
exports.IBuffer = IBuffer;

IContentTypeProvider = (function () {
  var cls = function IContentTypeProvider() {
    this.contentType = new String();
  };
  

  return cls;
}) ();
exports.IContentTypeProvider = IContentTypeProvider;

IDataReader = (function () {
  var cls = function IDataReader() {
    this.byteOrder = new ByteOrder();
    this.inputStreamOptions = new InputStreamOptions();
    this.unconsumedBufferLength = new Number();
    this.unicodeEncoding = new UnicodeEncoding();
  };
  

  cls.prototype.loadAsync = function loadAsync(count, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="count" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.readByte = function readByte() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readBytes = function () {
}

  cls.prototype.readBuffer = function readBuffer(length) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="length" type="Number">A param.</param>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.readBoolean = function readBoolean() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.readGuid = function readGuid() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.readInt16 = function readInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readInt32 = function readInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readInt64 = function readInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt16 = function readUInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt32 = function readUInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readUInt64 = function readUInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readSingle = function readSingle() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readDouble = function readDouble() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.readString = function readString(codeUnitCount) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="codeUnitCount" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.readDateTime = function readDateTime() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Date" />
    /// </signature>
    return new Date();
  }


  cls.prototype.readTimeSpan = function readTimeSpan() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.detachBuffer = function detachBuffer() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.detachStream = function detachStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  return cls;
}) ();
exports.IDataReader = IDataReader;

IDataWriter = (function () {
  var cls = function IDataWriter() {
    this.byteOrder = new ByteOrder();
    this.unicodeEncoding = new UnicodeEncoding();
    this.unstoredBufferLength = new Number();
  };
  

  cls.prototype.storeAsync = function storeAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.writeByte = function writeByte(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBytes = function writeBytes(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBuffer = function writeBuffer(buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }

cls.prototype.writeBuffer = function writeBuffer(buffer, start, count) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="start" type="Number">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeBoolean = function writeBoolean(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.writeGuid = function writeGuid(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt16 = function writeInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt32 = function writeInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeInt64 = function writeInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt16 = function writeUInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt32 = function writeUInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeUInt64 = function writeUInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeSingle = function writeSingle(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeDouble = function writeDouble(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeDateTime = function writeDateTime(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Date">A param.</param>
    /// </signature>
  }


  cls.prototype.writeTimeSpan = function writeTimeSpan(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeString = function writeString(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.measureString = function measureString(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.detachBuffer = function detachBuffer() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.detachStream = function detachStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  return cls;
}) ();
exports.IDataWriter = IDataWriter;

IInputStream = (function () {
  var cls = function IInputStream() {
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IInputStream = IInputStream;

IInputStreamReference = (function () {
  var cls = function IInputStreamReference() {
  };
  

  cls.prototype.openSequentialReadAsync = function openSequentialReadAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.IInputStreamReference = IInputStreamReference;

IOutputStream = (function () {
  var cls = function IOutputStream() {
  };
  

  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.IOutputStream = IOutputStream;

IPropertySetSerializer = (function () {
  var cls = function IPropertySetSerializer() {
  };
  

  cls.prototype.serialize = function serialize(propertySet) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertySet" type="Object">A param.</param>
    /// <returns type="IBuffer" />
    /// </signature>
    return new IBuffer();
  }


  cls.prototype.deserialize = function deserialize(propertySet, buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertySet" type="Object">A param.</param>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IPropertySetSerializer = IPropertySetSerializer;

IRandomAccessStream = (function () {
  var cls = function IRandomAccessStream() {
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
    this.size = new Number();
  };
  

  cls.prototype.getInputStreamAt = function getInputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  cls.prototype.seek = function seek(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.cloneStream = function cloneStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IRandomAccessStream" />
    /// </signature>
    return new IRandomAccessStream();
  }


  return cls;
}) ();
exports.IRandomAccessStream = IRandomAccessStream;

IRandomAccessStreamReference = (function () {
  var cls = function IRandomAccessStreamReference() {
  };
  

  cls.prototype.openReadAsync = function openReadAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.IRandomAccessStreamReference = IRandomAccessStreamReference;

IRandomAccessStreamWithContentType = (function () {
  var cls = function IRandomAccessStreamWithContentType() {
  };
  

  return cls;
}) ();
exports.IRandomAccessStreamWithContentType = IRandomAccessStreamWithContentType;

InMemoryRandomAccessStream = (function () {
  var cls = function InMemoryRandomAccessStream() {
    this.size = new Number();
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getInputStreamAt = function getInputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  cls.prototype.seek = function seek(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.cloneStream = function cloneStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IRandomAccessStream" />
    /// </signature>
    return new IRandomAccessStream();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.InMemoryRandomAccessStream = InMemoryRandomAccessStream;

InputStreamOverStream = (function () {
  var cls = function InputStreamOverStream() {
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.InputStreamOverStream = InputStreamOverStream;

OutputStreamOverStream = (function () {
  var cls = function OutputStreamOverStream() {
  };
  

  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.OutputStreamOverStream = OutputStreamOverStream;

RandomAccessStream = (function () {
  var cls = function RandomAccessStream() {
  };
  

  cls.copyAsync = function copyAsync(source, destination, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="IInputStream">A param.</param>
    /// <param name="destination" type="IOutputStream">A param.</param>
    /// </signature>
  }

cls.copyAsync = function copyAsync(source, destination, bytesToCopy, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="IInputStream">A param.</param>
    /// <param name="destination" type="IOutputStream">A param.</param>
    /// <param name="bytesToCopy" type="Number">A param.</param>
    /// </signature>
  }



  cls.copyAndCloseAsync = function copyAndCloseAsync(source, destination, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="IInputStream">A param.</param>
    /// <param name="destination" type="IOutputStream">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.RandomAccessStream = RandomAccessStream;

RandomAccessStreamOverStream = (function () {
  var cls = function RandomAccessStreamOverStream() {
    this.size = new Number();
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="InputStreamOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="IBuffer">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getInputStreamAt = function getInputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IInputStream" />
    /// </signature>
    return new IInputStream();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="IOutputStream" />
    /// </signature>
    return new IOutputStream();
  }


  cls.prototype.seek = function seek(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.cloneStream = function cloneStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IRandomAccessStream" />
    /// </signature>
    return new IRandomAccessStream();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.RandomAccessStreamOverStream = RandomAccessStreamOverStream;

RandomAccessStreamReference = (function () {
  var cls = function RandomAccessStreamReference() {
  };
  

  cls.prototype.openReadAsync = function openReadAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.createFromFile = function createFromFile(file) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="Object">A param.</param>
    /// <returns type="RandomAccessStreamReference" />
    /// </signature>
    return new RandomAccessStreamReference();
  }


  cls.createFromUri = function createFromUri(uri) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="uri" type="Object">A param.</param>
    /// <returns type="RandomAccessStreamReference" />
    /// </signature>
    return new RandomAccessStreamReference();
  }


  cls.createFromStream = function createFromStream(stream) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="stream" type="IRandomAccessStream">A param.</param>
    /// <returns type="RandomAccessStreamReference" />
    /// </signature>
    return new RandomAccessStreamReference();
  }


  return cls;
}) ();
exports.RandomAccessStreamReference = RandomAccessStreamReference;

