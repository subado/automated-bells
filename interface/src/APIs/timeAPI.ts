import { api } from '../constants'
import type { ITime } from '../interfaces'

export const timeAPI = {
  async getTime() {
    const response = await api.get<ITime>('time/')
    return response.data
  },
}
