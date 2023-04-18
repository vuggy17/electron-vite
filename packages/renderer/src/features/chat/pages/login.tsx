import {Checkbox, ConfigProvider, Space, Typography} from 'antd';
import React from 'react';
import {RouteChild} from '../routes';

export default function LoginPage({navigateTo}: RouteChild) {
  return (
    <div className="h-full flex w-full justify-center py-20">
      <ConfigProvider
        theme={{
          components: {
            Checkbox: {
              fontSize: 18,
              controlInteractiveSize: 24,
            },
          },
        }}
      >
        <div className="px-[60px] flex flex-col">
          <div
            className="w-[266px] aspect-square bg-gray-600 mx-auto cursor-pointer"
            onClick={() => navigateTo('main')}
          ></div>
          <div className="mt-[40px]">
            <Typography.Title level={4}>Login in to WhatsApp by QR Code</Typography.Title>
            <div className="h-[104px] text-center bg-gray-300"></div>
          </div>

          <div className="text-center mt-[20px]">
            <Checkbox checked>Keep me signed in</Checkbox>
          </div>
        </div>
      </ConfigProvider>
    </div>
  );
}
