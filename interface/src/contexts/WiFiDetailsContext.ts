import type { Dispatch, SetStateAction } from 'react'
import { useContext, createContext } from 'react'
import type { IWiFiDetails } from '../interfaces'

export const initialWiFiDetails: IWiFiDetails = {
  ssid: '',
  psk: '',
}

type WiFiDetailsContextProps = [
  IWiFiDetails,
  Dispatch<SetStateAction<IWiFiDetails>>
]

export const WiFiDetailsContext = createContext({} as WiFiDetailsContextProps)

export function useWiFiDetails() {
  return useContext(WiFiDetailsContext)
}
