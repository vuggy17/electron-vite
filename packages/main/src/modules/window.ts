import Module from './base-module';

/**
 *  **This module should never be instantiated**
 *
 *  All registered modules which need access to {@linkcode Electron.BrowserWindow} api should extend this class
 */
export default class WindowedModule extends Module {
  protected window: Electron.BrowserWindow;

  constructor(window: Electron.BrowserWindow) {
    super();
    this.window = window;
  }

  getWindow() {
    return this.window;
  }
}
