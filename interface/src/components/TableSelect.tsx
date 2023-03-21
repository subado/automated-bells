import { useEffect, useState } from 'react'
import { sheduleAPI } from '../APIs/sheduleAPI'
import { tablesAPI } from '../APIs/tablesAPI'
import { useShedule } from '../contexts/SheduleContext'
import { useTableDispatch } from '../contexts/TableContext'

const ColorVariants = {
  green: 'bg-green-500 hover:bg-green-700',
  blue: 'bg-blue-500 hover:bg-blue-700',
  red: 'bg-red-500 hover:bg-red-700',
}

interface IButtonProps {
  color: keyof typeof ColorVariants
  content: string
  onClick?: React.MouseEventHandler<HTMLButtonElement> | undefined
}

function Button({ color, content, onClick }: IButtonProps) {
  return (
    <button
      type='button'
      className={`${ColorVariants[color]} font-bold rounded text-white p-2 w-[30%]`}
      onClick={onClick}
    >
      {content}
    </button>
  )
}

export function TableSelect() {
  const [options, setOptions] = useState<string[]>([])
  const [selected, setSelected] = useState<string>('')
  const [, setShedule] = useShedule()
  const dispatchTable = useTableDispatch()

  async function fetchTableTitles() {
    const data = await tablesAPI.getTitles()
    setOptions(data.title)
    setSelected(data.title[0])
  }

  function postShedule() {
    setShedule({ title: selected })
    sheduleAPI.post({ title: selected })
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

  useEffect(() => {
    fetchTableTitles()
  }, [])

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
          content='Set'
          onClick={() => {
            postShedule()
          }}
        />
        <Button
          color='blue'
          content='Edit'
          onClick={() => {
            editTable()
          }}
        />
        <Button color='red' content='Delete' />
      </div>
    </div>
  )
}
