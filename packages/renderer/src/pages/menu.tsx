import {Button, Layout, Space, Typography} from 'antd';
import {lazy, Suspense} from 'react';

import {SuspensesedLangSelector} from '../components/lang-selector';
import PageHeader from '../components/page-header';
import {DetectTextController} from '../features/detect-text/controller';

const LanguageSelector = lazy(() => import('../components/lang-selector'));

export default function MenuPage() {
  const getText = async (image: File) => {
    try {
      const result = await new DetectTextController().detectFromImage(image, 'en');
      console.log(result);
    } catch (error) {
      console.error('Error caught: ', error);
    }
  };

  return (
    <Layout className="h-full flex-1">
      <PageHeader />
      <div className="px-[50px] pt-16 pb-36">
        <Space
          direction="vertical"
          className="w-full"
          size={'large'}
        >
          <Suspense fallback={<SuspensesedLangSelector />}>
            <LanguageSelector
              onFileDrop={file => {
                console.log(file);
                getText(file);
              }}
            />
          </Suspense>
        </Space>
      </div>
    </Layout>
  );
}
