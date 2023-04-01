import {TextDetectionService} from './../../../../internal/src/core/services/text-detection.service';
import type {TextDetectionPort} from '#internal';
import LanguageAdapter from './adapter';

class DetectTextController {
  constructor(private readonly textDetector: TextDetectionPort) {}

  async getSupportedLanguages() {
    const langs = await this.textDetector.getSupportedLanguages();
    return langs.map(LanguageAdapter.createLanguageFromInternal);
  }

  async detectFromImage(image: string, langCode: string) {
    const language = LanguageAdapter.createLanguageFromCode(langCode);
    const texts = await this.textDetector.getTextFromImage(image, language);
    // do some format stuff
    return 'formatted' + texts;
  }

  async getAvailableLanguage() {
    const langs = await this.textDetector.getSupportedLanguages();
    return langs.map(LanguageAdapter.createLanguageFromInternal);
  }
}

// TODO: dependency injection so we don't need to expose real service to the outside
const port = new TextDetectionService();
const RealDetectTextController = new DetectTextController(port);
export {RealDetectTextController as DetectTextController};
