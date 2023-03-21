import type React from 'react'

export interface ITable {
  title: string
  time: string[]
}

export interface ITableTitles {
  title: string[]
}

export interface ITime {
  hour: string
  minute: string
  second: string
}

export interface IProviderProps {
  children: React.ReactNode
}

export interface IShedule {
  title: string
}
