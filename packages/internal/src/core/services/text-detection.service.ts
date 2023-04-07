import {extractText, getAvailableOCRLanguage} from '#preload';

import type {TextDetectionPort} from '../../ports/text-detection';
import type {Language} from './../entities/language';

export class TextDetectionService implements TextDetectionPort {
  async getSupportedLanguages(): Promise<Language[]> {
    const langs = await getAvailableOCRLanguage();
    return langs;
  }
  async getTextFromImage(image: string, language: Language): Promise<string> {
    return extractText(image, language.code);
  }
  getTargetId(): Promise<string> {
    throw new Error('Method not implemented.');
  }
  attachCapturer(_targetId: string): Promise<boolean> {
    throw new Error('Method not implemented.');
  }
}
