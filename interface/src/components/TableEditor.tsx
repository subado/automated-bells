import { tablesAPI } from '../APIs/tablesAPI'
import { useOptions } from '../contexts/OptionsContext'
import { useTable } from '../contexts/TableContext'
import { Button } from './Button'
import { Table } from './Table/Table'

export function TableEditor() {
  const table = useTable()
  const [options, setOptions] = useOptions()

  function handleSubmit(e: React.FormEvent) {
    e.preventDefault()
    tablesAPI.post(table)
    if (!options.includes(table.title)) {
      setOptions([...options, table.title].sort())
    }
  }

  return (
    <form
      onSubmit={handleSubmit}
      className='flex flex-col items-center gap-y-5'
    >
      <Table />
      <Button color='orange' type='submit' className='p-2 w-[50vmin]'>
        Submit Table
      </Button>
    </form>
  )
}
