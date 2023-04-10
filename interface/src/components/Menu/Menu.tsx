import { MenuItem } from './MenuItem'

export function Menu() {
  return (
    <ul className='flex flex-col gap-y-6 absolute h-screen w-1/2 z-10 py-8 px-7 bg-white shadow-xl shadow-black text-center'>
      <MenuItem to='/'>Time</MenuItem>
      <MenuItem to='/ntp/'>NTP</MenuItem>
      <MenuItem to='/wifi/'>WiFi</MenuItem>
    </ul>
  )
}
