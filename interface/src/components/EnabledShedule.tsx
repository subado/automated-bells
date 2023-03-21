import { useEffect, useState } from 'react'
import { sheduleAPI } from '../APIs/sheduleAPI'

export function EnabledShedule() {
  const [enabled, setEnabled] = useState<string>('')

  async function fetchShedule() {
    const data = await sheduleAPI.getEnabledTitle()
    setEnabled(data.title)
  }

  useEffect(() => {
    fetchShedule()
  }, [])
  return <div>{enabled}</div>
}
