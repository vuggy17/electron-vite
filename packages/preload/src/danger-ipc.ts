import {ipcRenderer} from 'electron';

export function invoke(channel: string, ...args: unknown[]): Promise<unknown> {
  return ipcRenderer.invoke(channel, args);
}

export function send(channel: string, ...args: unknown[]): void {
  ipcRenderer.send(channel, args);
}
