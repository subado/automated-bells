import type { ChangeEvent, FormEvent } from 'react'
import { useEffect, useReducer, useState } from 'react'
import { ntpAPI } from '../APIs/ntpAPI'
import {
  initialState,
  TableContext,
  TableDispatchContext,
} from '../contexts/TableContext'
import { tableReducer } from '../reducers/tableReducer'
import { Form } from './Form'
import { Input } from './styled'
import { Table } from './Table/'

export function Ntp() {
  const [timeZone, setTimeZone] = useState({} as number)
  const [serversTable, dispatchServersTable] = useReducer(
    tableReducer,
    initialState
  )

  async function fetchNtpConfig() {
    const data = await ntpAPI.get()
    setTimeZone(data.timeZone)
    dispatchServersTable({
      type: 'set',
      table: { title: 'Сервера', items: data.servers },
    })
  }

  useEffect(() => {
    fetchNtpConfig()
  }, [])

  function handleSubmit(e: FormEvent) {
    e.preventDefault()
    ntpAPI.post({ timeZone: timeZone, servers: serversTable.items })
  }

  return (
    <Form
      onSubmit={handleSubmit}
      onClear={() => {
        setTimeZone({} as number)
        dispatchServersTable({ type: 'clearItems' })
      }}
      submitButtonContent='Отправить'
      clearButtonContent='Очистить'
    >
      <label htmlFor='timeZone'>
        timeZone
        <Input
          id='timeZone'
          type='number'
          min='-12'
          max='14'
          value={timeZone}
          onChange={(e: ChangeEvent<HTMLInputElement>) => {
            setTimeZone(e.target.valueAsNumber)
          }}
        />
      </label>
      <TableContext.Provider value={serversTable}>
        <TableDispatchContext.Provider value={dispatchServersTable}>
          <Table inputType='text' inputName='server' readOnlyTitle={true} />
        </TableDispatchContext.Provider>
      </TableContext.Provider>
    </Form>
  )
}
