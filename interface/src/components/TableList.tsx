import React, { useEffect } from 'react'
import { tablesAPI } from '../api/tablesAPI'
import { sheduleAPI } from '../api/sheduleAPI'
import { useTableList } from '../contexts/TableListContext'
import { useTable } from '../contexts/TableContext'

export function TableList() {
  const { state: tableList, dispatch: dispatchTableList } = useTableList()
  const { state: table, dispatch: dispatchTable } = useTable()
  async function fetchTableList() {
    const titles = await tablesAPI.getTableTitles()
    const selected = await sheduleAPI.getTitle()
    dispatchTableList({
      type: 'setTitles',
      title: titles.title,
    })
    dispatchTableList({
      type: 'select',
      selected: selected.title,
    })
  }

  useEffect(() => {
    fetchTableList()
  }, [])

  return (
    <ul className='m-auto text-center'>
      {tableList.title.map((title) => {
        return (
          <li
            key={title}
            className='flex-mb-4 items-center
            font-semibold'
          >
            {title}
            <input
              type='radio'
              name='select'
              value={title}
              checked={tableList.selected === title}
              onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
                dispatchTableList({
                  type: 'select',
                  selected: title,
                })
                dispatchTable({
                  type: 'updateTitle',
                  title: title,
                })
              }}
              className='ml-2'
            />
          </li>
        )
      })}
    </ul>
  )
}
