import type { Dispatch, SetStateAction } from 'react'
import { useState } from 'react'
import { useContext, createContext } from 'react'
import type { IChildrenProps, IScheduler } from '../interfaces'

type SchedulerContextProps = [IScheduler, Dispatch<SetStateAction<IScheduler>>]

const SchedulerContext = createContext({} as SchedulerContextProps)

export function SchedulerProvider({ children }: IChildrenProps) {
  const [scheduler, setScheduler] = useState({} as IScheduler)

  return (
    <SchedulerContext.Provider value={[scheduler, setScheduler]}>
      {children}
    </SchedulerContext.Provider>
  )
}

export function useScheduler() {
  return useContext(SchedulerContext)
}
