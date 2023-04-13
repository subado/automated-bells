import { useTableDispatch } from '../../contexts/TableContext'
import { Button } from '../Button'

interface RemoveButtonProps {
  index: number
}

export function RemoveButton({ index }: RemoveButtonProps) {
  const dispatch = useTableDispatch()
  return (
    <Button
      color='rose'
      onClick={() => {
        dispatch({
          type: 'removeItem',
          index: index,
        })
      }}
      className='w-[50%] py-2 text-white'
    >
      -
    </Button>
  )
}
