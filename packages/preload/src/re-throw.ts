import type {CustomError} from '../../../shared/types/app';
/**
 * check if response is a custom error(ie. api error, internally thrown error)
 */
export function isCustomError(response: any | CustomError) {
  if (!response) {
    return false;
  }
  return Boolean(response.isCustomError);
}

type Awaited<T> = T extends PromiseLike<infer U> ? Awaited<U> : T;
type AsyncFn = (...args: any[]) => Promise<any>;

export function withErrorFilter<T extends AsyncFn>(
  call: T,
): (...args: Parameters<T>) => Promise<Awaited<ReturnType<T>>> {
  return async (...args: Parameters<T>) => {
    try {
      const response = await call(...args);
      if (isCustomError(response)) throw response;
      else return response;
    } catch (exception) {
      // if ((exception as CustomError).isCustom === true) {
      //   // do some stuff here
      //   console.log('exception');
      // }
      return new Promise((_, reject) => reject(exception));
      console.log('exception-thrown');
    }
  };
}
