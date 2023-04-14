import ElectronStore from 'electron-store';
import {singleton} from 'tsyringe';

import type {UserSettings} from '../types/setting-schema';
import Module from './base-module';

@singleton()
export class SettingModule extends Module {
  private store: ElectronStore<UserSettings>;

  private _setting: UserSettings;

  constructor() {
    super();
    this.store = new ElectronStore<UserSettings>({
      defaults: {
        launchPosition: {x: 0, y: 0},
      },
    });

    this._setting = {} as UserSettings;
  }

  async load(): Promise<void> {
    // load settings
    this._setting.launchPosition = this.store.get('launchPosition');
  }

  setPosition(x: number, y: number): void {
    this._setting.launchPosition.x = x;
    this._setting.launchPosition.y = y;

    this.store.set('launchPosition', this._setting.launchPosition);
  }

  get setting(): UserSettings {
    return this._setting;
  }
}
