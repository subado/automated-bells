import { instance } from './api'
import { ITime } from '../interfaces/ITime'

export const timeAPI = {
  async getTime() {
    const response = await instance.get<ITime>(`time/`)
    return response.data
  },
}
