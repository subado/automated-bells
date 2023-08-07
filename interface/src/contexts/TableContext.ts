import { useContext, createContext, useReducer } from 'react'
import type { ITable } from '../interfaces'
import { tableReducer } from '../reducers/tableReducer'

export const initialState: ITable = {
  title: '',
  items: [],
}

const wrappedUseReducer = () => useReducer(tableReducer, initialState)
type TableContextProps = ReturnType<typeof wrappedUseReducer>

export const TableContext = createContext({} as TableContextProps[0])
export const TableDispatchContext = createContext({} as TableContextProps[1])

export function useTable() {
  return useContext(TableContext)
}

export function useTableDispatch() {
  return useContext(TableDispatchContext)
}
