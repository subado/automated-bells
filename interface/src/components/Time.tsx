import { useState, useEffect } from 'react'
import { timeAPI } from '../APIs/timeAPI'
import type { ITime } from '../interfaces'

export function Time() {
  const initialState = {
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
    <p className='p-1  w-[8rem]  text-center m-auto bg-black text-white font-mono shadow-sm shadow-black'>
      <span className='px-2 align-middle'>{time.hour}</span>:
      <span className='px-2 align-middle'>{time.minute}</span>:
      <span className='px-2 align-middle'>{time.second}</span>
    </p>
  )
}
