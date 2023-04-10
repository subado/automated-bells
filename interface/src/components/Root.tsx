import { useState } from 'react'
import { Outlet } from 'react-router-dom'
import { MenuOpenContext } from '../contexts/MenuOpenContext'
import { SchedulerProvider } from '../contexts/SchedulerContext'
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

      <SchedulerProvider>
        <MenuOpenContext.Provider value={[isMenuOpen, setMenuOpen]}>
          <Header />
        </MenuOpenContext.Provider>
        <main className='items-center'>
          <Outlet />
        </main>
      </SchedulerProvider>
    </>
  )
}
