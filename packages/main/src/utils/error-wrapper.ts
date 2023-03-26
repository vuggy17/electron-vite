/* eslint-disable prefer-rest-params */
// eslint-disable-next-line @typescript-eslint/ban-types

import type {CustomError} from '../../../../shared/types/app';

/**
 * **This function run only in main process**
 *
 * Wrap ipc handler with ease
 *
 * Because electron ipc handler cannot handle custom error
 * @param f ipc handler function
 *
 * @see refer to this {@link https://m-t-a.medium.com/electron-getting-custom-error-messages-from-ipc-main-617916e85151|this article} for more details
 *
 */
// The return value of this function is an object that contains the result of the
// async function that was wrapped, as well as a boolean value that indicates whether
// the promise was rejected or not.
// This is used to differentiate between a rejected promise and a promise that
// was resolved with a value that has an error property.
//

export function asyncWrapper<T>(f: (e: Electron.IpcMainInvokeEvent, ...args: any) => Promise<T>) {
  return async function () {
    try {
      return await f.apply(this, arguments);
    } catch (error) {
      if (error instanceof Error) {
        //TODO: build an custom error
        const internalError = {
          message: error.message,
          stack: error.stack,
          cause: error.cause,
        };

        return {
          error: internalError,
          isCustomError: true, // true if promise is rejected in main process
        } as unknown as CustomError;
      } else {
        return {
          error,
          isCustomError: false,
        };
      }
    }
  };
}
