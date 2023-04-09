import { api } from '../constants'
import type { IWiFi } from '../interfaces'

export const wifiAPI = {
  async get() {
    const response = await api.get<IWiFi>('wifi/')
    return response.data
  },
  async post(config: IWiFi) {
    return await api.post<IWiFi>('wifi/', config)
  },
}
