import { useEffect, useState } from 'react'
import { schedulerAPI } from '../../APIs/schedulerAPI'
import { tablesAPI } from '../../APIs/tablesAPI'
import { useOptions } from '../../contexts/OptionsContext'
import { useSchedulerTitle } from '../../contexts/SchedulerTitleContext'
import { useTableDispatch } from '../../contexts/TableContext'
import { Button } from './../Button'

export function TableSelect() {
  const [options, setOptions] = useOptions()
  const [selected, setSelected] = useState<string>('')
  const [, setTitle] = useSchedulerTitle()
  const dispatchTable = useTableDispatch()

  async function fetchTableTitles() {
    const data = await tablesAPI.getTitles()
    setOptions([...options, ...data.title])
  }

  function createButtonAction(callback: () => void) {
    return () => {
      if (selected != '') {
        callback()
      }
    }
  }

  async function postScheduler() {
    setTitle(selected)
    const scheduler = await schedulerAPI.get()
    schedulerAPI.post({ ...scheduler, title: selected })
  }

  async function editTable() {
    dispatchTable({
      type: 'updateTitle',
      title: selected,
    })
    const data = await tablesAPI.get(selected)
    dispatchTable({
      type: 'set',
      table: { title: data.title, items: data.time },
    })
  }

  function deleteTable() {
    setOptions(options.filter((opt) => opt != selected))
    tablesAPI.delete(selected)
  }

  useEffect(() => {
    fetchTableTitles()
  }, [])

  return (
    <div className='flex items-center flex-col gap-y-2 px-2 w-full'>
      <select
        id='table-select'
        className='w-full bg-gray-100 p-2 rounded ring-2 ring-gray-300 focus:ring-sky-400'
        onChange={(e: React.ChangeEvent<HTMLSelectElement>) => {
          setSelected(e.currentTarget.value)
        }}
      >
        <option value=''>-- Select Table --</option>
        {options.map((opt) => (
          <option key={opt} value={opt}>
            {opt}
          </option>
        ))}
      </select>
      <div className='flex flex-wrap flex-row gap-x-2 w-full justify-center gap-y-2'>
        <Button
          color='green'
          className='py-2 px-7 text-white'
          onClick={createButtonAction(postScheduler)}
        >
          Set
        </Button>
        <Button
          color='red'
          className='py-2 px-7 text-white'
          onClick={createButtonAction(deleteTable)}
        >
          Delete
        </Button>
        <Button
          color='blue'
          className='py-2 px-7 text-white'
          onClick={createButtonAction(editTable)}
        >
          Edit
        </Button>
      </div>
    </div>
  )
}
