import { useState } from 'react'
import type { IChildrenProps } from '../interfaces'

interface IButtonProps extends IChildrenProps {
  color: keyof typeof Colors
  type?: React.ButtonHTMLAttributes<HTMLButtonElement>['type']
  className?: string
  onClick?: React.MouseEventHandler<HTMLButtonElement> | undefined
}

const Colors = {
  green: 'bg-green-500',
  blue: 'bg-blue-500 ',
  red: 'bg-red-500',
  orange: 'bg-orange-500',
  emerald: 'bg-emerald-500',
  rose: 'bg-rose-500',
}

export function Button({
  color,
  type,
  onClick,
  className,
  children,
}: IButtonProps) {
  const ClickColor: typeof Colors = {
    green: 'shadow-green-500 bg-green-700',
    blue: 'shadow-blue-500 bg-blue-700',
    red: 'shadow-red-500 bg-red-700',
    orange: 'shadow-orange-500 bg-orange-700',
    emerald: 'shadow-emerald-500 bg-emerald-700',
    rose: 'shadow-rose-500 bg-rose-700',
  }
  const [effect, setEffect] = useState(false)
  function handleClick(e: React.MouseEvent<HTMLButtonElement>) {
    setEffect(true)
    onClick?.(e)
  }

  return (
    <button
      type={type || 'button'}
      className={`${Colors[color]}
        ${className} font-bold rounded text-white
        ${effect && `animate-click shadow ${ClickColor[color]}`}`}
      onClick={handleClick}
      onAnimationEnd={() => setEffect(false)}
    >
      {children}
    </button>
  )
}
