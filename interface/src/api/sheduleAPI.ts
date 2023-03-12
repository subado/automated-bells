import { instance } from './api'
import { TableTitleType } from '../interfaces/ITable'

export const sheduleAPI = {
  async getTitle() {
    const response = await instance.get<TableTitleType>(`shedule/`)
    return response.data
  },
}
