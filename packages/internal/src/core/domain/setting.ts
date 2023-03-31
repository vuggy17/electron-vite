export interface AppSetting {
  theme: 'dark' | 'light';
  primaryColor: 'blue' | 'green' | 'yellow';
  language: 'en';
}

// functionality setting, like auto save, auto backup, etc.
// eslint-disable-next-line @typescript-eslint/no-empty-interface
export interface UserSetting {}
