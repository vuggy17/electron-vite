import '@abraham/reflection';
import {app} from 'electron';
import {platform} from 'node:process';
import logger from '../../../shared/lib/logger';
import {CapturerModule, ContentProtectionModule, OcrModule} from './modules';
import AppModule from './modules/app';
import './security-restrictions';
import * as ModuleManagers from './utils/module-manager';
import WindowManager from './utils/window-manager';
import {restoreOrCreateMainWindow} from './windows/mainWindow';
import {createOverlayWindow} from '/@/windows/overlayWindow';
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
    const mainWindow = await restoreOrCreateMainWindow();
    const translateWindow = await createOverlayWindow();

    // Init modules
    ModuleManagers.init(
      new AppModule(mainWindow),
      new WindowManager(),
      // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
      new ContentProtectionModule(translateWindow),
      new OcrModule(),
      new CapturerModule(),
    );
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
