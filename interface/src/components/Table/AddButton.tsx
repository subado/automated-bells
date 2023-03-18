import { useTableDispatch } from '../../contexts/TableContext'

interface AddButtonProps {
  index: number
}

export function AddButton({ index }: AddButtonProps) {
  const dispatch = useTableDispatch()
  return (
    <button
      type='button'
      onClick={() => {
        dispatch({
          type: 'addTimeItem',
          index: index + 1,
        })
      }}
      className='bg-green-500 hover:bg-green-700 font-bold w-[50%] rounded text-lg text-white'
    >
      +
    </button>
  )
}
