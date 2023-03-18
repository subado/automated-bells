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
    <div className='p-1  w-[8rem]  text-center bg-gray-50 text-black font-mono shadow-sm text-sm shadow-black'>
      <span className='px-2 align-middle'>{time.hour}</span>:
      <span className='px-2 align-middle'>{time.minute}</span>:
      <span className='px-2 align-middle'>{time.second}</span>
    </div>
  )
}
