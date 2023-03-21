import { Header } from './Header'
import { TableEditor } from './TableEditor'
import { TableSelect } from './TableSelect'

export function Root() {
  return (
    <div className='flex flex-col items-center gap-y-5'>
      <Header />
      <TableSelect />
      <TableEditor />
    </div>
  )
}
