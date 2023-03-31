import 'antd/dist/reset.css';
import './App.css';
import {useState, useRef} from 'react';
import ThemeProvider from './Theme';
import MenuPage from './pages/menu';
import {Layout, Tabs} from 'antd';
import Routes from './routes';

const defaultTabs = [{label: 'Menu', children: <MenuPage />, key: '1', closable: false}];
type TargetKey = React.MouseEvent | React.KeyboardEvent | string;

const App = () => {
  // const [isDarkMode, setIsDarkMode] = useState(false);
  const [activeTabKey, setActiveTabKey] = useState('1');
  const [availableTabs, setAvailableTabs] = useState(defaultTabs);
  const newTabIndex = useRef(1);
  const availableTabsRef = useRef(availableTabs);

  const updatePageName = (name: string, pageKey: string) => {
    const newTabs = [...availableTabsRef.current];
    newTabs.forEach(item => {
      if (item.key === pageKey) {
        item.label = name;
      }
    });
    setAvailableTabs([...newTabs]);
  };

  const add = () => {
    const newActiveKey = `newTab${newTabIndex.current++}`;
    const newPanes = [...availableTabs];
    newPanes.push({
      label: 'New tab',
      children: (
        <Routes
          onPageSelected={selectedPageName => {
            updatePageName(selectedPageName, newActiveKey);
            // console.log('selectedPageName', availableTabs.length);
          }}
        />
      ),
      key: newActiveKey,
      closable: true,
    });
    availableTabsRef.current = newPanes; // to make sure the new tab is newest at the time updatePageName is called
    setAvailableTabs(newPanes);
    setActiveTabKey(newActiveKey);
  };

  const remove = (targetKey: TargetKey) => {
    let newActiveKey = activeTabKey;
    let lastIndex = -1;
    availableTabs.forEach((item, i) => {
      if (item.key === targetKey) {
        lastIndex = i - 1;
      }
    });
    const newPanes = availableTabs.filter(item => item.key !== targetKey);
    if (newPanes.length && newActiveKey === targetKey) {
      if (lastIndex >= 0) {
        newActiveKey = newPanes[lastIndex].key;
      } else {
        newActiveKey = newPanes[0].key;
      }
    }
    setAvailableTabs(newPanes);
    setActiveTabKey(newActiveKey);
  };

  const onEdit = (
    targetKey: React.MouseEvent | React.KeyboardEvent | string,
    action: 'add' | 'remove',
  ) => {
    if (action === 'add') {
      add();
    } else {
      remove(targetKey);
    }
  };

  const onChange = (key: string) => {
    setActiveTabKey(key);
  };
  return (
    <ThemeProvider isDark={false}>
      <Layout
        style={{
          height: '100vh',
        }}
      >
        <Tabs
          type="editable-card"
          onChange={onChange}
          activeKey={activeTabKey}
          onEdit={onEdit}
          items={availableTabs}
        />
      </Layout>
    </ThemeProvider>
  );
};
export default App;
