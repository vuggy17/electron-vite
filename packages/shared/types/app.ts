/**
 * Ocr related types
 */
export enum CaptureMode {
  Windowed,
  Fullscreen,
  Regional,
}
/**
 * Custom error
 */
export type CustomError = {
  error:
    | {
        message: string;
        stack: string;
        cause: unknown;
      }
    | Error;
  isCustom: boolean;
};
