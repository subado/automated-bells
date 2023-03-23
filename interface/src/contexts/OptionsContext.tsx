import type { Dispatch, SetStateAction } from 'react'
import { useState } from 'react'
import { useContext, createContext } from 'react'
import type { IProviderProps } from '../interfaces'

type OptionsContextProps = [string[], Dispatch<SetStateAction<string[]>>]

const OptionsContext = createContext({} as OptionsContextProps)

export function OptionsProvider({ children }: IProviderProps) {
  const [options, setOptions] = useState<string[]>([])

  return (
    <OptionsContext.Provider value={[options, setOptions]}>
      {children}
    </OptionsContext.Provider>
  )
}

export function useOptions() {
  return useContext(OptionsContext)
}