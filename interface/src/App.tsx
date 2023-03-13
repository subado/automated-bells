import { Time } from './components/Time'
import { Table } from './components/Table/Table'
import { TableList } from './components/TableList'
import { TableProvider } from './contexts/TableContext'
import { TimeProvider } from './contexts/TimeContext'
import { TableListProvider } from './contexts/TableListContext'

function App() {
  return (
    <div className='container m-auto'>
      <TimeProvider>
        <Time />
      </TimeProvider>
      <TableProvider>
        <TableListProvider>
          <TableList />
        </TableListProvider>
        <Table />
      </TableProvider>
    </div>
  )
}

export default App
