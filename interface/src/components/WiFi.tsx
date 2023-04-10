import { useEffect, useState } from 'react'
import { wifiAPI } from '../APIs/wifiAPI'
import {
  initialWiFiDetails,
  WiFiDetailsContext,
} from '../contexts/WiFiDetailsContext'
import { Form } from './Form'
import { WiFiDetails } from './WiFiDetails'

export function WiFi() {
  const [staConfig, setStaConfig] = useState(initialWiFiDetails)
  const [apConfig, setApConfig] = useState(initialWiFiDetails)

  async function fetchWiFiConfig() {
    const data = await wifiAPI.get()
    setStaConfig(data.sta)
    setApConfig(data.ap)
  }

  useEffect(() => {
    fetchWiFiConfig()
  }, [])

  function handleSubmit(e: React.FormEvent) {
    e.preventDefault()
    wifiAPI.post({ sta: staConfig, ap: apConfig })
  }

  function handleClear() {
    setStaConfig(initialWiFiDetails)
    setApConfig(initialWiFiDetails)
  }

  return (
    <Form
      onSubmit={handleSubmit}
      onClear={handleClear}
      submitButtonContent='Submit Config'
      clearButtonContent='Clear Config'
    >
      <WiFiDetailsContext.Provider value={[staConfig, setStaConfig]}>
        <WiFiDetails
          title='STA'
          idForSsid='staSsid'
          idForPsk='staPsk'
          className='border-teal-500 text-teal-500'
        />
      </WiFiDetailsContext.Provider>
      <WiFiDetailsContext.Provider value={[apConfig, setApConfig]}>
        <WiFiDetails
          title='AP'
          idForSsid='apSsid'
          idForPsk='apPsk'
          className='border-indigo-500 text-indigo-500'
        />
      </WiFiDetailsContext.Provider>
    </Form>
  )
}
