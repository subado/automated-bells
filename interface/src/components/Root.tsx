import { OptionsProvider } from '../contexts/OptionsContext'
import { SchedulerProvider } from '../contexts/SchedulerContext'
import { TableProvider } from '../contexts/TableContext'
import { Header } from './Header'
import { TableEditor } from './TableEditor'
import { TableSelect } from './TableSelect'

export function Root() {
  return (
    <div className='h-screen flex flex-col items-center gap-y-5 text-[4vmin]'>
      <TableProvider>
        <OptionsProvider>
          <SchedulerProvider>
            <Header />
            <TableSelect />
          </SchedulerProvider>
          <TableEditor />
        </OptionsProvider>
      </TableProvider>
    </div>
  )
}
