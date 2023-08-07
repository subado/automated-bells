import { useReducer, useState } from 'react'
import { tablesAPI } from '../../APIs/tablesAPI'
import { OptionsContext } from '../../contexts/OptionsContext'
import {
  initialState,
  TableContext,
  TableDispatchContext,
} from '../../contexts/TableContext'
import { tableReducer } from '../../reducers/tableReducer'
import { Form } from '../Form'
import { Table } from '../Table'
import { TableSelect } from './Select'

export function TimeTables() {
  const [timeTable, dispatchTimeTable] = useReducer(tableReducer, initialState)
  const [options, setOptions] = useState([] as string[])

  function handleTableSubmit(e: React.FormEvent) {
    e.preventDefault()
    tablesAPI.post({ title: timeTable.title, time: timeTable.items })
    if (!options.includes(timeTable.title)) {
      setOptions([...options, timeTable.title].sort())
    }
  }

  return (
    <OptionsContext.Provider value={[options, setOptions]}>
      <TableContext.Provider value={timeTable}>
        <TableDispatchContext.Provider value={dispatchTimeTable}>
          <TableSelect />
          <Form
            onSubmit={handleTableSubmit}
            onClear={() => {
              dispatchTimeTable({ type: 'clearItems' })
            }}
            submitButtonContent='Отправить'
            clearButtonContent='Очистить'
          >
            <Table
              inputType='time'
              inputName='time'
              titlePattern='[A-Za-z0-9]{1,23}'
            />
          </Form>
        </TableDispatchContext.Provider>
      </TableContext.Provider>
    </OptionsContext.Provider>
  )
}
