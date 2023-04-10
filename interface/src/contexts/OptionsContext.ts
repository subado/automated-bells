import type { Dispatch, SetStateAction } from 'react'
import { useContext, createContext } from 'react'

type OptionsContextProps = [string[], Dispatch<SetStateAction<string[]>>]

export const OptionsContext = createContext({} as OptionsContextProps)

export function useOptions() {
  return useContext(OptionsContext)
}
