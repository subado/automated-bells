import { TableProvider } from '../contexts/TableContext'
import { Table } from './Table/Table'

export function TableEditor() {
  return (
    <TableProvider>
      <Table />
    </TableProvider>
  )
}
