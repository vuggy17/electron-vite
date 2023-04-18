import {Button, Card, Layout, Space, Typography} from 'antd';
interface Props {
  onPageSelected: (pagePath: string) => void;
}

/**
 * Render this page when user press new tab without select a specific page
 * @returns
 */
export default function DiscoverPage({onPageSelected}: Props) {
  return (
    <Layout>
      <Card bordered={false}>
        <div className="flex w-full justify-center flex-col text-center">
          <Typography.Title level={3}>Discover a page</Typography.Title>
          <Space
            align="center"
            direction="vertical"
          >
            <Button
              type="link"
              onClick={() => onPageSelected('setting')}
            >
              <Typography.Link>Open setting</Typography.Link>
            </Button>
            <Button
              type="link"
              onClick={() => onPageSelected('announcement')}
            >
              <Typography.Link>See developer announcement </Typography.Link>
            </Button>
            <Button
              type="link"
              onClick={() => onPageSelected('chat')}
            >
              <Typography.Link> Open chat page </Typography.Link>
            </Button>
          </Space>
        </div>
      </Card>
    </Layout>
  );
}
