/* eslint-disable max-classes-per-file */
/* eslint-disable @typescript-eslint/ban-types */
declare module '@nodert-win11-22h2/windows.media.ocr' {
  export class Rect {
    constructor();
  }

  export class OcrEngine {
    static availableRecognizerLanguages: Object;

    static maxImageDimension: number;

    recognizerLanguage: Object;
    constructor();

    static isLanguageSupported(language: Object): boolean;

    static tryCreateFromLanguage(language: Object): OcrEngine;

    static tryCreateFromUserProfileLanguages(): OcrEngine;

    recognizeAsync(
      bitmap: Object,
      callback: (error: Error, result: OcrResult) => void
    ): void;
  }

  export class OcrLine {
    text: string;

    size: number;

    words: OcrWord[] & { size: number };
    constructor();
  }

  export class OcrResult {
    lines: OcrLine[] & { size: number };

    text: string;

    textAngle: number;
    constructor();
  }

  export class OcrWord {
    boundingRect: {
      bottom: number;
      height: number;
      left: number;
      right: number;
      top: number;
      width: number;
      x: number;
      y: number;
    };

    text: string;
    constructor();
  }
}
