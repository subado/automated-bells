import { useEffect } from 'react'
import { schedulerAPI } from '../../APIs/schedulerAPI'
import { useSchedulerTitle } from '../../contexts/SchedulerTitleContext'

export function SchedulerTitle() {
  const [title, setTitle] = useSchedulerTitle()

  async function fetchSchedulerTitle() {
    const data = await schedulerAPI.get()
    setTitle(data.title)
  }

  useEffect(() => {
    fetchSchedulerTitle()
  }, [])

  return <span>{title}</span>
}
