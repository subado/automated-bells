import { EnabledScheduler } from './EnabledScheduler'
import { Time } from './Time'

export function Header() {
  return (
    <div className='inline-flex justify-between w-[95vmin] py-1 px-3 bg-gray-100 shadow-sm shadow-gray-500 rounded-b'>
      <EnabledScheduler />
      <div className='border-l border-gray-400 pl-5'>
        <Time />
      </div>
    </div>
  )
}
