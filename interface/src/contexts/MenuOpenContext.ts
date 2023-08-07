import { useState } from 'react'
import { useContext, createContext } from 'react'

const initialState = false
const wrappedUseState = () => useState(initialState)
type MenuOpenContextProps = ReturnType<typeof wrappedUseState>

export const MenuOpenContext = createContext({} as MenuOpenContextProps)

export function useMenuOpen() {
  return useContext(MenuOpenContext)
}
