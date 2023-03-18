import { DropdownMenuProvider } from '../contexts/DropdownMenuContext'
import { DropdownMenu } from './DropdownMenu'
import { Time } from './Time'

export function Root() {
  return (
    <div className='flex flex-col items-center'>
      <Time />
      <DropdownMenuProvider>
        <DropdownMenu name='Choose item' />
      </DropdownMenuProvider>
    </div>
  )
}
