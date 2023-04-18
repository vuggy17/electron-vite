import {Image, Space, Typography} from 'antd';
import chatEmpty from '../assets/chat_empty.svg';

export default function Empty() {
  return (
    <div className="text-center">
      <Space
        direction="vertical"
        size={28}
      >
        <Image
          src={chatEmpty}
          alt="fallback"
          preview={false}
        />

        <Typography.Text
          strong
          className="text-[36px] text-[#333E5B]"
        >
          Keep your phone <br /> connected
        </Typography.Text>
        <Typography.Text
          type="secondary"
          className="text-[18px] -mt-6 "
        >
          Whatsapp connects to your phone to sync messages. <br />
          To reduce data usage. connect your phone to Wi-Fi.
        </Typography.Text>
      </Space>
    </div>
  );
}
