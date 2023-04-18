import 'antd/dist/reset.css';
import './App.css';

import {Card, Layout, Tabs} from 'antd';

import {DarkModeProvider} from './hooks/useDarkMode';
import useTabs from './hooks/useTabs';
import ThemeProvider from './Theme';

const App = () => {
  const {onChange, activeTabKey, availableTabs, onEdit} = useTabs();
  return (
    <DarkModeProvider>
      <ThemeProvider>
        <Layout
          style={{
            height: '100vh',
            width: '100vw',
          }}
        >
          <Layout.Content>
            <Card
              bordered={false}
              className="h-full first:[&>.ant-card-body]:p-0"
            >
              <Tabs
                className="h-full"
                type="editable-card"
                onChange={onChange}
                activeKey={activeTabKey}
                onEdit={onEdit}
                items={availableTabs}
              />
            </Card>
          </Layout.Content>
        </Layout>
      </ThemeProvider>
    </DarkModeProvider>
  );
};
export default App;
