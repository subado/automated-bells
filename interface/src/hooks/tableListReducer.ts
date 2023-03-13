import { TableTitleType, ITableList } from '../interfaces/ITable'

export type TableListAction =
  | {
      type: 'setTitles'
      title: TableTitleType[]
    }
  | {
      type: 'select'
      selected: ITableList['selected']
    }

export function tableListReducer(
  state: ITableList,
  action: TableListAction
): ITableList {
  switch (action.type) {
    case 'setTitles':
      return { ...state, title: action.title }
    case 'select':
      return { ...state, selected: action.selected }
    default:
      throw new Error()
  }
}
