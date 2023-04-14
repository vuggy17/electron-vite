import {extractText, getAvailableOCRLanguage} from '#preload';

import type {TextDetectionPort} from '../../ports/text-detection';
import type {Language} from './../entities/language';

export class TextDetectionService implements TextDetectionPort {
  async getSupportedLanguages(): Promise<Language[]> {
    const langs = await getAvailableOCRLanguage();
    return langs;
  }
  async getTextFromImage(image: File, language: string): Promise<string> {
    const {width, height, buffer} = await this.getImageMetadata(image);

    return extractText(buffer, language, width, height);
  }

  getTargetId(): Promise<string> {
    throw new Error('Method not implemented.');
  }
  attachCapturer(_targetId: string): Promise<boolean> {
    throw new Error('Method not implemented.');
  }

  private async getImageMetadata(
    image: File,
  ): Promise<{width: number; height: number; buffer: ArrayBuffer}> {
    return new Promise((resolve, reject) => {
      const canvas = document.createElement('canvas');
      const ctx = canvas.getContext('2d');

      const img = new Image();

      const objectUrl = URL.createObjectURL(image);
      img.onload = function () {
        // make canvas same size as image
        canvas.width = img.width;
        canvas.height = img.height;

        ctx!.drawImage(img, 0, 0);

        const result = ctx!.getImageData(0, 0, canvas.width, canvas.height);
        resolve({width: result.width, height: result.height, buffer: result.data.buffer});
        URL.revokeObjectURL(objectUrl);
      };

      img.src = objectUrl;
    });
  }
}
