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
      }}
    >
      {children}
    </ConfigProvider>
  );
}
