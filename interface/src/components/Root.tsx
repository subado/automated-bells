import { useState } from 'react'
import { Outlet } from 'react-router-dom'
import { MenuOpenContext } from '../contexts/MenuOpenContext'
import { SchedulerTitleProvider } from '../contexts/SchedulerTitleContext'
import { Header } from './Header/Header'
import { Menu } from './Menu/Menu'

export function Root() {
  const [isMenuOpen, setMenuOpen] = useState(false)

  if (isMenuOpen) {
    document.body.style.overflow = 'hidden'
  } else {
    document.body.style.overflow = ''
  }

  return (
    <>
      <MenuOpenContext.Provider value={[isMenuOpen, setMenuOpen]}>
        {isMenuOpen && <Menu />}
      </MenuOpenContext.Provider>

      <SchedulerTitleProvider>
        <MenuOpenContext.Provider value={[isMenuOpen, setMenuOpen]}>
          <Header />
        </MenuOpenContext.Provider>
        <main className='w-full md:w-[720px] m-auto flex flex-col gap-y-5 md:text-xl'>
          <Outlet />
        </main>
      </SchedulerTitleProvider>
    </>
  )
}
