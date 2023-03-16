import type { IDropdownMenuState } from '../interfaces'

export type DropdownMenuAction =
  | {
      type: 'push' | 'remove' | 'select'
      item: string
    }
  | {
      type: 'set'
      list: string[]
    }
  | {
      type: 'enable' | 'disable'
    }

export function dropdownMenuReducer(
  state: IDropdownMenuState,
  action: DropdownMenuAction
) {
  switch (action.type) {
    case 'push':
      state.list.push(action.item)
      return { ...state }
    case 'remove':
      return {
        ...state,
        list: state.list.filter((v) => {
          if (v === action.item) {
            return action.item
          } else {
            return v
          }
        }),
      }
    case 'select':
      return {
        ...state,
        selected: action.item,
      }
    case 'set':
      return { ...state, list: action.list }
    case 'enable':
      return { ...state, isEnable: true }
    case 'disable':
      return { ...state, isEnable: false }
  }
}
