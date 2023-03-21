import { api } from '../constants'
import type { ITable, ITableTitles } from '../interfaces'

export const tablesAPI = {
  async get(tableTitle: string) {
    const response = await api.get<ITable>(`tables/${tableTitle}/`)
    return response.data
  },
  async delete(tableTitle: string) {
    return await api.delete<ITable>(`tables/${tableTitle}/`)
  },
  async getTitles() {
    const response = await api.get<ITableTitles>(`tables/`)
    return response.data
  },
}
