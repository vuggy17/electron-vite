import {Language as WinrtLanguage} from 'windows.globalization';
import {OcrEngine} from 'windows.media.ocr';

// TODO: remove this when we actually implement the ocr module
/* eslint-disable @typescript-eslint/no-unused-vars */
import type {IpcMainInvokeEvent} from 'electron';
import {ipcMain} from 'electron';
import Module from './base-module';
import Channels from '#shared/lib/ipc-channels';
import logger from '/@/utils/logger';
import {WinrtParser} from '../utils/winrt-adapter';
import type {Language} from '../../../internal/src/core/entities';

export default class OcrModule extends Module {
  async load() {
    ipcMain.handle(Channels.OCR_EXTRACT, this.extractText.bind(this));
    ipcMain.handle(Channels.OCR_CHECK_LANGUAGE, this.hasSupport.bind(this));
    ipcMain.handle(Channels.OCR_GET_AVAILABLE_LANGUAGE, this.getAvailableLanguages.bind(this));
  }

  previousText = '';
  DIFF_THRESHOLD = 0.8;

  /**
   * extract text from the given image
   * @param _e
   * @param data
   * @param language
   */
  private async extractText(_e: IpcMainInvokeEvent, data: string, language: string) {
    const languageSupported = await this.hasSupport(_e, language);
    if (!languageSupported) {
      throw new Error('Language not supported');
    }
    const result = await this.tryExtract(data, language);
    this.previousText = result;
    return result;
  }

  /**
   * check if the given language is supported by the window ocr engine
   * @param _e
   * @param language
   */
  private async hasSupport(_e: IpcMainInvokeEvent, language: string) {
    return true;
  }

  /**
   * check the difference between the given text and the text in the given image
   */
  private checkDiff(currentResutl: string): number {
    return 0.5;
    throw new Error('not implemented yet');
  }

  private async extractTextFromImage(image: string, lang: string): Promise<string> {
    const language = new WinrtLanguage('en-US');
    console.log(OcrEngine.isLanguageSupported(language));
    return 'Google Translate is an online translation tool developed by Google. It provides website interfaces, mobile apps for Android and iOS operating systems, and application programming interfaces that help developers build web browser extensions and software applications.';
  }

  /**
   *
   * @param image base64 string of the image
   */
  public async tryExtract(image: string, lang: string): Promise<string> {
    try {
      const currentText = await this.extractTextFromImage(image, lang);
      if (this.checkDiff(currentText) <= this.DIFF_THRESHOLD) {
        return currentText;
      }
      return this.previousText;
    } catch (error) {
      logger.error(this.constructor.name, error);
      throw error;
    }
  }

  /**
   * get all available languages that can be used by the ocr engine
   */
  public getAvailableLanguages(): Language[] {
    const winrtLangs = OcrEngine.availableRecognizerLanguages;
    const lang = WinrtParser.parseList<Language>(winrtLangs, item =>
      WinrtParser.parseLanguage(item as WinrtLanguage),
    );
    return lang;
  }
}
