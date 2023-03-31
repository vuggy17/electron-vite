import type {TextDetectionPort} from '../../ports/text-detection';

export class TextDetectionService implements TextDetectionPort {
  getTextFromImage(_image: string, _language: string): Promise<string> {
    throw new Error('Method not implemented.');
  }
  getTargetId(): Promise<string> {
    throw new Error('Method not implemented.');
  }
  attachCapturer(_targetId: string): Promise<boolean> {
    throw new Error('Method not implemented.');
  }
}
