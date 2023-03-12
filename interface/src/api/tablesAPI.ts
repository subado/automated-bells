import { instance } from './api'
import { ITable, ITableTitles } from '../interfaces/ITable'

export const tablesAPI = {
  async getTables(tableTitle: string) {
    const response = await instance.get<ITable>(`tables/${tableTitle}`)
    return response.data
  },
  async getTableTitles() {
    const response = await instance.get<ITableTitles>(`tables/`)
    return response.data
  },
}
