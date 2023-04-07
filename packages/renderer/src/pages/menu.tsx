import {Button, Layout, Space, Typography} from 'antd';

import LanguageSelector from '../components/lang-selector';
import PageHeader from '../components/page-header';
import {DetectTextController} from '../features/detect-text/controller';

export default function MenuPage() {
  const getText = async () => {
    try {
      const result = await new DetectTextController().detectFromImage('fake image', 'en');
      console.log(result);
    } catch (error) {
      console.error('Error caught: ', error);
    }
  };

  return (
    <Layout>
      <PageHeader />
      <div className="px-[50px]">
        <Typography.Title
          level={1}
          className="mt-4"
        >
          React App
        </Typography.Title>
        <Space
          direction="vertical"
          className="w-full"
          size={'large'}
        >
          <LanguageSelector />

          <Space direction="vertical">
            <Button>create new window</Button>
            <Button onClick={getText}>extract text from image</Button>
          </Space>
        </Space>
      </div>
    </Layout>
  );
}
