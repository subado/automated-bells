import { useEffect, useState } from 'react'
import { schedulerAPI } from '../../APIs/schedulerAPI'
import { tablesAPI } from '../../APIs/tablesAPI'
import { useOptions } from '../../contexts/OptionsContext'
import { useScheduler } from '../../contexts/SchedulerContext'
import { useTableDispatch } from '../../contexts/TableContext'
import { ButtonList } from '../ButtonList'
import { Button } from './../Button'

export function TableSelect() {
  const [options, setOptions] = useOptions()
  const [selected, setSelected] = useState<string>('')
  const [, setScheduler] = useScheduler()
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
      <ButtonList buttonClassName='p-2'>
        <Button color='green' onClick={createButtonAction(postShedule)}>
          Set
        </Button>
        <Button color='blue' onClick={createButtonAction(editTable)}>
          Edit
        </Button>
        <Button color='red' onClick={createButtonAction(deleteTable)}>
          Delete
        </Button>
      </ButtonList>
    </div>
  )
}