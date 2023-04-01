import {theme} from 'antd';
import {ConfigProvider} from 'antd';

interface Props extends React.PropsWithChildren {
  isDark: boolean;
}
export default function ThemeProvider({isDark, children}: Props) {
  const {defaultAlgorithm, darkAlgorithm} = theme;

  return (
    <ConfigProvider
      theme={{
        algorithm: isDark ? darkAlgorithm : defaultAlgorithm,
        // token: {
        //   colorPrimary: '#00b96b',
        // },
        // components: {
        //   Layout: {
        //     colorBgHeader: '#00b96b',
        //     colorTextBase: '#fff',
        //   },
        // },
      }}
    >
      {children}
    </ConfigProvider>
  );
}
