/**
 * @module internal
 */
// this package is the same with reflect-metadata but smaller,
// we can use it since tsyringle doesn't need Reflect within esbuild,
//see:https://github.com/microsoft/tsyringe/issues/180
import '@abraham/reflection';

export * from './core/entities';
export * from './core/services';
export * from './ports';
