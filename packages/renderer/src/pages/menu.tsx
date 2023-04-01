import {createWindow, extractText} from '#preload';
import {Button, Layout, Typography} from 'antd';
import LanguageSelector from '../components/lang-selector';

export default function MenuPage() {
  return (
    <Layout>
      <div>
        <Typography.Title level={1}>React App</Typography.Title>
        <LanguageSelector />

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
