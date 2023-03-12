import React, { useContext, useReducer } from 'react'
import { ITable } from '../interfaces/ITable'
import { ProviderProps } from '../interfaces/ProviderProps'
import { tableReducer, TableAction } from '../hooks/tableReducer'

interface ITableContextProps {
  state: ITable
  dispatch: React.Dispatch<TableAction>
}

const TableContext = React.createContext({} as ITableContextProps)

export function useTable() {
  return useContext(TableContext)
}

export function TableProvider({ children }: ProviderProps) {
  const initialState: ITable = {
    title: '',
    time: [],
  }

  const [state, dispatch] = useReducer(tableReducer, initialState)

  return (
    <TableContext.Provider value={{ state: state, dispatch: dispatch }}>
      {children}
    </TableContext.Provider>
  )
}
