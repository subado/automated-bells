import { api } from '../../constants'
import { Button } from '../Button'
import { MenuItem } from './Item'

export function Menu() {
  function startRing() {
    api.post('ring/', { state: 'high' })
  }
  function stopRing() {
    api.post('ring/', { state: 'low' })
  }

  return (
    <ul className='overflow-auto fixed h-screen w-full md:w-[calc(320px_+_10vw)] z-10 py-8 px-3 bg-white shadow-xl shadow-black text-center text-2xl flex flex-col gap-y-6 tracking-wide'>
      <MenuItem to='/'>Time</MenuItem>
      <MenuItem to='/ntp/'>NTP</MenuItem>
      <MenuItem to='/wifi/'>WiFi</MenuItem>
      <MenuItem to='/scheduler/'>Scheduler</MenuItem>
      <span className='border' />
      <Button
        className='px-1 py-2 font-normal rounded-none text-white'
        color='slate'
        onMouseDown={startRing}
        onMouseUp={stopRing}
        onTouchStart={startRing}
        onTouchEnd={stopRing}
      >
        Ring
      </Button>
      <Button
        className='px-1 py-2 font-normal rounded-none text-white'
        color='darkSky'
        onClick={() => api.post('sync/')}
      >
        Sync
      </Button>
      <Button
        className='px-1 py-2 font-normal rounded-none text-white'
        color='darkRose'
        onClick={() => api.post('reset/')}
      >
        Restart
      </Button>
    </ul>
  )
}
