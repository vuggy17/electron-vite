import {dialog, ipcMain} from 'electron';
import {Module} from '../modules';
import {createOverlayWindow} from '/@/windows/overlayWindow';
import Channels from '../../../../shared/lib/ipc-channels';

export default class WindowManager extends Module {
  windows: Record<symbol, Electron.BrowserWindow>;
  nameReferences: Record<string, symbol[]>;
  IDMap: Record<number, symbol>;
  focus: string[];
  allowedWindowName = ['overlay', 'capturer'];

  async load() {
    ipcMain.handle(Channels.WINDOW_CREATE, async (event, name) => {
      console.log('creating window: ', name);
      switch (name) {
        case 'overlay': {
          const overlayWindow = await createOverlayWindow();

          this.add(overlayWindow, name);
          // throw new CustomError('not implemented yet');
          break;
        }
        case 'resultView':
          console.log(this.allowedWindowName.join(','));
          throw new Error('not implemented yet');

          break;
        default:
          console.error('Unknown window name: ', name);
          throw new Error('Unknown window name: ' + name);
      }
    });
  }

  constructor() {
    super();
    this.focus = [];
    this.windows = {};
    this.nameReferences = {};
    this.IDMap = {};
  }

  /**
   * add a new browser window to the manager
   * @param window
   * @param name {string} add a name to the window, so you can get it via {@linkcode getAll}
   * */
  add(window: Electron.BrowserWindow, name = '') {
    if (!this.allowedWindowName.includes(name)) throw new Error('Window name not allowed: ' + name);

    return this.addWindow(window, name);
  }

  private addWindow(window: Electron.BrowserWindow, name = '') {
    const newID = Symbol();
    this.windows[newID] = window;
    this.IDMap[window.id] = newID;
    window.on('closed', () => {
      delete this.windows[newID];
    });

    window.on('enter-full-screen', () => {
      window.webContents.send('window:changefullscreen', true);
    });
    window.on('leave-full-screen', () => {
      window.webContents.send('window:changefullscreen', false);
    });

    window.webContents.setWindowOpenHandler(_details => {
      dialog.showMessageBoxSync(window, {
        message: 'External link was blocked due to company restriction',
      });
      return {action: 'deny'};
    });

    if (name) {
      this.nameReferences[name] ??= new Array<symbol>();
      this.nameReferences[name].push(newID);
    }
    return newID;
  }

  /**
   * get a browser window by unique ID
   * @param windowID
   */
  get(windowID: symbol) {
    return this.windows[windowID] || null;
  }

  /**
   * get a browser window by {@linkcode Electron.BrowserWindow.id}
   * @param internalID {number}
   */
  getByInternalID(internalID: number) {
    if (this.IDMap[internalID]) {
      return this.windows[this.IDMap[internalID]] || null;
    }
    return null;
  }

  /**
   * get all browser windows by its name
   * @param name
   */
  getAll(name: string): Electron.BrowserWindow[] {
    const toReturn: Electron.BrowserWindow[] = [];
    (this.nameReferences[name] || []).forEach(ID => {
      if (this.get(ID)) {
        toReturn.push(this.get(ID));
      }
    });
    return toReturn;
  }
}
