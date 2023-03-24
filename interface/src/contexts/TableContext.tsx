import type { Dispatch } from 'react'
import { useContext, useReducer, createContext } from 'react'
import type { ITable, IChildrenProps } from '../interfaces'
import type { TableAction } from '../reducers/tableReducer'
import { tableReducer } from '../reducers/tableReducer'

const TableContext = createContext({} as ITable)
const TableDispatchContext = createContext({} as Dispatch<TableAction>)

export function TableProvider({ children }: IChildrenProps) {
  const [table, dispatch] = useReducer(tableReducer, initialState)

  return (
    <TableContext.Provider value={table}>
      <TableDispatchContext.Provider value={dispatch}>
        {children}
      </TableDispatchContext.Provider>
    </TableContext.Provider>
  )
}

export function useTable() {
  return useContext(TableContext)
}

export function useTableDispatch() {
  return useContext(TableDispatchContext)
}

const initialState: ITable = {
  title: '',
  time: [],
}
