import {Button} from 'antd';
import React from 'react';
import Empty from '../components/empty';
import {RouteChild} from '../routes';

export default function DashBoard({navigateTo}: RouteChild) {
  return (
    <div>
      <div>dash DashBoard</div>

      <Empty />
      <Button onClick={() => navigateTo('login')}>go to login</Button>
    </div>
  );
}
