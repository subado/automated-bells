import { useEffect, useState } from 'react'
import { tablesAPI } from '../APIs/tablesAPI'

const ColorVariants = {
  green: 'bg-green-500 hover:bg-green-700',
  blue: 'bg-blue-500 hover:bg-blue-700',
  red: 'bg-red-500 hover:bg-red-700',
}

interface IButtonProps {
  color: keyof typeof ColorVariants
  content: string
}

function Button({ color, content }: IButtonProps) {
  return (
    <button
      type='button'
      className={`${ColorVariants[color]} font-bold rounded text-white p-2 w-[30%]`}
    >
      {content}
    </button>
  )
}

export function TableSelect() {
  const [options, setOptions] = useState<string[]>([])

  async function fetchTableTitles() {
    const data = await tablesAPI.getTableTitles()
    setOptions(data.title)
  }

  useEffect(() => {
    fetchTableTitles()
  }, [])

  return (
    <div className='flex items-center flex-col '>
      <select className='w-[95vmin] bg-gray-100 p-2 rounded ring-2 ring-gray-300 focus:ring-sky-400'>
        {options.map((opt) => (
          <option key={opt} value={opt}>
            {opt}
          </option>
        ))}
      </select>
      <div className='flex flex-row gap-x-5 mt-2 w-[95vmin] justify-center'>
        <Button color='green' content='Set' />
        <Button color='blue' content='Edit' />
        <Button color='red' content='Delete' />
      </div>
    </div>
  )
}
