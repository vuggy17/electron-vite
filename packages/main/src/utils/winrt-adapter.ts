import type {Language as WinrtLanguage} from 'windows.globalization';

import {Language} from '../../../internal/src/core/entities';

function parseLanguage(input: WinrtLanguage): Language {
  return new Language(input.languageTag.toString(), input.displayName.toString());
}

// eslint-disable-next-line @typescript-eslint/no-explicit-any
function parseCollection<T>(collection: any, parseFn: (i: any) => T): T[] {
  const result: T[] = [];
  for (let i = 0; i < collection.size; i++) {
    const item = collection[i];
    result.push(parseFn(item));
  }
  return result;
}

export const WinrtParser = {
  parseCollection,
  parseLanguage,
};
