import { OptionsProvider } from '../contexts/OptionsContext'
import { SheduleProvider } from '../contexts/SheduleContext'
import { TableProvider } from '../contexts/TableContext'
import { Header } from './Header'
import { TableEditor } from './TableEditor'
import { TableSelect } from './TableSelect'

export function Root() {
  return (
    <div className='flex flex-col items-center gap-y-5'>
      <TableProvider>
        <OptionsProvider>
          <SheduleProvider>
            <Header />
            <TableSelect />
          </SheduleProvider>
          <TableEditor />
        </OptionsProvider>
      </TableProvider>
    </div>
  )
}
