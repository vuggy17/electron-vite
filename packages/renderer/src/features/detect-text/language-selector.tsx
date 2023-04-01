import {useCallback, useEffect, useState} from 'react';
import {DetectTextController} from './controller';
import type {Language} from './types';

export default function useLanguage() {
  const [sourceLangs, setSourceLangs] = useState<Language[]>([]);

  const refreshSourceLangs = useCallback(() => {
    DetectTextController.getSupportedLanguages().then(setSourceLangs);
  }, []);

  useEffect(() => {
    DetectTextController.getSupportedLanguages().then(refreshSourceLangs);
    DetectTextController.getAvailableLanguage();
  }, []);

  return {
    sourceLangs,
    refreshSourceLangs,
  };
}
