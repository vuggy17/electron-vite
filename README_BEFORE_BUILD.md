# Build node-addon module

### DON’T USE PNPM, IT WILL LEAD TO BUILD FAILURE

Happy path 🤪

1. Install package by <your package manager>
2. Make it to be build with electron-builder
3. Rebuild it with electron-rebuild to match with node version of electron for you will get node_module_version not match error
4. Happy hacking!

### Q&A

1. **Resouce busy or locked:** You’ll get this error when your local package has build or release folder, just make sure there is no folders contained in it.

1. **<your package manager> install fail:** You’ll get this error when you use incorrect package manager to install your package, [see this link](https://github.com/pnpm/pnpm/issues/2135) for an example of that, I have no idea why it happens.

1. **Ultimate guide to solve other problems:**

Make sure your project installation with <your package manager> not have any failure before install any node addon package.

Install addon package locally: `npm install --save ../path/to/mymodule` [detail about how to install package locally](https://stackoverflow.com/questions/15806241/how-to-specify-local-modules-as-npm-package-dependencies)

If any error appears, try bellow steps:

- Clean npm cache: npm cache clean -f
- Clean electron-gyp cache by remove this folder C:\Users\<your name>\.electron-gyp\cache
- Clean node-gyp cache: C:\Users\<your name>\AppData\Local\node-gyp\Cache

If these guide not help, good luck with google 🙏
