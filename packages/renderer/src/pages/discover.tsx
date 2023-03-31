import {Button, Layout, Space} from 'antd';
import React from 'react';

interface Props {
  onPageSelected: (pagePath: string) => void;
}

/**
 * Render this page when user press new tab without select a specific page
 * @returns
 */
export default function DiscoverPage({onPageSelected}: Props) {
  return (
    <Layout>
      <Space>
        <Space align="center"> Discover a page</Space>
      </Space>
      <Space
        align="center"
        direction="vertical"
      >
        <Button
          type="link"
          onClick={() => onPageSelected('setting')}
        >
          Open setting
        </Button>
        <Button
          type="link"
          onClick={() => onPageSelected('announcement')}
        >
          See developer announcement
        </Button>
      </Space>
    </Layout>
  );
}
