import logger from '/@/utils/logger';
import {app} from 'electron';
import WindowedModule from './window';

export default class AppModule extends WindowedModule {
  /**
   *
   * @param window main window instance
   * @param _config
   */
  constructor(window: Electron.BrowserWindow, _config?: any) {
    super(window);
  }

  async load(): Promise<void> {
    this.ensureSingleInstance();
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
