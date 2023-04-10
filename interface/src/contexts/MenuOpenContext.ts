import type { Dispatch, SetStateAction } from 'react'
import { useContext, createContext } from 'react'

type MenuOpenContextProps = [boolean, Dispatch<SetStateAction<boolean>>]

export const MenuOpenContext = createContext({} as MenuOpenContextProps)

export function useMenuOpen() {
  return useContext(MenuOpenContext)
}
