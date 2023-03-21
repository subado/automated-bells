import { api } from '../constants'
import type { IShedule } from '../interfaces'

export const sheduleAPI = {
  async get() {
    const response = await api.get<IShedule>('shedule/')
    return response.data
  },
  async post(shedule: IShedule) {
    const response = await api.post<IShedule>('shedule/', shedule)
    return response
  },
}
