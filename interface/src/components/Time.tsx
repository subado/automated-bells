import { useEffect } from 'react'
import { timeAPI } from '../api/timeAPI'
import { useTime } from '../contexts/TimeContext'

export function Time() {
  const { state: timeState, setState: setTime } = useTime()

  async function fetchTime() {
    const data = await timeAPI.getTime()
    setTime(data)
  }

  useEffect(() => {
    fetchTime()
    setInterval(fetchTime, 1000)
  }, [])

  return (
    <p className='p-1 w-min m-auto bg-gray-50 border border-gray-300 rounded-xl'>
      {timeState.time}
    </p>
  )
}
