export type TableTitleType = string

export interface ITable {
  title: TableTitleType
  time: string[]
}

export interface ITableTitles {
  title: TableTitleType[]
}

export interface ITableList extends ITableTitles {
  selected: TableTitleType
}
