import {createWindow, extractText} from '#preload';

const App = () => {
  return (
    <div>
      <h1>React App</h1>

      <p>hello dasdsa redsadsaact</p>

      <button
        type="button"
        onClick={() =>
          createWindow('resultView12')
            .then(result => console.log('ok', result))
            .catch(error => console.log('error', error))
        }
      >
        create new window
      </button>
      <button
        type="button"
        onClick={() =>
          extractText('image string', 'eng')
            .then(result => console.log('ok', result))
            .catch(error => console.log('error', error))
        }
      >
        extract text from image
      </button>
    </div>
  );
};
export default App;
