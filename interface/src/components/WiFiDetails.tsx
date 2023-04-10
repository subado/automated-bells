import { useWiFiDetails } from '../contexts/WiFiDetailsContext'
import { Input } from './Input'

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

  function onChangeSsid(e: React.ChangeEvent<HTMLInputElement>) {
    setDetails({ ...details, ssid: e.target.value })
  }

  function onChangePsk(e: React.ChangeEvent<HTMLInputElement>) {
    setDetails({ ...details, psk: e.target.value })
  }

  return (
    <>
      <div className='flex flex-col gap-y-3 items-center w-full'>
        <h1
          className={`text-[130%] font-black w-full text-center border-b-4 ${className}`}
        >
          {title}
        </h1>
        <Input
          label='SSID'
          id={idForSsid}
          type='text'
          value={details.ssid}
          onChange={onChangeSsid}
          required={true}
        />
        <Input
          label='PSK'
          id={idForPsk}
          type='text'
          value={details.psk}
          onChange={onChangePsk}
        />
      </div>
    </>
  )
}
