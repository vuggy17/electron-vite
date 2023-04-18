import {Layout, Space, Typography} from 'antd';
import {useMemo, useState} from 'react';
import DashBoard from './pages/dashboard';
import LoginPage from './pages/login';

type RoutePaths = 'login' | 'main';

const DEFAULT_PATH = '/';

interface Props {
  onPageSelected: (name: string) => void;
}

export interface RouteChild {
  navigateTo: (path: RoutePaths) => void;
}

export default function ChatRoutes() {
  const [selectedPath, setSelectedPath] = useState(DEFAULT_PATH);

  const triggerNavigate = (path: RoutePaths) => setSelectedPath(path);

  const routers: {path: RoutePaths; element: JSX.Element}[] = useMemo(
    () => [
      {
        path: 'login',
        element: <LoginPage navigateTo={triggerNavigate} />,
      },
      {
        path: 'main',
        element: <DashBoard navigateTo={triggerNavigate} />,
      },
    ],
    [],
  );

  const displayElement = routers.filter(route => route.path === selectedPath)[0]?.element;

  if (selectedPath === DEFAULT_PATH) return <LoginPage navigateTo={triggerNavigate} />;

  return displayElement;
}
