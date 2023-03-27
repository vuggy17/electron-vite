  
BitmapBounds = (function () {
  var cls = function BitmapBounds() {
      this.x = new Number();
      this.y = new Number();
      this.width = new Number();
      this.height = new Number();
    };
  return cls;
}) ();
exports.BitmapBounds = BitmapBounds;


  
BitmapPlaneDescription = (function () {
  var cls = function BitmapPlaneDescription() {
      this.startIndex = new Number();
      this.width = new Number();
      this.height = new Number();
      this.stride = new Number();
    };
  return cls;
}) ();
exports.BitmapPlaneDescription = BitmapPlaneDescription;


  
BitmapSize = (function () {
  var cls = function BitmapSize() {
      this.width = new Number();
      this.height = new Number();
    };
  return cls;
}) ();
exports.BitmapSize = BitmapSize;


_BitmapAlphaMode = function () {
  this.premultiplied = 0;
  this.straight = 1;
  this.ignore = 2;
}
exports.BitmapAlphaMode = new _BitmapAlphaMode();

_BitmapBufferAccessMode = function () {
  this.read = 0;
  this.readWrite = 1;
  this.write = 2;
}
exports.BitmapBufferAccessMode = new _BitmapBufferAccessMode();

_BitmapFlip = function () {
  this.none = 0;
  this.horizontal = 1;
  this.vertical = 2;
}
exports.BitmapFlip = new _BitmapFlip();

_BitmapInterpolationMode = function () {
  this.nearestNeighbor = 0;
  this.linear = 1;
  this.cubic = 2;
  this.fant = 3;
}
exports.BitmapInterpolationMode = new _BitmapInterpolationMode();

_BitmapPixelFormat = function () {
  this.unknown = 0;
  this.rgba16 = 1;
  this.rgba8 = 2;
  this.gray16 = 3;
  this.gray8 = 4;
  this.bgra8 = 5;
  this.nv12 = 6;
  this.p010 = 7;
  this.yuy2 = 8;
}
exports.BitmapPixelFormat = new _BitmapPixelFormat();

_BitmapRotation = function () {
  this.none = 0;
  this.clockwise90Degrees = 1;
  this.clockwise180Degrees = 2;
  this.clockwise270Degrees = 3;
}
exports.BitmapRotation = new _BitmapRotation();

_ColorManagementMode = function () {
  this.doNotColorManage = 0;
  this.colorManageToSRgb = 1;
}
exports.ColorManagementMode = new _ColorManagementMode();

_ExifOrientationMode = function () {
  this.ignoreExifOrientation = 0;
  this.respectExifOrientation = 1;
}
exports.ExifOrientationMode = new _ExifOrientationMode();

_JpegSubsamplingMode = function () {
  this.default = 0;
  this.y4Cb2Cr0 = 1;
  this.y4Cb2Cr2 = 2;
  this.y4Cb4Cr4 = 3;
}
exports.JpegSubsamplingMode = new _JpegSubsamplingMode();

_PngFilterMode = function () {
  this.automatic = 0;
  this.none = 1;
  this.sub = 2;
  this.up = 3;
  this.average = 4;
  this.paeth = 5;
  this.adaptive = 6;
}
exports.PngFilterMode = new _PngFilterMode();

_TiffCompressionMode = function () {
  this.automatic = 0;
  this.none = 1;
  this.ccitt3 = 2;
  this.ccitt4 = 3;
  this.lzw = 4;
  this.rle = 5;
  this.zip = 6;
  this.lzwhDifferencing = 7;
}
exports.TiffCompressionMode = new _TiffCompressionMode();

