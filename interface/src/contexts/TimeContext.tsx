import React, { useContext, useState } from 'react'
import { ITime } from '../interfaces/ITime'
import { ProviderProps } from '../interfaces/ProviderProps'

interface ITimeContextProps {
  state: ITime
  setState: React.Dispatch<React.SetStateAction<ITime>>
}

const TimeContext = React.createContext({} as ITimeContextProps)

export function useTime() {
  return useContext(TimeContext)
}

export function TimeProvider({ children }: ProviderProps) {
  const initialState: ITime = {
    time: '',
  }

  const [state, setState] = useState<ITime>(initialState)

  return (
    <TimeContext.Provider value={{ state: state, setState: setState }}>
      {children}
    </TimeContext.Provider>
  )
}
