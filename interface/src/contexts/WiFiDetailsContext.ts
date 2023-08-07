import { useState } from 'react'
import { useContext, createContext } from 'react'
import type { IWiFiDetails } from '../interfaces'

export const initialState: IWiFiDetails = {
  ssid: '',
  psk: '',
}

const wrappedUseState = () => useState(initialState)
type WiFiDetailsContextProps = ReturnType<typeof wrappedUseState>

export const WiFiDetailsContext = createContext({} as WiFiDetailsContextProps)

export function useWiFiDetails() {
  return useContext(WiFiDetailsContext)
}
