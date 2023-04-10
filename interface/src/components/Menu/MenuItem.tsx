import { NavLink } from 'react-router-dom'
import { useMenuOpen } from '../../contexts/MenuOpenContext'
import type { IChildrenProps } from '../../interfaces'

interface IMenuItemProps extends IChildrenProps {
  to: string
}

export function MenuItem({ to, children }: IMenuItemProps) {
  const [, setMenuOpen] = useMenuOpen()

  return (
    <NavLink
      className={({ isActive }) =>
        'w-full ' + (isActive ? 'border-b-4 border-sky-700' : '')
      }
      to={to}
      onClick={() => {
        setMenuOpen(false)
      }}
    >
      {children}
    </NavLink>
  )
}
