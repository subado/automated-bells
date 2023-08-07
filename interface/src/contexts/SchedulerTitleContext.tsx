import type { PropsWithChildren } from 'react'
import { useContext, createContext, useState } from 'react'

const initialState = ''
const wrappedUseState = () => useState(initialState)
type SchedulerTitleContextProps = ReturnType<typeof wrappedUseState>

const SchedulerTitleContext = createContext({} as SchedulerTitleContextProps)

export function SchedulerTitleProvider({ children }: PropsWithChildren) {
  const [schedulerTitle, setSchedulerTitle] = wrappedUseState()

  return (
    <SchedulerTitleContext.Provider value={[schedulerTitle, setSchedulerTitle]}>
      {children}
    </SchedulerTitleContext.Provider>
  )
}

export function useSchedulerTitle() {
  return useContext(SchedulerTitleContext)
}
