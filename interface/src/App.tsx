import { Time } from './components/Time'
import { DropdownMenu } from './components/DropdownMenu'
import { DropdownMenuProvider } from './contexts/DropdownMenuContext'

function App() {
  return (
    <div className='flex flex-col items-center'>
      <Time />
      <DropdownMenuProvider>
        <DropdownMenu name='Choose item' />
      </DropdownMenuProvider>
    </div>
  )
}

export default App
