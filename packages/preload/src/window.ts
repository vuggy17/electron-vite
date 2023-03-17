import {WINDOW_CONTENT_PROTECTION, WINDOW_CREATE} from '../chanels';
import {ipcRenderer} from 'electron';

export function createWindow(name: 'overlay' | 'resultView') {
  return ipcRenderer.invoke(WINDOW_CREATE, name);
}

export function changeWindowContentProtection(enable: boolean) {
  return ipcRenderer.invoke(WINDOW_CONTENT_PROTECTION, enable);
}
