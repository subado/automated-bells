import { useState } from 'react'
import type { IChildrenProps } from '../interfaces'

interface IButtonProps extends IChildrenProps {
  color: keyof typeof Colors
  type?: React.ButtonHTMLAttributes<HTMLButtonElement>['type']
  className?: string
  text?: string
  onClick?: React.MouseEventHandler<HTMLButtonElement> | undefined
}

const Colors = {
  green: 'bg-green-500',
  blue: 'bg-blue-500 ',
  red: 'bg-red-500',
  orange: 'bg-orange-500',
  emerald: 'bg-emerald-500',
  rose: 'bg-rose-500',
  gray: 'bg-gray-500',
  lightGray: 'bg-gray-100',
}

export function Button({
  color,
  type,
  className,
  text,
  onClick,
  children,
}: IButtonProps) {
  const ClickColor: typeof Colors = {
    green: 'shadow-green-500 bg-green-700',
    blue: 'shadow-blue-500 bg-blue-700',
    red: 'shadow-red-500 bg-red-700',
    orange: 'shadow-orange-500 bg-orange-700',
    emerald: 'shadow-emerald-500 bg-emerald-700',
    rose: 'shadow-rose-500 bg-rose-700',
    gray: 'shadow-gray-500 bg-gray-700',
    lightGray: 'shadow-black bg-gray-50',
  }
  const [clickEffect, setClickEffect] = useState(false)
  function handleClick(e: React.MouseEvent<HTMLButtonElement>) {
    setClickEffect(true)
    onClick?.(e)
  }

  return (
    <button
      type={type || 'button'}
      className={`${!clickEffect && Colors[color]}
         font-bold rounded ${text || 'text-white'} ${className}
        ${clickEffect && `animate-click shadow ${ClickColor[color]}`}`}
      onClick={handleClick}
      onAnimationEnd={() => setClickEffect(false)}
    >
      {children}
    </button>
  )
}
