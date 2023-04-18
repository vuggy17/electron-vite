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
        algorithm: false ? darkAlgorithm : defaultAlgorithm,
        token: {
          colorPrimary: '#128C7E',
          colorText: '#010101',
        },
        components: {
          Select: {
            borderRadiusLG: 24,
            controlHeight: 40, // option height
            controlHeightLG: 48, // input height
            // controlItemBgActive: '#D1E4E8',
            controlPaddingHorizontal: 20,
          },
          Input: {
            controlHeightLG: 48,
          },
        },
      }}
    >
      {children}
    </ConfigProvider>
  );
}
