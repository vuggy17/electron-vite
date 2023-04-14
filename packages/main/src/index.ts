import '@abraham/reflection';
import './security-restrictions';

import {join} from 'node:path';
import {platform} from 'node:process';

import {app, BrowserWindow} from 'electron';
import {container} from 'tsyringe';

import logger from '/@/utils/logger';

import {CapturerModule, ContentProtectionModule, OcrModule} from './modules';
import AppModule from './modules/app';
import {SettingModule} from './modules/setting';
import * as ModuleManagers from './utils/module-manager';
import WindowManager from './utils/window-manager';
import {restoreOrCreateMainWindow} from './windows/main';
import {createOverlayWindow} from './windows/overlay';
/**
 * Shout down background process if all windows was closed
 */
app.on('window-all-closed', () => {
  if (platform !== 'darwin') {
    app.quit();
  }
});

/**
 * Disable Hardware Acceleration to save more system resources.
 */
app.disableHardwareAcceleration();

/**
 * @see https://www.electronjs.org/docs/latest/api/app#event-activate-macos Event: 'activate'.
 */
app.on('activate', restoreOrCreateMainWindow);

/**
 * Create the application window when the background process is ready.
 */
app
  .whenReady()
  .then(async () => {
    const mainWindow = new BrowserWindow({
      show: false, // Use the 'ready-to-show' event to show the instantiated BrowserWindow.
      webPreferences: {
        nodeIntegration: false,
        devTools: false,
        contextIsolation: true,
        sandbox: false, // Sandbox disabled because the demo of preload script depend on the Node.js api
        webviewTag: false, // The webview tag is not recommended. Consider alternatives like an iframe or Electron's BrowserView. @see https://www.electronjs.org/docs/latest/api/webview-tag#warning
        preload: join(app.getAppPath(), 'packages/preload/dist/index.cjs'),
      },
    });
    mainWindow.setSize(1500, 1024);
    /**
     * If the 'show' property of the BrowserWindow's constructor is omitted from the initialization options,
     * it then defaults to 'true'. This can cause flickering as the window loads the html content,
     * and it also has show problematic behaviour with the closing of the window.
     * Use `show: false` and listen to the  `ready-to-show` event to show the window.
     *
     * @see https://github.com/electron/electron/issues/25012 for the afford mentioned issue.
     */
    mainWindow.on('ready-to-show', () => {
      mainWindow?.show();

      if (import.meta.env.DEV) {
        mainWindow?.webContents.openDevTools();
      }
    });
    const translateWindow = await createOverlayWindow();

    // Init modules
    ModuleManagers.init(
      new AppModule(mainWindow, container.resolve(SettingModule)),
      new WindowManager(),
      new ContentProtectionModule(translateWindow),
      new OcrModule(),
      new CapturerModule(),
    );

    /**
     * URL for main window.
     * Vite dev server for development.
     * `file://../renderer/index.html` for production and test.
     */
    const pageUrl =
      import.meta.env.DEV && import.meta.env.VITE_DEV_SERVER_URL !== undefined
        ? import.meta.env.VITE_DEV_SERVER_URL
        : new URL('../renderer/dist/index.html', 'file://' + __dirname).toString();

    mainWindow.loadURL(pageUrl);
  })
  .catch(logger.error);

/**
 * Install Vue.js or any other extension in development mode only.
 * Note: You must install `electron-devtools-installer` manually
 */
// if (import.meta.env.DEV) {
//   app
//     .whenReady()
//     .then(() => import('electron-devtools-installer'))
//     .then(module => {
//       console.log(module);
//       module.default.default(module.REACT_DEVELOPER_TOOLS, {
//         loadExtensionOptions: {
//           allowFileAccess: true,
//         },
//       });
//     })
//     .catch(e => console.error('Failed install extension:', e));
// }

/**
 * Check for app updates, install it in background and notify user that new version was installed.
 * No reason run this in non-production build.
 * @see https://www.electron.build/auto-update.html#quick-setup-guide
 *
 * Note: It may throw "ENOENT: no such file app-update.yml"
 * if you compile production app without publishing it to distribution server.
 * Like `npm run compile` does. It's ok 😅
 */

if (import.meta.env.PROD) {
  app
    .whenReady()
    .then(() => import('electron-updater'))
    .then(module => {
      const autoUpdater =
        module.autoUpdater ||
        // @ts-expect-error Hotfix for https://github.com/electron-userland/electron-builder/issues/7338
        (module.default.autoUpdater as typeof module['autoUpdater']);
      return autoUpdater.checkForUpdatesAndNotify();
    })
    .catch(e => logger.error('Failed check and install updates:', e));
}
