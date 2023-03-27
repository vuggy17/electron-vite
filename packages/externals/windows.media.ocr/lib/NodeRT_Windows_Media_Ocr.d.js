  
Rect = (function () {
  var cls = function Rect() {
    };
  return cls;
}) ();
exports.Rect = Rect;


OcrEngine = (function () {
  var cls = function OcrEngine() {
    this.recognizerLanguage = new Object();
  };
  

  cls.prototype.recognizeAsync = function recognizeAsync(bitmap, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bitmap" type="Object">A param.</param>
    /// </signature>
  }


  cls.isLanguageSupported = function isLanguageSupported(language) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="language" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.tryCreateFromLanguage = function tryCreateFromLanguage(language) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="language" type="Object">A param.</param>
    /// <returns type="OcrEngine" />
    /// </signature>
    return new OcrEngine();
  }


  cls.tryCreateFromUserProfileLanguages = function tryCreateFromUserProfileLanguages() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="OcrEngine" />
    /// </signature>
    return new OcrEngine();
  }


  cls.availableRecognizerLanguages = new Object();
  cls.maxImageDimension = new Number();
  return cls;
}) ();
exports.OcrEngine = OcrEngine;

OcrLine = (function () {
  var cls = function OcrLine() {
    this.text = new String();
    this.words = new Object();
  };
  

  return cls;
}) ();
exports.OcrLine = OcrLine;

OcrResult = (function () {
  var cls = function OcrResult() {
    this.lines = new Object();
    this.text = new String();
    this.textAngle = new Number();
  };
  

  return cls;
}) ();
exports.OcrResult = OcrResult;

OcrWord = (function () {
  var cls = function OcrWord() {
    this.boundingRect = new Object();
    this.text = new String();
  };
  

  return cls;
}) ();
exports.OcrWord = OcrWord;

