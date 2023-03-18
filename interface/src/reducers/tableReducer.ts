import type { ITable } from '../interfaces'

export type TableAction =
  | {
      type: 'set'
      table: ITable
    }
  | {
      type: 'updateTitle'
      title: ITable['title']
    }
  | {
      type: 'updateTimeItem'
      index: number
      item: ITable['time'][number]
    }
  | {
      type: 'addTimeItem' | 'removeTimeItem'
      index: number
    }

export function tableReducer(state: ITable, action: TableAction): ITable {
  switch (action.type) {
    case 'set':
      return action.table
    case 'updateTitle':
      return {
        ...state,
        title: action.title,
      }
    case 'updateTimeItem':
      return {
        ...state,
        time: [
          ...state.time.map((t, i) => (i === action.index ? action.item : t)),
        ],
      }
    case 'addTimeItem':
      state.time.splice(action.index, 0, '')
      return {
        ...state,
        time: state.time,
      }
    case 'removeTimeItem':
      state.time.splice(action.index, 1)
      return {
        ...state,
        time: state.time,
      }
    default:
      throw new Error()
  }
}
