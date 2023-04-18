import {Space, Typography} from 'antd';
import React from 'react';

import {availableFeatures} from '#shared/feature-flag';

import ChatPage from './chat';
import OcrPage from './ocr';

export default function EntryPage() {
  const {chat, ocr} = availableFeatures;

  if (ocr) {
    return <OcrPage />;
  }
  if (chat) {
    return <ChatPage />;
  }
  return (
    <div className="flex h-full w-full justify-center ">
      <Space direction="vertical">
        <Typography.Title>Sorry :( </Typography.Title>
        <Typography.Text>Our developer was forgot to enable this feature 🤦‍♂️</Typography.Text>
      </Space>
    </div>
  );
}
