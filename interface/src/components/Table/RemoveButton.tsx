import { useTable } from '../../contexts/TableContext'

interface RemoveButtonProps {
  index: number
}

export function RemoveButton({ index }: RemoveButtonProps) {
  const { dispatch: dispatchTable } = useTable()
  return (
    <button
      type='button'
      onClick={() => {
        dispatchTable({
          type: 'removeTimeItem',
          index: index,
        })
      }}
      className='bg-red-500 hover:bg-red-700 font-bold w-[40px] rounded text-l text-white'
    >
      -
    </button>
  )
}
