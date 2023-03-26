// TODO: remove this when we actually implement the ocr module
/* eslint-disable @typescript-eslint/no-unused-vars */
import type {IpcMainInvokeEvent} from 'electron';
import {ipcMain} from 'electron';
import Module from './base-module';
import Channels from '../../../../shared/lib/ipc-channels';
import {asyncWrapper} from '../utils/error-wrapper';

export default class OcrModule extends Module {
  async load() {
    ipcMain.handle(Channels.OCR_EXTRACT, asyncWrapper(this.extractText));
    ipcMain.handle(Channels.OCR_VALIDATE_LANGUAGE, asyncWrapper(this.validateLanguage));
  }

  /**
   * extract text from the given image
   * @param _e
   * @param data
   * @param language
   */
  private async extractText(_e: IpcMainInvokeEvent, data: string, language: string) {
    throw new Error('not implemented yet');
  }

  /**
   * check if the given language is supported by the window ocr engine
   * @param _e
   * @param language
   */
  private async validateLanguage(_e: IpcMainInvokeEvent, language: string) {
    throw new Error('not implemented yet');
  }
}
