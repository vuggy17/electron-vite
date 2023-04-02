import {useCallback, useEffect, useState} from 'react';
// import { rendererContainer } from '../../../../di';

import {DetectTextController} from './controller';
import type {Language} from './types';


export default function useLanguage() {
  const [sourceLangs, setSourceLangs] = useState<Language[]>([]);

  const refreshSourceLangs = useCallback(() => {
    const instance = new DetectTextController();
    // const instance = rendererContainer.resolve(DetectTextController);
    instance.getSupportedLanguages().then(setSourceLangs);
  }, []);

  useEffect(() => {
    const instance = new DetectTextController();
    // const instance = rendererContainer.resolve(DetectTextController);
    instance.getSupportedLanguages().then(setSourceLangs);
    // const instance = rendererContainer.resolve(DetectTextController);
    // instance.getSupportedLanguages().then(refreshSourceLangs);
    //  new DetectTextController().getAvailableLanguage();
  }, []);

  return {
    sourceLangs,
    refreshSourceLangs,
  };
}
