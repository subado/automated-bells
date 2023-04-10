import { useMenuOpen } from '../../contexts/MenuOpenContext'
import { Button } from './../Button'
import { EnabledScheduler } from './EnabledScheduler'
import { Time } from './Time'

export function Header() {
  const [, setMenuOpen] = useMenuOpen()

  return (
    <header className='inline-flex justify-between w-full py-1 px-2 bg-gray-100 shadow-sm shadow-gray-500 rounded-b sticky top-0'>
      <Button
        color='lightGray'
        className='w-[15%] pr-2'
        text='text-black'
        isAnimated={false}
        onClick={() => setMenuOpen(true)}
      >
        ☰
      </Button>
      <span className='px-2 border-x border-gray-400 w-full'>
        <EnabledScheduler />
      </span>
      <span className='pl-2'>
        <Time />
      </span>
    </header>
  )
}
