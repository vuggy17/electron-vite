/**
 * Example of Module, other modules should extent this class
 */

import * as os from 'os';

import logger from '../../../../shared/lib/logger';

/**
 * @description
 * - Base module to be extended by other modules
 *
 * - Ensure singleton pattern on modules
 *
 * - Implements a simple platform check, error handling and logging
 */
class Module {
  protected loaded: boolean;
  protected platforms: NodeJS.Platform[];

  constructor() {
    this.loaded = false;
    this.platforms = ['win32']; // 'win32', 'linux', 'darwin'
  }

  /**
   * **Do not override this method**
   *
   * Load the module if the current platform is supported
   */
  async init(): Promise<void> {
    if (this.loaded) throw new TypeError(`Module ${this.constructor.name} is already loaded`);

    if (this.platforms.includes(os.platform())) {
      await this.load().catch(err => {
        throw err;
      });
      this.loaded = true;
    } else {
      logger.info(
        `Skipping load of ${this.constructor.name} (supported platform: ${this.platforms.join(
          ', ',
        )})`,
      );
    }
  }

  /**
   * @NOTE: override this method
   */
  async load(): Promise<void> {
    throw new TypeError(`Module ${this.constructor.name} should have a load() method`);
    // Do whatever you want here :)
  }
}

export default Module;
