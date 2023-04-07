import {existsSync, readdirSync, rm, statSync} from 'fs';
import path from 'path';
import {fileURLToPath} from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const __rootdir = path.join(__dirname, '..');

// cleanup build artifacts, like bin and build folders of winrt packages
// recursively traverse through the packages/externals/* folders then delete bin and build folders
function deleteFolders(dirPath) {
  if (existsSync(dirPath)) {
    readdirSync(dirPath).forEach(file => {
      const curPath = path.join(dirPath, file);
      if (statSync(curPath).isDirectory()) {
        if (file === 'bin' || file === 'build') {
          rm(curPath, {recursive: true}, error => console.warn('Error deleting folder', error));
        } else {
          deleteFolders(curPath);
        }
      }
    });
  }
}

const externalsPath = path.join(__rootdir, 'packages', 'externals');

deleteFolders(externalsPath);
