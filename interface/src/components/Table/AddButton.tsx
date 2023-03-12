import { useTable } from '../../contexts/TableContext'

interface AddButtonProps {
  index: number
}

export function AddButton({ index }: AddButtonProps) {
  const { dispatch: dispatchTable } = useTable()
  return (
    <button
      type='button'
      onClick={() => {
        dispatchTable({
          type: 'addTimeItem',
          index: index + 1,
        })
      }}
      className='bg-green-500 hover:bg-green-700 font-bold w-[40px] rounded text-l text-white'
    >
      +
    </button>
  )
}
