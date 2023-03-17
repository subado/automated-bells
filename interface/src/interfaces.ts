import type React from 'react'

export interface ITableState {
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

export interface IDropdownMenuState {
  isEnable: boolean
  list: string[]
  selected: string
}

export interface IProviderProps {
  children: React.ReactNode
}
