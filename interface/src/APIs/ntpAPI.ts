import { api } from '../constants'
import type { INtp } from '../interfaces'

export const ntpAPI = {
  async get() {
    const response = await api.get<INtp>('ntp/')
    return response.data
  },
  async post(config: INtp) {
    return await api.post<INtp>('ntp/', config)
  },
}
