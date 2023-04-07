import type {Language as WinrtLanguage} from 'windows.globalization';
import {Language} from '../../../internal/src/core/entities';

function parseLanguage(input: WinrtLanguage): Language {
  return new Language(input.languageTag.toString(), input.displayName.toString());
}

function parseList<T>(list: any, parseFn: (i: unknown) => T): T[] {
  const result: T[] = [];
  for (let i = 0; i < list.size; i++) {
    const item = list[i];
    result.push(parseFn(item));
  }
  return result;
}

export const WinrtParser = {
  parseList,
  parseLanguage,
};
