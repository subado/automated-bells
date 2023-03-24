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
          type: 'removeTimeItem',
          index: index,
        })
      }}
      className='w-[50%]'
    >
      -
    </Button>
  )
}
