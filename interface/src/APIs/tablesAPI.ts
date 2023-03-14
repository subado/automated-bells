import { api } from '../constants'
import type { ITable, ITableTitles } from '../interfaces'

export const tablesAPI = {
  async getTables(tableTitle: string) {
    const response = await api.get<ITable>(`tables/${tableTitle}`)
    return response.data
  },
  async getTableTitles() {
    const response = await api.get<ITableTitles>(`tables/`)
    return response.data
  },
}
