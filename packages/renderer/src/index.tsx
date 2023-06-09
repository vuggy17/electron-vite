import '@abraham/reflection';
import '#shared/lib/di/renderer'; // register all dependencies

import React from 'react';
import ReactDOM from 'react-dom/client';
import {ErrorBoundary} from 'react-error-boundary';

import App from './App';

function Fallback({error, resetErrorBoundary}: {error: Error; resetErrorBoundary: () => void}) {
  return (
    <div role="alert">
      <p>Something went wrong:</p>
      <pre style={{color: 'red'}}>{error.message}</pre>
      <button onClick={() => resetErrorBoundary()}>Continue to app</button>
    </div>
  );
}

const root = ReactDOM.createRoot(document.getElementById('root') as HTMLElement);
root.render(
  <React.StrictMode>
    <ErrorBoundary
      FallbackComponent={Fallback}
      onError={(error: Error, info: {componentStack: string}) => console.error(error.message, info)}
    >
      <App />
    </ErrorBoundary>
  </React.StrictMode>,
);
