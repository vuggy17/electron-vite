// TODO: remove this when we actually implement the ocr module
/* eslint-disable @typescript-eslint/no-unused-vars */
import type {IpcMainInvokeEvent} from 'electron';
import {ipcMain} from 'electron';
import {toIBuffer} from 'nodert-streams';
import {Language as WinrtLanguage} from 'windows.globalization';
import {BitmapAlphaMode, BitmapPixelFormat, SoftwareBitmap} from 'windows.graphics.imaging';
import type {OcrLine, OcrResult} from 'windows.media.ocr';
import {OcrEngine} from 'windows.media.ocr';

import logger from '/@/utils/logger';
import Channels from '#shared/lib/ipc-channels';

import type {Language} from '../../../internal/src/core/entities';
import {WinrtParser} from '../utils/winrt-adapter';
import Module from './base-module';

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
  private async extractText(_e: IpcMainInvokeEvent, data: ArrayBuffer, language: string) {
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

  private recognizePromise(winrtBitmap: SoftwareBitmap, lang: string) {
    const engine = OcrEngine.tryCreateFromLanguage(new WinrtLanguage(lang));
  }

  private async extractTextFromImage(image: ArrayBuffer, lang: string): Promise<string> {
    const language = new WinrtLanguage('en-US');
    console.log(OcrEngine.isLanguageSupported(language));
    const bitmap = await this.getWinRTBitmap(
      await this.toWinrtBuffer(this.toBuffer(image)),
      400,
      500,
    );

    return new Promise((resolve, reject) => {
      const engine = OcrEngine.tryCreateFromLanguage(new WinrtLanguage(lang));

      engine.recognizeAsync(bitmap, (err, nativeResult: OcrResult) => {
        const nativeLines = nativeResult.lines as any; // c# vector: Windows::Foundation::Collections:IVectorView
        const texts: string[] = [];

        for (let index = 0; index < nativeLines.size; index++) {
          const element: OcrLine = nativeLines[index];
          texts.push(element.text.toString());
        }
        resolve(texts.join(';'));
      });
    });

    const internalResult = WinrtParser.parseList(result);
    return 'Google Translate is an online translation tool developed by Google. It provides website interfaces, mobile apps for Android and iOS operating systems, and application programming interfaces that help developers build web browser extensions and software applications.';
  }

  /**
   *
   * @param image base64 string of the image
   */
  public async tryExtract(image: ArrayBuffer, lang: string): Promise<string> {
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

  /**
   *
   * @param iBufferInstance winrt IBuffer instance https://learn.microsoft.com/en-us/uwp/api/windows.storage.streams.ibuffer?view=winrt-22621
   * @returns winrt SoftwareBitmap
   */
  async getWinRTBitmap(
    iBufferInstance: object,
    width: number,
    height: number,
  ): Promise<SoftwareBitmap> {
    return SoftwareBitmap.createCopyFromBuffer(
      iBufferInstance,
      BitmapPixelFormat.rgba8,
      width,
      height,
      BitmapAlphaMode.premultiplied,
    );
  }

  // async toNodeJsBuffer(source: Uint8ClampedArray) {
  //   return Buffer.from(source.buffer, source.byteOffset, source.byteLength);
  // }
  // convert js array buffer to nodejs buffer
  toBuffer(arrayBuffer: ArrayBuffer) {
    const buffer = Buffer.alloc(arrayBuffer.byteLength);
    const view = new Uint8Array(arrayBuffer);
    for (let i = 0; i < buffer.length; ++i) {
      buffer[i] = view[i];
    }
    return buffer;
  }

  async toWinrtBuffer(source: Buffer) {
    return toIBuffer(source);
  }
}
