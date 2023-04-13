import React from 'react'
import type { IChildrenProps } from '../interfaces'
import { Button } from './Button'
import { ButtonList } from './ButtonList'

interface IFormProps extends IChildrenProps {
  onSubmit: React.FormEventHandler<HTMLFormElement>
  onClear: React.MouseEventHandler<HTMLButtonElement>
  submitButtonContent: string
  clearButtonContent: string
}

export function Form({
  children,
  onSubmit,
  onClear,
  submitButtonContent,
  clearButtonContent,
}: IFormProps) {
  return (
    <form
      className='flex flex-col items-center gap-y-3 px-2'
      onSubmit={onSubmit}
    >
      {children}
      <ButtonList buttonClassName='p-2 text-white'>
        <Button color='orange' type='submit'>
          {submitButtonContent}
        </Button>
        <Button color='sky' onClick={onClear}>
          {clearButtonContent}
        </Button>
      </ButtonList>
    </form>
  )
}
