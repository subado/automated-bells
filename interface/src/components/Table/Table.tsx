import React, { useEffect } from 'react'
import { useParams } from 'react-router-dom'
import { tablesAPI } from '../../APIs/tablesAPI'
import { useTable } from '../../contexts/TableContext'
import { useTableDispatch } from '../../contexts/TableContext'
import { AddButton } from './AddButton'
import { RemoveButton } from './RemoveButton'

export function Table() {
  const table = useTable()
  const dispatch = useTableDispatch()
  const params = useParams<{ title?: string }>()

  async function fetchTable() {
    try {
      const data = await tablesAPI.getTables(params.title as string)
      dispatch({
        type: 'set',
        table: data,
      })
    } catch (error: unknown) {
      table.time = []
    }
  }

  useEffect(() => {
    fetchTable()
  }, [])

  return (
    <table className='text-center w-full'>
      <thead className='bg-gray-100 border-b-2 border-gray-200'>
        <tr>
          <th colSpan={2}>
            <input
              className='bg-gray-100 w-full text-center p-2 font-semibold tracking-wide placeholder:italic placeholder:text-slate-400'
              placeholder='Title'
              type='text'
              name='title'
              value={table.title}
              onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
                dispatch({
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
        {table.time.map((item, i) => (
          <tr
            className='odd:bg-white even:bg-gray-100 border-2 border-gray-200'
            key={i}
          >
            <td className='px-3 py-1 rounded w-[50%]'>
              <input
                type='time'
                name='time'
                value={item}
                onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
                  dispatch({
                    type: 'updateTimeItem',
                    index: i,
                    item: event.target.value,
                  })
                }}
                required={true}
                className='text-lg'
              />
            </td>
            <td className='w-[50%]'>
              <AddButton index={i} />
              <RemoveButton index={i} />
            </td>
          </tr>
        ))}
      </tbody>
    </table>
  )
}
