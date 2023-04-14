// TODO: remove this when we actually implement the ocr module
/* eslint-disable @typescript-eslint/no-unused-vars */
import type {IpcMainInvokeEvent} from 'electron';
import {ipcMain} from 'electron';
import {toIBuffer} from 'nodert.streams';
import {Language as WinrtLanguage} from 'windows.globalization';
import {BitmapAlphaMode, BitmapPixelFormat, SoftwareBitmap} from 'windows.graphics.imaging';
import type {OcrLine, OcrResult} from 'windows.media.ocr';
import {OcrEngine} from 'windows.media.ocr';

import logger from '/@/utils/logger';
import Channels from '#shared/lib/ipc-channels';

import type {Language} from '../../../internal/src/core/entities';
import {ValidationError} from '../utils/error';
import {WinrtParser} from '../utils/winrt-adapter';
import Module from './base-module';

export default class OcrModule extends Module {
  async load() {
    ipcMain.handle(Channels.OCR_EXTRACT, this.extractText.bind(this));
    ipcMain.handle(Channels.OCR_CHECK_LANGUAGE, this.isLanguageSupportOcr.bind(this));
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
  private async extractText(
    _e: IpcMainInvokeEvent,
    data: ArrayBuffer,
    language: string,
    imgWidth: number,
    imgHeight: number,
  ) {
    try {
      await this.isLanguageSupportOcr(_e, language);

      const result = await this.tryExtract(data, language, imgWidth, imgHeight);
      this.previousText = result;
      return result;
    } catch (error) {
      logger.error(OcrModule.constructor.name, error);
    }
  }

  /**
   * check if the given language is supported by the window ocr engine
   * @param _e
   * @param language
   */
  private async isLanguageSupportOcr(_e: IpcMainInvokeEvent, language: string) {
    const winrtLang = new WinrtLanguage(language);

    const hasSupport = OcrEngine.isLanguageSupported(winrtLang);
    if (!hasSupport) {
      throw new ValidationError('Language not supported');
    }
    return hasSupport;
  }
  /**
   *
   * @param image base64 string of the image
   */
  public async tryExtract(
    image: ArrayBuffer,
    lang: string,
    imgWidth: number,
    imgHeight: number,
  ): Promise<string> {
    const language = new WinrtLanguage(lang);
    const bitmap = await this.getSoftwareBitmap(
      await this.toWinrtBuffer(this.toBuffer(image)),
      imgWidth,
      imgHeight,
    );

    return new Promise((resolve, reject) => {
      const engine = OcrEngine.tryCreateFromLanguage(language);

      engine.recognizeAsync(bitmap, (err, nativeResult: OcrResult) => {
        if (err) {
          return reject(err);
        }
        const nativeLines = nativeResult.lines as any; // c# vector: Windows::Foundation::Collections:IVectorView
        // const texts: string[] = [];

        // for (let index = 0; index < nativeLines.size; index++) {
        //   const element: OcrLine = nativeLines[index];
        //   texts.push(element.text.toString());
        // }

        const texts = WinrtParser.parseCollection<string>(nativeLines, line =>
          line.text.toString(),
        );
        resolve(texts.join(';'));
      });
    });

    return 'Google Translate is an online translation tool developed by Google. It provides website interfaces, mobile apps for Android and iOS operating systems, and application programming interfaces that help developers build web browser extensions and software applications.';
  }

  /**
   * get all available languages that can be used by the ocr engine
   */
  public getAvailableLanguages(): Language[] {
    const winrtLangs = OcrEngine.availableRecognizerLanguages;
    const lang = WinrtParser.parseCollection<Language>(winrtLangs, item =>
      WinrtParser.parseLanguage(item as WinrtLanguage),
    );
    return lang;
  }

  /**
   *
   * @param iBufferInstance winrt IBuffer instance https://learn.microsoft.com/en-us/uwp/api/windows.storage.streams.ibuffer?view=winrt-22621
   * @returns winrt SoftwareBitmap
   */
  async getSoftwareBitmap(
    iBufferInstance: object,
    width: number,
    height: number,
  ): Promise<SoftwareBitmap> {
    console.log('width', width);
    console.log('height', height);

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
    // const buffer = Buffer.alloc(arrayBuffer.byteLength);
    // const view = new Uint8Array(arrayBuffer);
    // for (let i = 0; i < buffer.length; ++i) {
    //   buffer[i] = view[i];
    // }
    // return buffer;

    return Buffer.from(arrayBuffer);
  }

  async toWinrtBuffer(source: Buffer) {
    return toIBuffer(source);
  }
}
