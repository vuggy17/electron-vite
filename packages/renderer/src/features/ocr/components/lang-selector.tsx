import {DropboxCircleFilled, SendOutlined} from '@ant-design/icons';
import {
  Button,
  Card,
  Col,
  ConfigProvider,
  Row,
  Select,
  Skeleton,
  Space,
  Typography,
  Upload,
} from 'antd';

const {Dragger} = Upload;
import useLanguage from '../features/detect-text';

interface Props {
  onFileDrop: (file: File) => void;
}

export default function LanguageSelector({onFileDrop}: Props) {
  const {sourceLangs, refreshSourceLangs} = useLanguage();

  const onSourceLangChange = (value: string) => {
    console.log(`selected ${value}`);
  };

  if (sourceLangs.length === 0) return null;

  return (
    <div className="relative">
      <div className="absolute z-10 left-1/2 -ml-[28px] mt-7 p-1 bg-white rounded-full">
        <ConfigProvider
          theme={{
            components: {
              Button: {
                controlHeightLG: 56,
                colorBgContainer: '#FFF',
              },
            },
          }}
        >
          <Button
            type="primary"
            shape="circle"
            size="large"
            icon={<SendOutlined />}
          />
        </ConfigProvider>
      </div>
      <Row
        gutter={16}
        justify="center"
        align={'top'}
      >
        <Col span={9}>
          <Card className="rounded-[24px] bg-[#F5FAFC] pl-6 pr-14 rounded-b-none pt-7 pb-11">
            <Space
              direction="vertical"
              size={32}
            >
              <Row
                align={'middle'}
                gutter={16}
              >
                <Col flex="none">
                  <Typography.Text
                    strong
                    className="tracking-tight text-[#646467]"
                  >
                    From :
                  </Typography.Text>
                </Col>
                <Col flex="auto">
                  <Select
                    size="large"
                    className="w-full"
                    popupClassName="rounded-[12px] px-0 pt-[12px] pb-[16px]"
                    defaultValue={sourceLangs[0].code}
                    onChange={onSourceLangChange}
                  >
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code + 21}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code + '2'}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                  </Select>
                </Col>
              </Row>
              <Typography.Paragraph className="text-lg">
                Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem
                Ipsum has been the industry's standard dummy text ever since the 1500s
              </Typography.Paragraph>
            </Space>

            <div className="h-20 invisible"></div>
            <div className="bg-slate-600 h-16"></div>
          </Card>
          <Card className="rounded-b-[24px] bg-[#F5FAFC] p-10 rounded-t-none py-8 mt-[2px]">
            <Dragger
              accept="image/*"
              multiple={false}
              beforeUpload={() => false}
              itemRender={() => null}
              onChange={info => {
                const file = info.file;
                if (!file) {
                  console.warn('No file');
                  return;
                }
                onFileDrop(file as unknown as File);
              }}
            >
              <Space
                direction="vertical"
                align="center"
                className="w-full"
              >
                <Typography.Title level={4}>Drop your documents here!</Typography.Title>
                {/* open file button */}
                <div className="rounded-full bg-[#111116] p-[6px] pl-4 flex items-center  gap-4 w-fit">
                  <Typography.Text className="text-base font-medium tracking-wide">
                    Choose files
                  </Typography.Text>
                  <div className="bg-[#1f1f24] p-2 rounded-full w-14">
                    <DropboxCircleFilled />
                  </div>
                </div>
              </Space>
            </Dragger>
          </Card>
        </Col>
        <Col span={9}>
          <Card className="rounded-[24px] bg-[#F5FAFC] pl-6 pr-14 rounded-b-none pt-7 pb-11">
            <Space
              direction="vertical"
              size={32}
            >
              <Row
                align={'middle'}
                gutter={16}
              >
                <Col flex="none">
                  <Typography.Text
                    strong
                    className="tracking-tight text-[#646467]"
                  >
                    From :
                  </Typography.Text>
                </Col>
                <Col flex="auto">
                  <Select
                    size="large"
                    className="w-full"
                    popupClassName="rounded-[12px] px-0 pt-[12px] pb-[16px]"
                    defaultValue={sourceLangs[0].code}
                    onChange={onSourceLangChange}
                  >
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code + 21}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                    {sourceLangs.map(lang => (
                      <Select.Option key={lang.code + '2'}>
                        <Typography.Text>{lang.name}</Typography.Text>
                      </Select.Option>
                    ))}
                  </Select>
                </Col>
              </Row>
              <Typography.Paragraph className="text-lg">
                Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem
                Ipsum has been the industry's standard dummy text ever since the 1500s
              </Typography.Paragraph>
            </Space>

            <div className="h-20 invisible"></div>
            <div className="bg-slate-600 h-16"></div>
          </Card>
          <Card className="rounded-b-[24px] bg-[#F5FAFC] p-10 rounded-t-none py-8 mt-[2px]">
            <Dragger
              accept="image/*"
              multiple={false}
              beforeUpload={() => false}
              itemRender={() => null}
              onChange={info => {
                const file = info.file;
                if (!file) {
                  console.warn('No file');
                  return;
                }
                onFileDrop(file as unknown as File);
              }}
            >
              <Space
                direction="vertical"
                align="center"
                className="w-full"
              >
                <Typography.Title level={4}>Drop your documents here!</Typography.Title>
                {/* open file button */}
                <div className="rounded-full bg-[#111116] p-[6px] pl-4 flex items-center  gap-4 w-fit">
                  <Typography.Text className="text-base font-medium tracking-wide">
                    Choose files
                  </Typography.Text>
                  <div className="bg-[#1f1f24] p-2 rounded-full w-14">
                    <DropboxCircleFilled />
                  </div>
                </div>
              </Space>
            </Dragger>
          </Card>
        </Col>
      </Row>
    </div>
  );
}

export function SuspensesedLangSelector() {
  return (
    <Skeleton
      loading={true}
      active
    >
      <div className="h-[80px]"></div>
    </Skeleton>
  );
}
