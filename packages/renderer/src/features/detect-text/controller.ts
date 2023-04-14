import {autoInjectable, inject} from 'tsyringe';

import type {TextDetectionPort} from '#internal/ports';
import {TEXT_DETECTION_SERVICE} from '#shared/lib/di/renderer';

import LanguageAdapter from './adapter';

@autoInjectable()
export class DetectTextController {
  private readonly textDetector: TextDetectionPort;

  constructor(@inject(TEXT_DETECTION_SERVICE) readonly _textDetector?: TextDetectionPort) {
    if (!_textDetector) {
      throw new ReferenceError(DetectTextController.constructor.name + 'has missing dependency');
    }
    this.textDetector = _textDetector;
  }

  async getSupportedLanguages() {
    const langs = await this.textDetector.getSupportedLanguages();
    return langs.map(LanguageAdapter.createLanguageFromInternal);
  }

  async detectFromImage(image: File, langCode: string) {
    // Need to convert image to buffer using canvas since original File.buffer is larger than buffer size of Window SoftwareBitmap can handle

    const texts = await this.textDetector.getTextFromImage(image, langCode);
    return texts;
  }

  async getAvailableLanguage() {
    const langs = await this.textDetector.getSupportedLanguages();
    return langs.map(LanguageAdapter.createLanguageFromInternal);
  }
}
