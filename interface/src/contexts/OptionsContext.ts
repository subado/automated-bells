import { useContext, createContext, useState } from 'react'

const initialState = Array<string>
const wrappedUseState = () => useState(initialState)
type OptionsContextProps = ReturnType<typeof wrappedUseState>

export const OptionsContext = createContext({} as OptionsContextProps)

export function useOptions() {
  return useContext(OptionsContext)
}
