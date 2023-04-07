import {ipcMain} from 'electron';

import Channels from '#shared/lib/ipc-channels';

import WindowedModule from './window';

export default class ContentProtectionModule extends WindowedModule {
  async load() {
    ipcMain.handle(Channels.WINDOW_SET_CONTENT_PROTECTION, async (event, enable) => {
      this.window.setContentProtection(enable);
    });
  }
}
