import { useEffect, useState } from 'react'
import { sheduleAPI } from '../APIs/sheduleAPI'
import { useShedule } from '../contexts/SheduleContext'

export function EnabledShedule() {
  const [shedule, setShedule] = useShedule()

  async function fetchShedule() {
    const data = await sheduleAPI.get()
    setShedule(data)
  }

  useEffect(() => {
    fetchShedule()
  }, [])
  return <div>{shedule.title}</div>
}
