import {useState} from 'react';
import {createWindow, extractText} from '#preload';
import {Button, Layout, Typography} from 'antd';
import {FireTwoTone, StarTwoTone} from '@ant-design/icons';

export default function MenuPage() {
  const [isDarkMode, setIsDarkMode] = useState(false);

  return (
    <Layout>
      <div>
        <Typography.Title level={1}>React App</Typography.Title>
        <h1 className="text-3xl font-bold underline">Tailwind works</h1>

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
  );
}
