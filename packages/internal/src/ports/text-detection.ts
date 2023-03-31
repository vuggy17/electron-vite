export interface TextDetectionPort {
  getTextFromImage(image: string, language: string): Promise<string>;
  /**
   * get the id of window for application to stream the image to
   */
  getTargetId(): Promise<string>;

  /**
   * move capturer window to the target
   * @param targetId the id of window for application to stream the image from
   */
  attachCapturer(targetId: string): Promise<boolean>;
}