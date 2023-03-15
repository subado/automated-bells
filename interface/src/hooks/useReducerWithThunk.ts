import type { Reducer, ReducerState, Dispatch, ReducerAction } from 'react'
import { useReducer } from 'react'

export function useReducerWithThunk<R extends Reducer<any, any>>(
  reducer: R,
  initialState: ReducerState<R>,
  initializer?: undefined
): [ReducerState<R>, typeof dispatchWithThunk] {
  const [state, dispatch] = useReducer(reducer, initialState, initializer)

  function dispatchWithThunk(
    action: ReducerAction<R> | ((D: Dispatch<ReducerAction<R>>) => void)
  ): void {
    if (typeof action === 'function') {
      action(dispatch)
    } else {
      dispatch(action)
    }
  }

  return [state, dispatchWithThunk]
}
