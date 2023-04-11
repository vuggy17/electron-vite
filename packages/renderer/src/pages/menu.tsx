import {Button, Layout, Space, Typography} from 'antd';
import {lazy, Suspense} from 'react';

import {SuspensesedLangSelector} from '../components/lang-selector';
import PageHeader from '../components/page-header';
import {DetectTextController} from '../features/detect-text/controller';

const LanguageSelector = lazy(() => import('../components/lang-selector'));

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
    <Layout className="h-full flex-1">
      <PageHeader />
      <div className="px-[50px] pt-16 pb-36">
        {/* <Typography.Title
          level={1}
          className="mt-4 invisible"
        >
          React App
        </Typography.Title> */}
        <Space
          direction="vertical"
          className="w-full"
          size={'large'}
        >
          <Suspense fallback={<SuspensesedLangSelector />}>
            <LanguageSelector />
          </Suspense>

          {/* <Space direction="vertical">
            <Button>create new window</Button>
            <Button onClick={getText}>extract text from image</Button>
          </Space> */}
        </Space>
      </div>
    </Layout>
  );
}
