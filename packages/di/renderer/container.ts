import {TextDetectionService} from '../../internal/src/core/services';
import {container} from 'tsyringe';
import {TEXT_DETECTION_SERVICE} from './tokens';

const rendererContainer = container.createChildContainer();

// this won't work
// rendererContainer.register(TEXT_DETECTION_SERVICE, {
//   useClass: TextDetectionService,
// });

// interface register only registered on the root container
container.register(TEXT_DETECTION_SERVICE, {
  useClass: TextDetectionService,
});

export {rendererContainer};
