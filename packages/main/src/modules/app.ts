import {app} from 'electron';

import logger from '/@/utils/logger';

import type {SettingModule} from './setting';
import WindowedModule from './window';

export default class AppModule extends WindowedModule {
  /**
   *
   * @param window main window instance
   * @param _config
   */
  constructor(window: Electron.BrowserWindow, private settingModule: SettingModule) {
    super(window);
  }

  async load(): Promise<void> {
    this.ensureSingleInstance();
    await this.settingModule.load();

    console.log(this.settingModule.setting.launchPosition);

    /**
     * If the 'show' property of the BrowserWindow's constructor is omitted from the initialization options,
     * it then defaults to 'true'. This can cause flickering as the window loads the html content,
     * and it also has show problematic behaviour with the closing of the window.
     * Use `show: false` and listen to the  `ready-to-show` event to show the window.
     *
     * @see https://github.com/electron/electron/issues/25012 for the afford mentioned issue.
     */
    this.window.on('ready-to-show', () => {
      // hot reload
      if (import.meta.env.DEV) {
        this.window.removeAllListeners();
      }

      const {x, y} = this.settingModule.setting.launchPosition;
      this.window.setPosition(x, y);
      this.window?.show();

      if (import.meta.env.DEV) {
        this.window?.webContents.openDevTools();
      }
    });

    this.window.on('moved', () => {
      const [xPos, yPos] = this.window.getPosition();
      this.settingModule.setPosition(xPos, yPos);
    });
  }

  ensureSingleInstance(): void {
    const isSingleInstance = app.requestSingleInstanceLock();

    app.on('second-instance', () => {
      // Someone tried to run a second instance, we should focus our window.
      if (this.window) {
        if (this.window.isMinimized()) this.window.restore();
        this.window.focus();
      }
    });

    if (!isSingleInstance) {
      logger.info('Another instance of App is already running, quitting...');
      app.quit();
    }
  }
}
