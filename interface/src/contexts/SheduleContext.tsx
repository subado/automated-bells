import type { Dispatch, SetStateAction } from 'react'
import { useState } from 'react'
import { useContext, createContext } from 'react'
import type { IShedule, IChildrenProps } from '../interfaces'

type SheduleContextProps = [IShedule, Dispatch<SetStateAction<IShedule>>]

const SheduleContext = createContext({} as SheduleContextProps)

export function SheduleProvider({ children }: IChildrenProps) {
  const [shedule, setShedule] = useState(initialState)

  return (
    <SheduleContext.Provider value={[shedule, setShedule]}>
      {children}
    </SheduleContext.Provider>
  )
}

export function useShedule() {
  return useContext(SheduleContext)
}

const initialState: IShedule = {
  title: '',
}
