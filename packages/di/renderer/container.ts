import {TextDetectionService} from '../../internal/src/core/services/text-detection.service';
import {container} from 'tsyringe';
import {TEXT_DETECTION_SERVICE} from './tokens';

const rendererContainer = container.createChildContainer();

rendererContainer.register(TEXT_DETECTION_SERVICE, {
  useClass: TextDetectionService,
});

console.log('ccc');

export {rendererContainer};
