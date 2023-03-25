import { useEffect, useState } from 'react'
import { schedulerAPI } from '../APIs/schedulerAPI'
import { tablesAPI } from '../APIs/tablesAPI'
import { useOptions } from '../contexts/OptionsContext'
import { useScheduler } from '../contexts/SchedulerContext'
import { useTableDispatch } from '../contexts/TableContext'
import { Button } from './Button'

export function TableSelect() {
  const [options, setOptions] = useOptions()
  const [selected, setSelected] = useState<string>('')
  const [, setScheduler] = useScheduler()
  const dispatchTable = useTableDispatch()

  async function fetchTableTitles() {
    const data = await tablesAPI.getTitles()
    setOptions(data.title)
  }

  function createButtonAction(callback: () => void) {
    return () => {
      if (selected != '') {
        callback()
      }
    }
  }

  function postShedule() {
    setScheduler({ title: selected })
    schedulerAPI.post({ title: selected })
  }

  async function editTable() {
    dispatchTable({
      type: 'updateTitle',
      title: selected,
    })
    const data = await tablesAPI.get(selected)
    dispatchTable({
      type: 'set',
      table: data,
    })
  }

  function deleteTable() {
    setOptions(options.filter((opt) => opt != selected))
    tablesAPI.delete(selected)
  }

  useEffect(() => {
    fetchTableTitles()
  }, [])

  useEffect(() => {
    setSelected(options.length ? options[0] : '')
  }, [options])

  return (
    <div className='flex items-center flex-col '>
      <select
        className='w-[95vmin] bg-gray-100 p-2 rounded ring-2 ring-gray-300 focus:ring-sky-400'
        onChange={(e: React.ChangeEvent<HTMLSelectElement>) => {
          setSelected(e.currentTarget.value)
        }}
      >
        {options.map((opt) => (
          <option key={opt} value={opt}>
            {opt}
          </option>
        ))}
      </select>
      <div className='flex flex-row gap-x-5 mt-2 w-[95vmin] justify-center'>
        <Button
          color='green'
          onClick={createButtonAction(postShedule)}
          className='p-2 w-[33%]'
        >
          Set
        </Button>
        <Button
          color='blue'
          onClick={createButtonAction(editTable)}
          className='p-2 w-[33%]'
        >
          Edit
        </Button>
        <Button
          color='red'
          onClick={createButtonAction(deleteTable)}
          className='p-2 w-[33%]'
        >
          Delete
        </Button>
      </div>
    </div>
  )
}
