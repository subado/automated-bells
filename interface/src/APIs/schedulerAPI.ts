import { api } from '../constants'
import type { IScheduler } from '../interfaces'

export const schedulerAPI = {
  async get() {
    const response = await api.get<IScheduler>('scheduler/')
    return response.data
  },
  async post(scheduler: IScheduler) {
    return await api.post<IScheduler>('scheduler/', scheduler)
  },
}
