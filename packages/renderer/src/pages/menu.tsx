import {Layout, message, Space} from 'antd';
import {lazy, Suspense} from 'react';

import {SuspensesedLangSelector} from '../components/lang-selector';
import PageHeader from '../components/page-header';
import {DetectTextController} from '../features/detect-text/controller';

const LanguageSelector = lazy(() => import('../components/lang-selector'));

export default function MenuPage() {
  const [messageApi, contextHolder] = message.useMessage();

  const getText = async (image: File) => {
    try {
      const result = await new DetectTextController().detectFromImage(image, 'en-US');
      messageApi.success('Text copied to clipboard 🫡');

      // TODO: check if clipboard is supported in production
      navigator.clipboard.writeText(result);
    } catch (error) {
      messageApi.error('Fail to detect text!');
      console.error('Error caught: ', error);
    }
  };

  return (
    <Layout className="h-full flex-1">
      {contextHolder}
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
