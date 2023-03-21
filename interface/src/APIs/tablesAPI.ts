import { api } from '../constants'
import type { ITable, ITableTitles } from '../interfaces'

export const tablesAPI = {
  async get(title: string) {
    const response = await api.get<ITable>(`tables/${title}/`)
    return response.data
  },
  async delete(title: string) {
    return await api.delete<ITable>(`tables/${title}/`)
  },
  async getTitles() {
    const response = await api.get<ITableTitles>(`tables/`)
    return response.data
  },
}
