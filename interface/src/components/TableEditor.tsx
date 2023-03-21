import { TableProvider } from '../contexts/TableContext'
import { Table } from './Table/Table'

export function TableEditor() {
  return (
    <TableProvider>
      <Table />
      <button
        type='submit'
        className='bg-orange-500 hover:bg-orange-700 font-bold rounded text-white p-2 w-[50vmin]'
      >
        Submit Table
      </button>
    </TableProvider>
  )
}
