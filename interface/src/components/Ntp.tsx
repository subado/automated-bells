import { useEffect, useReducer, useState } from 'react'
import { ntpAPI } from '../APIs/ntpAPI'
import {
  initialTable,
  TableContext,
  TableDispatchContext,
} from '../contexts/TableContext'
import { tableReducer } from '../reducers/tableReducer'
import { Form } from './Form'
import { Input } from './Input'
import { Table } from './Table/Table'

export function Ntp() {
  const [timeZone, setTimeZone] = useState({} as number)
  const [serversTable, dispatchServersTable] = useReducer(
    tableReducer,
    initialTable
  )

  async function fetchNtpConfig() {
    const data = await ntpAPI.get()
    setTimeZone(data.timeZone)
    dispatchServersTable({
      type: 'set',
      table: { title: 'Servers', items: data.servers },
    })
  }

  useEffect(() => {
    fetchNtpConfig()
  }, [])

  function handleSubmit(e: React.FormEvent) {
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
      submitButtonContent='Submit Config'
      clearButtonContent='Clear Config'
    >
      <Input
        label='Time zone'
        id='timeZone'
        type='number'
        min='-12'
        max='14'
        value={timeZone}
        onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
          setTimeZone(e.target.valueAsNumber)
        }}
      />
      <TableContext.Provider value={serversTable}>
        <TableDispatchContext.Provider value={dispatchServersTable}>
          <Table inputType='text' inputName='server' readOnlyTitle={true} />
        </TableDispatchContext.Provider>
      </TableContext.Provider>
    </Form>
  )
}
