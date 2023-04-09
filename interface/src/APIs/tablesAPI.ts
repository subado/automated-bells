import { api } from '../constants'
import type { ITableTime, ITableTitles } from '../interfaces'

export const tablesAPI = {
  async get(title: string) {
    const response = await api.get<ITableTime>(`tables/${title}/`)
    return response.data
  },
  async delete(title: string) {
    return await api.delete<ITableTime>(`tables/${title}/`)
  },
  async post(table: ITableTime) {
    return await api.post<ITableTime>('tables/', table)
  },
  async getTitles() {
    const response = await api.get<ITableTitles>('tables/')
    return response.data
  },
}
