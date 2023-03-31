import {createWindow, extractText} from '#preload';
import {Button, Layout, Typography} from 'antd';
import 'antd/dist/reset.css';
import './App.css';
import {FireTwoTone, StarTwoTone} from '@ant-design/icons';
import {useState} from 'react';
import ThemeProvider from './Theme';

const App = () => {
  const [isDarkMode, setIsDarkMode] = useState(false);

  return (
    <ThemeProvider isDark={isDarkMode}>
      <Layout style={{
        height: '100vh',
      }}>
        <div>
          <Typography.Title level={1}>React App</Typography.Title>

          <Typography.Text>hello dasdsa redsadsaact</Typography.Text>
          <Button
            icon={isDarkMode ? <StarTwoTone /> : <FireTwoTone />}
            onClick={() => setIsDarkMode(!isDarkMode)}
          />
          <Button
            onClick={() =>
              createWindow('resultView')
                .then(result => console.log('ok', result))
                .catch(error => {
                  console.log('err', error);
                })
            }
          >
            create new window
          </Button>
          <Button
            onClick={() =>
              extractText('image string', 'eng').then(result => console.log('ok', result))
            }
          >
            extract text from image
          </Button>
        </div>
      </Layout>
    </ThemeProvider>
  );
};
export default App;
