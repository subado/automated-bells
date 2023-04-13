import { useTableDispatch } from '../../contexts/TableContext'
import { Button } from '../Button'

interface AddButtonProps {
  index: number
}

export function AddButton({ index }: AddButtonProps) {
  const dispatch = useTableDispatch()
  return (
    <Button
      color='emerald'
      onClick={() => {
        dispatch({
          type: 'addItem',
          index: index + 1,
        })
      }}
      className='w-[50%] py-2 text-white'
    >
      +
    </Button>
  )
}
