import { Table } from './Table/Table'

export function TableEditor() {
  return (
    <form className='flex flex-col items-center gap-y-5'>
      <Table />
      <button
        type='submit'
        className='bg-orange-500 hover:bg-orange-700 font-bold rounded text-white p-2 w-[50vmin]'
      >
        Submit Table
      </button>
    </form>
  )
}