BitmapBuffer = (function () {
  var cls = function BitmapBuffer() {
  };
  

  cls.prototype.getPlaneCount = function getPlaneCount() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getPlaneDescription = function getPlaneDescription(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="BitmapPlaneDescription" />
    /// </signature>
    return new BitmapPlaneDescription();
  }


  cls.prototype.createReference = function createReference() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.BitmapBuffer = BitmapBuffer;

BitmapCodecInformation = (function () {
  var cls = function BitmapCodecInformation() {
    this.codecId = new String();
    this.fileExtensions = new Object();
    this.friendlyName = new String();
    this.mimeTypes = new Object();
  };
  

  return cls;
}) ();
exports.BitmapCodecInformation = BitmapCodecInformation;

BitmapDecoder = (function () {
  var cls = function BitmapDecoder() {
    this.bitmapContainerProperties = new BitmapPropertiesView();
    this.decoderInformation = new BitmapCodecInformation();
    this.frameCount = new Number();
    this.bitmapAlphaMode = new BitmapAlphaMode();
    this.bitmapPixelFormat = new BitmapPixelFormat();
    this.bitmapProperties = new BitmapPropertiesView();
    this.dpiX = new Number();
    this.dpiY = new Number();
    this.orientedPixelHeight = new Number();
    this.orientedPixelWidth = new Number();
    this.pixelHeight = new Number();
    this.pixelWidth = new Number();
  };
  

  cls.prototype.getPreviewAsync = function getPreviewAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getFrameAsync = function getFrameAsync(frameIndex, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="frameIndex" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getThumbnailAsync = function getThumbnailAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getPixelDataAsync = function getPixelDataAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getPixelDataAsync = function getPixelDataAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  cls.createAsync = function createAsync(stream, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="stream" type="Object">A param.</param>
    /// </signature>
  }

cls.createAsync = function createAsync(decoderId, stream, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="decoderId" type="String">A param.</param>
    /// <param name="stream" type="Object">A param.</param>
    /// </signature>
  }



  cls.getDecoderInformationEnumerator = function getDecoderInformationEnumerator() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.bmpDecoderId = new String();
  cls.gifDecoderId = new String();
  cls.icoDecoderId = new String();
  cls.jpegDecoderId = new String();
  cls.jpegXRDecoderId = new String();
  cls.pngDecoderId = new String();
  cls.tiffDecoderId = new String();
  cls.heifDecoderId = new String();
  cls.webpDecoderId = new String();
  return cls;
}) ();
exports.BitmapDecoder = BitmapDecoder;

BitmapEncoder = (function () {
  var cls = function BitmapEncoder() {
    this.isThumbnailGenerated = new Boolean();
    this.generatedThumbnailWidth = new Number();
    this.generatedThumbnailHeight = new Number();
    this.bitmapContainerProperties = new BitmapProperties();
    this.bitmapProperties = new BitmapProperties();
    this.bitmapTransform = new BitmapTransform();
    this.encoderInformation = new BitmapCodecInformation();
  };
  

  cls.prototype.goToNextFrameAsync = function goToNextFrameAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.goToNextFrameAsync = function goToNextFrameAsync(encodingOptions, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="encodingOptions" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.setPixelData = function setPixelData(pixelFormat, alphaMode, width, height, dpiX, dpiY, pixels) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="width" type="Number">A param.</param>
    /// <param name="height" type="Number">A param.</param>
    /// <param name="dpiX" type="Number">A param.</param>
    /// <param name="dpiY" type="Number">A param.</param>
    /// <param name="pixels" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.setSoftwareBitmap = function setSoftwareBitmap(bitmap) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bitmap" type="SoftwareBitmap">A param.</param>
    /// </signature>
  }


  cls.createAsync = function createAsync(encoderId, stream, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="encoderId" type="String">A param.</param>
    /// <param name="stream" type="Object">A param.</param>
    /// </signature>
  }

cls.createAsync = function createAsync(encoderId, stream, encodingOptions, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="encoderId" type="String">A param.</param>
    /// <param name="stream" type="Object">A param.</param>
    /// <param name="encodingOptions" type="Object">A param.</param>
    /// </signature>
  }



  cls.createForTranscodingAsync = function createForTranscodingAsync(stream, bitmapDecoder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="stream" type="Object">A param.</param>
    /// <param name="bitmapDecoder" type="BitmapDecoder">A param.</param>
    /// </signature>
  }



  cls.createForInPlacePropertyEncodingAsync = function createForInPlacePropertyEncodingAsync(bitmapDecoder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bitmapDecoder" type="BitmapDecoder">A param.</param>
    /// </signature>
  }



  cls.getEncoderInformationEnumerator = function getEncoderInformationEnumerator() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.bmpEncoderId = new String();
  cls.gifEncoderId = new String();
  cls.jpegEncoderId = new String();
  cls.jpegXREncoderId = new String();
  cls.pngEncoderId = new String();
  cls.tiffEncoderId = new String();
  cls.heifEncoderId = new String();
  return cls;
}) ();
exports.BitmapEncoder = BitmapEncoder;

BitmapFrame = (function () {
  var cls = function BitmapFrame() {
    this.bitmapAlphaMode = new BitmapAlphaMode();
    this.bitmapPixelFormat = new BitmapPixelFormat();
    this.bitmapProperties = new BitmapPropertiesView();
    this.dpiX = new Number();
    this.dpiY = new Number();
    this.orientedPixelHeight = new Number();
    this.orientedPixelWidth = new Number();
    this.pixelHeight = new Number();
    this.pixelWidth = new Number();
  };
  

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getPixelDataAsync = function getPixelDataAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getPixelDataAsync = function getPixelDataAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.BitmapFrame = BitmapFrame;

BitmapProperties = (function () {
  var cls = function BitmapProperties() {
  };
  

  cls.prototype.setPropertiesAsync = function setPropertiesAsync(propertiesToSet, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertiesToSet" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getPropertiesAsync = function getPropertiesAsync(propertiesToRetrieve, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertiesToRetrieve" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.BitmapProperties = BitmapProperties;

BitmapPropertiesView = (function () {
  var cls = function BitmapPropertiesView() {
  };
  

  cls.prototype.getPropertiesAsync = function getPropertiesAsync(propertiesToRetrieve, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertiesToRetrieve" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.BitmapPropertiesView = BitmapPropertiesView;

BitmapPropertySet = (function () {
  var cls = function BitmapPropertySet() {
  };
  

  cls.prototype.lookup = function lookup(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="BitmapTypedValue" />
    /// </signature>
    return new BitmapTypedValue();
  }


  cls.prototype.hasKey = function hasKey(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getView = function getView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.insert = function insert(key, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <param name="value" type="BitmapTypedValue">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.remove = function remove(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.BitmapPropertySet = BitmapPropertySet;

BitmapTransform = (function () {
  var cls = function BitmapTransform() {
    this.scaledWidth = new Number();
    this.scaledHeight = new Number();
    this.rotation = new BitmapRotation();
    this.interpolationMode = new BitmapInterpolationMode();
    this.flip = new BitmapFlip();
    this.bounds = new BitmapBounds();
  };
  

  return cls;
}) ();
exports.BitmapTransform = BitmapTransform;

BitmapTypedValue = (function () {
  var cls = function BitmapTypedValue() {
    this.type = new Number();
    this.value = new Object();
  };
  
var cls = function BitmapTypedValue(value, type) {
      this.type = new Number();
      this.value = new Object();
};


  return cls;
}) ();
exports.BitmapTypedValue = BitmapTypedValue;

IBitmapFrame = (function () {
  var cls = function IBitmapFrame() {
    this.bitmapAlphaMode = new BitmapAlphaMode();
    this.bitmapPixelFormat = new BitmapPixelFormat();
    this.bitmapProperties = new BitmapPropertiesView();
    this.dpiX = new Number();
    this.dpiY = new Number();
    this.orientedPixelHeight = new Number();
    this.orientedPixelWidth = new Number();
    this.pixelHeight = new Number();
    this.pixelWidth = new Number();
  };
  

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getPixelDataAsync = function getPixelDataAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getPixelDataAsync = function getPixelDataAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IBitmapFrame = IBitmapFrame;

IBitmapFrameWithSoftwareBitmap = (function () {
  var cls = function IBitmapFrameWithSoftwareBitmap() {
  };
  

  cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// </signature>
  }

cls.prototype.getSoftwareBitmapAsync = function getSoftwareBitmapAsync(pixelFormat, alphaMode, transform, exifOrientationMode, colorManagementMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pixelFormat" type="BitmapPixelFormat">A param.</param>
    /// <param name="alphaMode" type="BitmapAlphaMode">A param.</param>
    /// <param name="transform" type="BitmapTransform">A param.</param>
    /// <param name="exifOrientationMode" type="ExifOrientationMode">A param.</param>
    /// <param name="colorManagementMode" type="ColorManagementMode">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IBitmapFrameWithSoftwareBitmap = IBitmapFrameWithSoftwareBitmap;

IBitmapPropertiesView = (function () {
  var cls = function IBitmapPropertiesView() {
  };
  

  cls.prototype.getPropertiesAsync = function getPropertiesAsync(propertiesToRetrieve, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertiesToRetrieve" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IBitmapPropertiesView = IBitmapPropertiesView;

ImageStream = (function () {
  var cls = function ImageStream() {
    this.contentType = new String();
    this.size = new Number();
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
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
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
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
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.ImageStream = ImageStream;

PixelDataProvider = (function () {
  var cls = function PixelDataProvider() {
  };
  

  cls.prototype.detachPixelData = function detachPixelData() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Array<Number>" />
    /// </signature>
    return new Array<Number>();
  }


  return cls;
}) ();
exports.PixelDataProvider = PixelDataProvider;

SoftwareBitmap = (function () {
  var cls = function SoftwareBitmap() {
    this.dpiY = new Number();
    this.dpiX = new Number();
    this.bitmapAlphaMode = new BitmapAlphaMode();
    this.bitmapPixelFormat = new BitmapPixelFormat();
    this.isReadOnly = new Boolean();
    this.pixelHeight = new Number();
    this.pixelWidth = new Number();
  };
  
var cls = function SoftwareBitmap(format, width, height) {
      this.dpiY = new Number();
      this.dpiX = new Number();
      this.bitmapAlphaMode = new BitmapAlphaMode();
      this.bitmapPixelFormat = new BitmapPixelFormat();
      this.isReadOnly = new Boolean();
      this.pixelHeight = new Number();
      this.pixelWidth = new Number();
};

var cls = function SoftwareBitmap(format, width, height, alpha) {
      this.dpiY = new Number();
      this.dpiX = new Number();
      this.bitmapAlphaMode = new BitmapAlphaMode();
      this.bitmapPixelFormat = new BitmapPixelFormat();
      this.isReadOnly = new Boolean();
      this.pixelHeight = new Number();
      this.pixelWidth = new Number();
};


  cls.prototype.lockBuffer = function lockBuffer(mode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="BitmapBufferAccessMode">A param.</param>
    /// <returns type="BitmapBuffer" />
    /// </signature>
    return new BitmapBuffer();
  }


  cls.prototype.copyTo = function copyTo(bitmap) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bitmap" type="SoftwareBitmap">A param.</param>
    /// </signature>
  }


  cls.prototype.copyFromBuffer = function copyFromBuffer(buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.copyToBuffer = function copyToBuffer(buffer) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getReadOnlyView = function getReadOnlyView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }


  cls.prototype.close = function close() {
}


  cls.createCopyFromSurfaceAsync = function createCopyFromSurfaceAsync(surface, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="surface" type="Object">A param.</param>
    /// </signature>
  }

cls.createCopyFromSurfaceAsync = function createCopyFromSurfaceAsync(surface, alpha, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="surface" type="Object">A param.</param>
    /// <param name="alpha" type="BitmapAlphaMode">A param.</param>
    /// </signature>
  }



  cls.copy = function copy(source) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="SoftwareBitmap">A param.</param>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }


  cls.convert = function convert(source, format) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="SoftwareBitmap">A param.</param>
    /// <param name="format" type="BitmapPixelFormat">A param.</param>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }

cls.convert = function convert(source, format, alpha) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="SoftwareBitmap">A param.</param>
    /// <param name="format" type="BitmapPixelFormat">A param.</param>
    /// <param name="alpha" type="BitmapAlphaMode">A param.</param>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }


  cls.createCopyFromBuffer = function createCopyFromBuffer(source, format, width, height) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="Object">A param.</param>
    /// <param name="format" type="BitmapPixelFormat">A param.</param>
    /// <param name="width" type="Number">A param.</param>
    /// <param name="height" type="Number">A param.</param>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }

cls.createCopyFromBuffer = function createCopyFromBuffer(source, format, width, height, alpha) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="Object">A param.</param>
    /// <param name="format" type="BitmapPixelFormat">A param.</param>
    /// <param name="width" type="Number">A param.</param>
    /// <param name="height" type="Number">A param.</param>
    /// <param name="alpha" type="BitmapAlphaMode">A param.</param>
    /// <returns type="SoftwareBitmap" />
    /// </signature>
    return new SoftwareBitmap();
  }


  return cls;
}) ();
exports.SoftwareBitmap = SoftwareBitmap;

