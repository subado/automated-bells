import type { ButtonHTMLAttributes } from 'react'
import { useState } from 'react'

export interface IButtonProps extends ButtonHTMLAttributes<HTMLButtonElement> {
  color: keyof typeof Colors
  isAnimated?: boolean
}

const Colors = {
  green: 'bg-green-500',
  blue: 'bg-blue-500 ',
  red: 'bg-red-500',
  orange: 'bg-orange-500',
  emerald: 'bg-emerald-500',
  rose: 'bg-rose-500',
  darkRose: 'bg-rose-700',
  gray: 'bg-gray-500',
  lightGray: 'bg-gray-100',
  sky: 'bg-sky-500',
  darkSky: 'bg-sky-700',
  pink: 'bg-pink-500',
  slate: 'bg-slate-500',
}

export function Button({
  color,
  isAnimated = true,
  children,
  ...rest
}: IButtonProps) {
  const ClickColor: typeof Colors = {
    green: 'shadow-green-500 bg-green-700',
    blue: 'shadow-blue-500 bg-blue-700',
    red: 'shadow-red-500 bg-red-700',
    orange: 'shadow-orange-500 bg-orange-700',
    emerald: 'shadow-emerald-500 bg-emerald-700',
    rose: 'shadow-rose-500 bg-rose-700',
    darkRose: 'shadow-rose-700 bg-rose-900',
    gray: 'shadow-gray-500 bg-gray-700',
    lightGray: 'shadow-black bg-gray-50',
    sky: 'shadow-sky-500 bg-sky-700',
    darkSky: 'shadow-sky-700 bg-sky-900',
    pink: 'shadow-pink-500 bg-pink-700',
    slate: 'shadow-slate-500 bg-slate-700',
  }

  const [isActive, setActive] = useState(false)

  rest = {
    ...rest,
    className: `${(!isActive || !isAnimated) && Colors[color]}
         font-bold rounded ${rest.className}
        ${
          isAnimated && isActive && ` animate-click shadow ${ClickColor[color]}`
        }`,
    type: rest.type || 'button',
  }

  if (rest.onClick != undefined) {
    const handleClick = rest.onClick
    rest.onClick = (e: React.MouseEvent<HTMLButtonElement>) => {
      setActive(true)
      handleClick?.(e)
    }
    rest.onAnimationEnd = () => setActive(false)
  } else if (rest.onMouseDown != undefined && rest.onMouseUp) {
    const handleDown = rest.onMouseDown
    rest.onMouseDown = (e: React.MouseEvent<HTMLButtonElement>) => {
      setActive(true)
      handleDown?.(e)
    }
    const handleUp = rest.onMouseUp
    rest.onMouseUp = (e: React.MouseEvent<HTMLButtonElement>) => {
      setActive(false)
      handleUp?.(e)
    }
  }
  return <button {...rest}>{children}</button>
}
