import { AxiosError } from 'axios'
import React, { useEffect } from 'react'
import { tablesAPI } from '../../api/tablesAPI'
import { useTable } from '../../contexts/TableContext'
import { AddButton } from './AddButton'
import { RemoveButton } from './RemoveButton'

export function Table() {
  const { state: table, dispatch: dispatchTable } = useTable()

  async function fetchTable() {
    if (table.title !== '') {
      try {
        const data = await tablesAPI.getTables(table.title)
        dispatchTable({
          type: 'set',
          table: data,
        })
      } catch (error: unknown) {
        table.time = []
      }
    }
  }

  useEffect(() => {
    fetchTable()
  }, [table.title])

  return (
    <table className='w-fit text-center m-auto'>
      <thead className='bg-gray-100 border-b-2 border-gray-200'>
        <tr>
          <th colSpan={2}>
            <input
              className='bg-gray-100 text-center p-2 font-semibold tracking-wide placeholder:italic placeholder:text-slate-400'
              placeholder='Title'
              type='text'
              name='title'
              value={table.title}
              onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
                dispatchTable({
                  type: 'updateTitle',
                  title: event.target.value,
                })
              }}
              required={true}
            />
          </th>
        </tr>
      </thead>
      <tbody>
        {table.time.length === 0 && (
          <tr>
            <td>
              <AddButton index={0} />
            </td>
          </tr>
        )}
        {table.time.map((time, i) => {
          return (
            <tr
              className='odd:bg-white even:bg-gray-100 border-2 border-gray-200'
              key={i}
            >
              <td className='px-3 py-1 rounded'>
                <input
                  type='time'
                  name='time'
                  value={time}
                  onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
                    dispatchTable({
                      type: 'updateTimeItem',
                      index: i,
                      item: event.target.value,
                    })
                  }}
                  required={true}
                />
              </td>
              <td className=''>
                <AddButton index={i} />
                <RemoveButton index={i} />
              </td>
            </tr>
          )
        })}
      </tbody>
    </table>
  )
}
