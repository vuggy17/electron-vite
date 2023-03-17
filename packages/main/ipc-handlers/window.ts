import {WINDOW_CONTENT_PROTECTION, WINDOW_CREATE} from './../../preload/chanels';
import {ipcMain} from 'electron';
import {createWindow} from '/@/overlayWindow';

ipcMain.handle(WINDOW_CONTENT_PROTECTION, (event, enable) => {
  console.log('setting window content protection to: ', enable);
});

ipcMain.handle(WINDOW_CREATE, async (event, name) => {
  console.log('creating window: ', name);
  switch (name) {
    case 'overlay':
      await createWindow();
      break;
    case 'resultView':
      console.log('resultView not implemented yet');
      break;
    default:
      console.error('unknown window name: ', name);
  }
});
