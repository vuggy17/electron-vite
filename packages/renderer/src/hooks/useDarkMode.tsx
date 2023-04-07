import {createContext, useContext} from 'react';
import hookExternal from 'beautiful-react-hooks/useDarkMode';
export const DarkModeContext = createContext({
  isDarkMode: false,
  toggle: () => {
    console.log('I will be override later');
  },
});

export function DarkModeProvider({children}: React.PropsWithChildren) {
  const {toggle, isDarkMode} = hookExternal();

  return (
    <DarkModeContext.Provider value={{isDarkMode, toggle}}> {children} </DarkModeContext.Provider>
  );
}

export function useDarkMode() {
  const {isDarkMode, toggle} = useContext(DarkModeContext);
  return {isDarkMode, toggle};
}
