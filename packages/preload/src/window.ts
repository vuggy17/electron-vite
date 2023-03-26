import {ipcRenderer} from 'electron';
import Channels from '../../../shared/lib/ipc-channels';
import {withErrorFilter} from './re-throw';

async function _createWindow(name: string) {
  return ipcRenderer.invoke(Channels.WINDOW_CREATE, name);
}

function _changeWindowContentProtection(enable: boolean) {
  return ipcRenderer.invoke(Channels.WINDOW_SET_CONTENT_PROTECTION, enable);
}

export const createWindow = withErrorFilter(_createWindow);
export const changeWindowContentProtection = withErrorFilter(_changeWindowContentProtection);

// TODO: replace withErrorFilter with this
// function promiseWrapper<T>(promise: Promise<T>) {
//   return promise
//     .then(data => {
//       return {data};
//     })
//     .catch(error => {
//       return {error};
//     });
// }
