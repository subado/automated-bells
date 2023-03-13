import React, { useContext, useReducer } from 'react'
import { tableListReducer, TableListAction } from '../hooks/tableListReducer'
import { ITableList } from '../interfaces/ITable'
import { ProviderProps } from '../interfaces/ProviderProps'

interface ITableListContextProps {
  state: ITableList
  dispatch: React.Dispatch<TableListAction>
}

const TableListContext = React.createContext({} as ITableListContextProps)

export function useTableList() {
  return useContext(TableListContext)
}

export function TableListProvider({ children }: ProviderProps) {
  const initialState: ITableList = {
    title: [],
    selected: '',
  }

  const [state, dispatch] = useReducer(tableListReducer, initialState)

  return (
    <TableListContext.Provider value={{ state: state, dispatch: dispatch }}>
      {children}
    </TableListContext.Provider>
  )
}
