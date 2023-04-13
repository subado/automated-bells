import type { Dispatch, SetStateAction } from 'react'
import { useState } from 'react'
import { useContext, createContext } from 'react'
import type { IChildrenProps } from '../interfaces'

type SchedulerTitleContextProps = [string, Dispatch<SetStateAction<string>>]

const SchedulerTitleContext = createContext({} as SchedulerTitleContextProps)

export function SchedulerTitleProvider({ children }: IChildrenProps) {
  const [schedulerTitle, setSchedulerTitle] = useState('')

  return (
    <SchedulerTitleContext.Provider value={[schedulerTitle, setSchedulerTitle]}>
      {children}
    </SchedulerTitleContext.Provider>
  )
}

export function useSchedulerTitle() {
  return useContext(SchedulerTitleContext)
}
