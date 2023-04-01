/**
 * will resolve a promise after a given time with a given value
 */
export function delay<T>(ms: number, value: T): () => Promise<T> {
  return () => new Promise(resolve => setTimeout(() => resolve(value), ms));
}

/**
 * get random number in the range [min, max)
 * @param min {number} the minimum value in ms
 * @param max {number} the maximum value in ms
 * @return a random number in the range [min, max)
 */
export function getRandomInt(min = 0, max = 300): number {
  return Math.floor(Math.random() * (max - min)) + min;
}
