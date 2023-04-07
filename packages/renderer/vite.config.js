/* eslint-env node */

import {chrome} from '../../.electron-vendors.cache.json';
import react from '@vitejs/plugin-react';
import {renderer} from 'unplugin-auto-expose';
import {join} from 'node:path';
import {injectAppVersion} from '../../version/inject-app-version-plugin.mjs';

const ioc = require.resolve('tsyringe/dist/esm2015/index.js');
const PACKAGE_ROOT = __dirname;
const PROJECT_ROOT = join(PACKAGE_ROOT, '../..');

/**
 * @type {import('vite').UserConfig}
 * @see https://vitejs.dev/config/
 */
const config = {
  mode: process.env.MODE,
  root: PACKAGE_ROOT,
  envDir: PROJECT_ROOT,
  resolve: {
    alias: {
      '/@/': join(PACKAGE_ROOT, 'src') + '/',
      '#shared': join(PACKAGE_ROOT, '../shared') + '/',
      '#internal': join(PACKAGE_ROOT, '../internal') + '/',
      tsyringe: ioc, // this make pre-bundle slower, but make autoInject work!, https://github.com/microsoft/tsyringe/issues/142
    },
  },
  base: '',
  server: {
    fs: {
      strict: true,
    },
  },
  build: {
    sourcemap: true,
    target: `chrome${chrome}`,
    outDir: 'dist',
    assetsDir: '.',
    rollupOptions: {
      input: join(PACKAGE_ROOT, 'index.html'),
    },
    emptyOutDir: true,
    reportCompressedSize: false,
  },
  test: {
    environment: 'happy-dom',
  },
  plugins: [
    react(),
    renderer.vite({
      preloadEntry: join(PACKAGE_ROOT, '../preload/src/index.ts'),
    }),
    injectAppVersion(),
  ],
  // to make vite pre-bundle faster https://github.com/vitejs/vite/issues/8850, this behavior could be implemented by vite 4.2.1
  optimizeDeps: {
    include: ['@ant-design/icons', 'react', 'antd'],
  },
};

export default config;
