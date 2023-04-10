import type { Dispatch } from 'react'
import { useContext, createContext } from 'react'
import type { ITable } from '../interfaces'
import type { TableAction } from '../reducers/tableReducer'

export const initialTable: ITable = {
  title: '',
  items: [],
}

export const TableContext = createContext(initialTable)
export const TableDispatchContext = createContext({} as Dispatch<TableAction>)

export function useTable() {
  return useContext(TableContext)
}

export function useTableDispatch() {
  return useContext(TableDispatchContext)
}
