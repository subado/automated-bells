import { sheduleAPI } from './api/sheduleAPI'
import { Time } from './components/Time'
import { Table } from './components/Table/Table'
import { TableProvider } from './contexts/TableContext'
import { TimeProvider } from './contexts/TimeContext'

function App() {
  return (
    <div className='container m-auto'>
      <TimeProvider>
        <Time />
      </TimeProvider>
      <TableProvider>
        <Table />
      </TableProvider>
    </div>
  )
}

export default App
