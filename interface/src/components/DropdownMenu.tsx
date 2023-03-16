import { useEffect } from 'react'
import { tablesAPI } from '../APIs/tablesAPI'
import {
  useDropdownMenu,
  useDropdownMenuDispatch,
} from '../contexts/DropdownMenuContext'

interface PropsType {
  name: string
}

export function DropdownMenu(props: PropsType) {
  const menu = useDropdownMenu()
  const dispatch = useDropdownMenuDispatch()

  async function fetchTableTitles() {
    const data = await tablesAPI.getTableTitles()
    dispatch({ type: 'set', list: data.title })
  }

  useEffect(() => {
    fetchTableTitles()
  }, [])

  function toggleEnable() {
    if (menu.isEnable) {
      dispatch({ type: 'disable' })
    } else {
      dispatch({ type: 'enable' })
    }
  }

  function handleButtonToggling(e: React.MouseEvent<HTMLButtonElement>) {
    toggleEnable()
  }

  function handleItemSelecting(e: React.MouseEvent<HTMLButtonElement>) {
    const button: HTMLButtonElement = e.currentTarget
    dispatch({ type: 'select', item: button.name })
    toggleEnable()
  }

  return (
    <div className='m-2 relative text-left'>
      <button
        className='inline-flex w-full justify-center gap-x-1.5 rounded-md bg-white px-3 py-2 text-sm font-semibold text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 focus:ring-50 hover:bg-gray-50'
        type='button'
        onClick={handleButtonToggling}
      >
        {menu.selected === '' ? props.name : menu.selected}
        <svg
          className='-mr-1 h-5 w-5 text-gray-400'
          viewBox='0 0 20 20'
          fill='currentColor'
        >
          <path d='M5.23 7.21a.75.75 0 011.06.02L10 11.168l3.71-3.938a.75.75 0 111.08 1.04l-4.25 4.5a.75.75 0 01-1.08 0l-4.25-4.5a.75.75 0 01.02-1.06z' />
        </svg>
      </button>

      {menu.isEnable && (
        <div className='absolute right-0 origin-top-right z-10 mt-2 w-min rounded-md bg-white shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none'>
          {menu.list.map((v) => (
            <button
              key={v}
              name={v}
              onClick={handleItemSelecting}
              className='text-gray-700 block px-4 py-2 text-sm text-left hover:bg-gray-200 w-full'
            >
              {v}
            </button>
          ))}
        </div>
      )}
    </div>
  )
}
