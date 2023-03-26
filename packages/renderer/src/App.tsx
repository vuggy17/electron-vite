
import {createWindow} from '#preload';

const App = () => {
  return (
    <div>
      <h1>React App</h1>

      <p>hello dasdsa redsadsaact</p>

      <button
        type="button"
        onClick={() => createWindow('resultView12').then((result) => console.log('ok', result))}
      >
        create new window
      </button>
    </div>
  );
};
export default App;
