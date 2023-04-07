import {ipcMain} from 'electron';
import WindowedModule from './window';
import Channels from '#shared/lib/ipc-channels';

export default class ContentProtectionModule extends WindowedModule {
  async load() {
    ipcMain.handle(Channels.WINDOW_SET_CONTENT_PROTECTION, async (event, enable) => {
      this.window.setContentProtection(enable);
    });
  }
}
