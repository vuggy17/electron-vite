import {Layout, Space, Typography} from 'antd';
import {useState} from 'react';

import AnnouncementPage from './pages/announcement';
import ChatPage from './pages/chat';
import DiscoverPage from './pages/discover';
import OcrPage from './pages/ocr';
import SettingPage from './pages/setting';

const routers = [
  {
    path: 'menu',
    element: <OcrPage />,
  },
  {
    path: 'setting',
    element: <SettingPage />,
  },
  {
    path: 'announcement',
    element: <AnnouncementPage />,
  },
  {
    path: 'chat',
    element: <ChatPage />,
  },
];

const DISCOVER_PATH = '/';

interface Props {
  onPageSelected: (name: string) => void;
}

export default function Routes({onPageSelected}: Props) {
  const [selectedPath, setSelectedPath] = useState(DISCOVER_PATH);

  const getDisplayElement = (path: string) => {
    const page = routers.find(route => route.path === path);
    if (page) {
      setTimeout(() => {
        // this is a hack to make sure the page is rendered before we call onPageSelected
        onPageSelected(path.charAt(0).toUpperCase() + path.slice(1)); // Capitalize first letter, e.g. setting -> Setting
      }, 100);
      return page.element;
    } else {
      console.warn(`Page ${path} not found`);
      return (
        <Layout>
          <Space
            direction="vertical"
            align="center"
          >
            <Typography.Text>Page not found</Typography.Text>
            <Typography.Link onClick={() => setSelectedPath(DISCOVER_PATH)}>
              Take me back
            </Typography.Link>
          </Space>
        </Layout>
      );
    }
  };

  if (selectedPath === DISCOVER_PATH)
    return <DiscoverPage onPageSelected={path => setSelectedPath(path)} />;
  return getDisplayElement(selectedPath);
}
