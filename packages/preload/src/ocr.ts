import {ipcRenderer} from 'electron';

import Channels from '../../shared/lib/ipc-channels';

export async function extractText(
  data: ArrayBuffer,
  language: string,
  imgWidth: number,
  imgHeight: number,
) {
  return ipcRenderer.invoke(Channels.OCR_EXTRACT, data, language, imgWidth, imgHeight);
}

export function canProcessOCRForLanguage(langCode: string) {
  return ipcRenderer.invoke(Channels.OCR_CHECK_LANGUAGE, langCode);
}

export function getAvailableOCRLanguage() {
  return ipcRenderer.invoke(Channels.OCR_GET_AVAILABLE_LANGUAGE);
}
