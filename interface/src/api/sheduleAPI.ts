import { instance } from './api'
import { IShedule } from '../interfaces/IShedule'

export const sheduleAPI = {
  async getTitle() {
    const response = await instance.get<IShedule>(`shedule/`)
    return response.data
  },
  async postTitle(shedule: IShedule) {
    const response = await instance.post<IShedule>(`shedule/`, shedule)
    return response
  },
}
