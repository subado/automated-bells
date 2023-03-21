import { api } from '../constants'
import type { IShedule } from '../interfaces'

export const sheduleAPI = {
  async getEnabledTitle() {
    const response = await api.get<IShedule>('shedule/')
    return response.data
  },
}
