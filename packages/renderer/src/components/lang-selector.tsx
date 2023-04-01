import React from 'react';
import type { Language } from '../features/detect-text';
import useLanguage from '../features/detect-text';
import {Button, Card, Col, Row, Select, Typography} from 'antd';
import {ReloadOutlined} from '@ant-design/icons';

export default function LanguageSelector() {
  const {sourceLangs, refreshSourceLangs} = useLanguage();

  const onSourceLangChange = (value: Language) => {
    console.log(`selected ${value}`);
  };

  return (
    <Row gutter={32}>
      <Col flex={1}>
        <Card>
          <Typography.Title level={3}>Detect language from</Typography.Title>
          <Select
          className='w-full'
            defaultActiveFirstOption={true}
            options={sourceLangs.map(lang => ({label: lang.name, value: lang.code}))}
            onChange={onSourceLangChange}
          />

          <Button
            shape="circle"
            icon={<ReloadOutlined />}
            onClick={refreshSourceLangs}
          />
        </Card>
      </Col>
      <Col flex={1}>
        <Card>
          <Typography.Title level={3}>Detect language from</Typography.Title>
          <Select
            defaultActiveFirstOption
            options={sourceLangs.map(lang => ({label: lang.name, value: lang.code}))}
            onChange={onSourceLangChange}
          />
        </Card>
      </Col>
    </Row>
  );
}
