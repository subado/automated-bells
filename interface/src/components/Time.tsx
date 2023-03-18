import { useState, useEffect } from 'react'
import { timeAPI } from '../APIs/timeAPI'
import type { ITime } from '../interfaces'

export function Time() {
  const initialState: ITime = {
    hour: '',
    minute: '',
    second: '',
  }
  const [time, setTime] = useState<ITime>(initialState)

  async function fetchTime() {
    const data = await timeAPI.getTime()
    setTime(data)
  }

  useEffect(() => {
    fetchTime()
    setInterval(fetchTime, 1000)
  }, [])

  return (
    <div className='inline-flex align-middle gap-x-2.5 py-1 px-3 bg-gray-50 text-black shadow-sm shadow-black'>
      <p>{time.hour}</p>:<p>{time.minute}</p>:<p>{time.second}</p>
    </div>
  )
}
