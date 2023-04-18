import {useCallback, useEffect, useState} from 'react';

import {DetectTextController} from './controller';
import type {Language} from './types';

export default function useLanguage() {
  const [sourceLangs, setSourceLangs] = useState<Language[]>([]);

  const refreshSourceLangs = useCallback(() => {
    const controller = new DetectTextController();
    controller.getSupportedLanguages().then(setSourceLangs);
  }, []);

  useEffect(() => {
    const controller = new DetectTextController();
    controller.getSupportedLanguages().then(setSourceLangs);
  }, []);

  return {
    sourceLangs,
    refreshSourceLangs,
  };
}
