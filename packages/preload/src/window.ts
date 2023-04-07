import {ipcRenderer} from 'electron';
import Channels from '../../shared/lib/ipc-channels';

export async function createWindow(name: string) {
  return ipcRenderer.invoke(Channels.WINDOW_CREATE, name);
}

export function changeWindowContentProtection(enable: boolean) {
  return ipcRenderer.invoke(Channels.WINDOW_SET_CONTENT_PROTECTION, enable);
}
