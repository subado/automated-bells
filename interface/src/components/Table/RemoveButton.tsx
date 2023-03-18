import { useTableDispatch } from '../../contexts/TableContext'

interface RemoveButtonProps {
  index: number
}

export function RemoveButton({ index }: RemoveButtonProps) {
  const dispatch = useTableDispatch()
  return (
    <button
      type='button'
      onClick={() => {
        dispatch({
          type: 'removeTimeItem',
          index: index,
        })
      }}
      className='bg-red-500 hover:bg-red-700 font-bold w-[50%] rounded text-lg text-white'
    >
      -
    </button>
  )
}
