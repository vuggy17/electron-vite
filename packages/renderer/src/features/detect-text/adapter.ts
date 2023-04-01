import {Language as InternalLanguage} from '../../../../internal/src/core/entities';
import type {Language} from './types';

function createLanguageFromCode(code: string): InternalLanguage {
  if (code == 'en') {
    return new InternalLanguage('en', 'English');
  }
  throw new Error('Invalid language code, no language with code: ' + code);
}

function createLanguageFromInternal(internalLang: InternalLanguage): Language {
  const {code, name} = internalLang;

  return {code, name} as Language;
}

const LanguageAdapter = {
  createLanguageFromCode,
  createLanguageFromInternal,
};

export default LanguageAdapter;
