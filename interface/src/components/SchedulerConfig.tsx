import type { FormEvent } from 'react'
import { useState } from 'react'
import { useEffect } from 'react'
import { schedulerAPI } from '../APIs/schedulerAPI'
import type { IScheduler } from '../interfaces'
import { Form } from './Form'
import { Input } from './Input'

export function SchedulerConfig() {
  const [scheduler, setScheduler] = useState({} as IScheduler)

  async function fetchScheduler() {
    const data = await schedulerAPI.get()
    setScheduler(data)
  }

  useEffect(() => {
    fetchScheduler()
  }, [])

  function handleSubmit(e: FormEvent<HTMLFormElement>) {
    e.preventDefault()
    schedulerAPI.post(scheduler)
  }

  return (
    <Form
      onSubmit={handleSubmit}
      onClear={() => {
        setScheduler({
          ...scheduler,
          pin: {} as number,
          duration: {} as number,
        })
      }}
      submitButtonContent={'Отправить'}
      clearButtonContent={'Очистить'}
    >
      <Input
        label='Пин'
        id='pin'
        type='number'
        min={0}
        max={255}
        value={scheduler.pin}
        onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
          setScheduler({ ...scheduler, pin: e.target.valueAsNumber })
        }}
      />
      <Input
        label='Длительность'
        id='duration'
        type='number'
        min={1}
        value={scheduler.duration}
        onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
          setScheduler({ ...scheduler, duration: e.target.valueAsNumber })
        }}
      />
    </Form>
  )
}
