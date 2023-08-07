import { useTable } from '../../contexts/TableContext'
import { useTableDispatch } from '../../contexts/TableContext'
import { AddButton } from './AddButton'
import { RemoveButton } from './RemoveButton'

export interface ITableProps {
  inputType: string
  inputName: string
  inputPattern?: string
  titlePattern?: string
  readOnlyTitle?: boolean
}

export function Table({
  inputType,
  inputName,
  inputPattern,
  titlePattern,
  readOnlyTitle,
}: ITableProps) {
  const table = useTable()
  const dispatch = useTableDispatch()

  function changeTitle(e: React.ChangeEvent<HTMLInputElement>) {
    dispatch({
      type: 'updateTitle',
      title: e.target.value,
    })
  }

  return (
    <table className='text-center w-full'>
      <thead className='bg-gray-100 border-b-2 border-gray-200'>
        <tr>
          <th colSpan={3}>
            <input
              className='text-center w-full bg-inherit p-2 tracking-wide placeholder:italic placeholder:text-slate-400'
              placeholder='Заголовок'
              type='text'
              name='title'
              pattern={titlePattern}
              value={table.title}
              onChange={changeTitle}
              readOnly={readOnlyTitle}
              required={true}
            />
          </th>
        </tr>
      </thead>
      <tbody>
        {table.items.length === 0 && (
          <tr>
            <td>
              <AddButton index={0} />
            </td>
          </tr>
        )}
        {table.items.map((item, i) => (
          <tr
            className='odd:bg-white even:bg-gray-100 border-2 border-gray-200'
            key={i}
          >
            <td className='w-1/12'>{i + 1}</td>
            <td className='border-x-2 border-gray-200'>
              <input
                type={inputType}
                name={inputName}
                pattern={inputPattern}
                value={item}
                onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
                  dispatch({
                    type: 'updateItem',
                    index: i,
                    item: e.target.value,
                  })
                }}
                required={true}
                className='w-full bg-inherit text-center text-xl'
              />
            </td>
            <td className='w-1/3'>
              <AddButton index={i} />
              <RemoveButton index={i} />
            </td>
          </tr>
        ))}
      </tbody>
    </table>
  )
}
