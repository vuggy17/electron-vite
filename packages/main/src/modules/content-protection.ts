import {ipcMain} from 'electron';
import WindowedModule from './window';
import Channels from '../../../../shared/lib/ipc-channels';
import {asyncWrapper} from '../utils/error-wrapper';

export default class ContentProtectionModule extends WindowedModule {
  async load() {
    ipcMain.handle(
      Channels.WINDOW_SET_CONTENT_PROTECTION,
      asyncWrapper(async (event, enable) => {
        this.window.setContentProtection(enable);
      }),
    );
  }
}
