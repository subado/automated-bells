import { api } from '../constants'
import type { IShedule } from '../interfaces'

export const sheduleAPI = {
  async getTitle() {
    const response = await api.get<IShedule>('shedule/')
    return response.data
  },
  async postTitle(title: string) {
    const response = await api.post<IShedule>('shedule/', { title: title })
    return response.data
  },
}
