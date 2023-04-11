import {generate} from '@ant-design/colors';
import {DropboxCircleFilled, SendOutlined} from '@ant-design/icons';
import {Button, Col, ConfigProvider, Row, Select, Skeleton, Space, Typography, Upload} from 'antd';

const {Dragger} = Upload;
import useLanguage from '../features/detect-text';

export default function LanguageSelector() {
  const colors = generate('#3283ff', {
    theme: 'default',
  });
  console.log(colors);
  const {sourceLangs, refreshSourceLangs} = useLanguage();

  const onSourceLangChange = (value: string) => {
    console.log(`selected ${value}`);
  };

  if (sourceLangs.length === 0) return null;

  return (
    <div className="relative">
      <div className="absolute z-10 left-1/2 -ml-[28px] mt-7 p-1 bg-[#111116] rounded-full">
        <ConfigProvider
          theme={{
            components: {
              Button: {
                controlHeightLG: 56,
              },
            },
          }}
        >
          <Button
            type="primary"
            shape="circle"
            size="large"
            icon={<SendOutlined />}
          ></Button>
        </ConfigProvider>
      </div>
      <Row gutter={16}>
        <Col span={12}>
          <div className="rounded-[32px] bg-[#1b1b1f] pl-6 pr-14 rounded-b-none pt-7 pb-11">
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
                  <ConfigProvider
                    theme={{
                      components: {
                        Select: {
                          borderRadiusLG: 24,
                          controlHeight: 50, // option height
                          controlHeightLG: 56, // input height
                          paddingContentHorizontal: 48,
                        },
                        Input: {
                          controlHeight: 40,
                          controlHeightLG: 64,
                        },
                      },
                    }}
                  >
                    <Select
                      size="large"
                      // open={true}
                      className="w-full"
                      // popupClassName="rounded-xl"
                      defaultValue={sourceLangs[0].code}
                      // options={[
                      //   ...sourceLangs.map(lang => ({label: lang.name, value: lang.code})),
                      //   ...sourceLangs.map(lang => ({label: lang.name, value: lang.code})),
                      // ]}
                      onChange={onSourceLangChange}
                    >
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code + 21}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code + '2'}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                    </Select>
                  </ConfigProvider>
                </Col>
              </Row>
              <Typography.Paragraph className="text-lg">
                Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem
                Ipsum has been the industry's standard dummy text ever since the 1500s
              </Typography.Paragraph>
            </Space>

            <div className="h-20 invisible"></div>
            <div className="bg-slate-600 h-16"></div>
          </div>
          <div className="rounded-b-[32px]  bg-[#1b1b1f] p-10 rounded-t-none py-8 mt-[2px]">
            <Dragger>
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
          </div>
        </Col>
        <Col span={12}>
          <div className="rounded-[32px] bg-[#1b1b1f] pr-6 pl-14 rounded-b-none pt-7 pb-11">
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
                    To :
                  </Typography.Text>
                </Col>
                <Col flex="auto">
                  <ConfigProvider
                    theme={{
                      components: {
                        Select: {
                          borderRadiusLG: 24,
                          controlHeight: 50, // option height
                          controlHeightLG: 56, // input height
                          paddingContentHorizontal: 48,
                        },
                        Input: {
                          controlHeight: 40,
                          controlHeightLG: 64,
                        },
                      },
                    }}
                  >
                    <Select
                      size="large"
                      // open={true}
                      className="w-full"
                      // popupClassName="rounded-xl"
                      defaultValue={sourceLangs[0].code}
                      // options={[
                      //   ...sourceLangs.map(lang => ({label: lang.name, value: lang.code})),
                      //   ...sourceLangs.map(lang => ({label: lang.name, value: lang.code})),
                      // ]}
                      onChange={onSourceLangChange}
                    >
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code + 21}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                      {sourceLangs.map(lang => (
                        <Select.Option
                          className="!rounded-lg"
                          key={lang.code + '2'}
                        >
                          <Typography.Text>{lang.name}</Typography.Text>
                        </Select.Option>
                      ))}
                    </Select>
                  </ConfigProvider>
                </Col>
              </Row>
              <Typography.Paragraph className="text-lg">
                Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem
                Ipsum has been the industry's standard dummy text ever since the 1500s
              </Typography.Paragraph>
            </Space>

            <div className="h-20 invisible"></div>
            <div className="bg-slate-600 h-16"></div>
          </div>
          <div className="rounded-b-[32px]  bg-[#1b1b1f] p-10 rounded-t-none py-8 mt-[2px]">
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
          </div>
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
