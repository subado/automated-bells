import type { Dispatch } from 'react'
import { useContext } from 'react'
import { useReducer, createContext } from 'react'
import type { IDropdownMenuState, IProviderProps } from '../interfaces'
import type { DropdownMenuAction } from '../reducers/dropdownMenuReducer'
import { dropdownMenuReducer } from '../reducers/dropdownMenuReducer'

const DropdownMenuContext = createContext({} as IDropdownMenuState)
const DropdownMenuDispatchContext = createContext(
  {} as Dispatch<DropdownMenuAction>
)

export function DropdownMenuProvider({ children }: IProviderProps) {
  const [menu, dispatch] = useReducer(dropdownMenuReducer, initialState)

  return (
    <DropdownMenuContext.Provider value={menu}>
      <DropdownMenuDispatchContext.Provider value={dispatch}>
        {children}
      </DropdownMenuDispatchContext.Provider>
    </DropdownMenuContext.Provider>
  )
}

export function useDropdownMenu() {
  return useContext(DropdownMenuContext)
}

export function useDropdownMenuDispatch() {
  return useContext(DropdownMenuDispatchContext)
}

const initialState: IDropdownMenuState = {
  list: [],
  selected: '',
}
