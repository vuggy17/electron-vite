import {Language} from './../entities/language';
import type {TextDetectionPort} from '../../ports/text-detection';
// import {getAvailableOCRLanguage} from '#preload';
export class TextDetectionService implements TextDetectionPort {
  async getSupportedLanguages(): Promise<Language[]> {
    // throw new Error('Method not implemented.');

    // const langs = await getAvailableOCRLanguage();

    return [
      new Language('en', 'English'),
      new Language('zh', 'Chinese'),
      new Language('ja', 'Japanese'),
    ];
  }
  getTextFromImage(_image: string, _language: Language): Promise<string> {
    throw new Error('Method not implemented.');
  }
  getTargetId(): Promise<string> {
    throw new Error('Method not implemented.');
  }
  attachCapturer(_targetId: string): Promise<boolean> {
    throw new Error('Method not implemented.');
  }
}
