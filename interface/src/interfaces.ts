export interface ITableTime {
  title: string
  time: string[]
}

export interface ITable {
  title: string
  items: string[]
}

export interface ITableTitles {
  title: string[]
}

export interface ITime {
  hour: string
  minute: string
  second: string
}

export interface IChildrenProps {
  children: React.ReactNode
}

export interface IScheduler {
  title: string
}

export interface INtp {
  servers: string[]
  timeZone: number
}

export interface IWiFiDetails {
  ssid: string
  psk: string
}

export interface IWiFi {
  sta: IWiFiDetails
  ap: IWiFiDetails
}
