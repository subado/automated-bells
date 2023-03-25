import { useEffect } from 'react'
import { schedulerAPI } from '../APIs/schedulerAPI'
import { useScheduler } from '../contexts/SchedulerContext'

export function EnabledScheduler() {
  const [scheduler, setScheduler] = useScheduler()

  async function fetchScheduler() {
    const data = await schedulerAPI.get()
    setScheduler(data)
  }

  useEffect(() => {
    fetchScheduler()
  }, [])
  return <div>{scheduler.title}</div>
}
