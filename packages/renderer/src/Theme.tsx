import {theme} from 'antd';
import {ConfigProvider} from 'antd';

import {useDarkMode} from './hooks/useDarkMode';

type Props = React.PropsWithChildren;
export default function ThemeProvider({children}: Props) {
  const {defaultAlgorithm, darkAlgorithm} = theme;
  const {isDarkMode} = useDarkMode();

  return (
    <ConfigProvider
      theme={{
        algorithm: isDarkMode ? darkAlgorithm : defaultAlgorithm,
        token: {
          colorPrimary: '#335cff',
          colorBgContainer: '#1b1b1f',
          colorText: '#f1f1f1',
          colorBgLayout: '#111116',
          fontSize: 16,
        },
      }}
    >
      {children}
    </ConfigProvider>
  );
}
