import type {DesktopCapturerSource} from 'electron';
import {desktopCapturer, ipcMain} from 'electron';

import Channels from '#shared/lib/ipc-channels';

import Module from './base-module';

export default class Capturer extends Module {
  async load() {
    ipcMain.handle(
      Channels.CAPTURER_GET_WINDOW_SOURCES,
      this.getWindowChromeMediaSourceIds.bind(this),
    );
    ipcMain.handle(
      Channels.CAPTURER_GET_SCREEN_SOURCES,
      this.getScreenChromeMediaSourceIds.bind(this),
    );
  }

  getScreenChromeMediaSourceIds(_e: Electron.IpcMainInvokeEvent): Promise<DesktopCapturerSource[]> {
    return desktopCapturer.getSources({types: ['screen']});
  }

  getWindowChromeMediaSourceIds(_e: Electron.IpcMainInvokeEvent): Promise<DesktopCapturerSource[]> {
    return desktopCapturer.getSources({types: ['window']});
  }
}
