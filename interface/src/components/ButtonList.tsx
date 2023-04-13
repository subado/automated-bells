import type { ReactElement } from 'react'
import React from 'react'
import type { IButtonProps } from './Button'

interface IButtonListProps {
  children: Array<ReactElement<IButtonProps>>
  buttonClassName?: string
}

export function ButtonList({ children, buttonClassName }: IButtonListProps) {
  children = React.Children.map(children, (child) =>
    React.cloneElement(child, {
      className: `${child.props.className} ${buttonClassName} w-fit`,
    })
  )

  return (
    <div className='flex flex-wrap flex-row gap-x-2 w-full justify-center gap-y-2'>
      {children}
    </div>
  )
}
