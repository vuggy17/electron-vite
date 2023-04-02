import type {TextDetectionPort} from '#internal';
import {TextDetectionService} from '../../../../internal/src/core/services/text-detection.service';
import LanguageAdapter from './adapter';
import {autoInjectable, inject, registry} from 'tsyringe';
import {TEXT_DETECTION_SERVICE} from '../../../../di';

@autoInjectable()
@registry([{token: 'text-detection-service', useClass: TextDetectionService}])
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

// // TODO: dependency injection so we don't need to expose real service to the outside
// const port = new TextDetectionService();
// const RealDetectTextController = new DetectTextController(port);
// export {RealDetectTextController as DetectTextController};
