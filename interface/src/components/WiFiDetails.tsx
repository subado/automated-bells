import type { ChangeEvent } from 'react'
import { useWiFiDetails } from '../contexts/WiFiDetailsContext'
import { Input } from './styled'

interface IWiFIDetailsProps {
  title: string
  idForSsid: string
  idForPsk: string
  className?: string
}

export function WiFiDetails({
  title,
  idForSsid,
  idForPsk,
  className,
}: IWiFIDetailsProps) {
  const [details, setDetails] = useWiFiDetails()

  function onChangeSsid(e: ChangeEvent<HTMLInputElement>) {
    setDetails({ ...details, ssid: e.currentTarget.value })
  }

  function onChangePsk(e: ChangeEvent<HTMLInputElement>) {
    setDetails({ ...details, psk: e.currentTarget.value })
  }

  return (
    <>
      <div className='flex flex-col gap-y-3 items-center w-full'>
        <h1
          className={`text-[130%] font-black w-full text-center border-b-4 ${className}`}
        >
          {title}
        </h1>
        <label htmlFor={idForSsid}>
          SSID
          <Input
            id={idForSsid}
            type='text'
            value={details.ssid}
            onChange={onChangeSsid}
            required={true}
          />
        </label>
        <label htmlFor={idForPsk}>
          PSK
          <Input
            id={idForPsk}
            type='text'
            value={details.psk}
            onChange={onChangePsk}
          />
        </label>
      </div>
    </>
  )
}
