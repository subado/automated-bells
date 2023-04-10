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
      type: 'updateItem'
      index: number
      item: ITable['items'][number]
    }
  | {
      type: 'addItem' | 'removeItem'
      index: number
    }
  | {
      type: 'clearItems'
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
    case 'updateItem':
      return {
        ...state,
        items: [
          ...state.items.map((t, i) => (i === action.index ? action.item : t)),
        ],
      }
    case 'addItem':
      state.items.splice(action.index, 0, '')
      return {
        ...state,
        items: state.items,
      }
    case 'removeItem':
      state.items.splice(action.index, 1)
      return {
        ...state,
        items: state.items,
      }
    case 'clearItems':
      return { ...state, items: [] }
    default:
      throw new Error()
  }
}
