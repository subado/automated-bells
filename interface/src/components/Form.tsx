import React from 'react'
import type { PropsWithChildren } from 'react'
import { Button } from './Button'
interface IFormProps extends PropsWithChildren {
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

      <div className='flex flex-wrap flex-row gap-x-2 w-full justify-center gap-y-2'>
        <Button color='orange' className='py-2 px-7 text-white' type='submit'>
          {submitButtonContent}
        </Button>
        <Button color='sky' className='py-2 px-7 text-white' onClick={onClear}>
          {clearButtonContent}
        </Button>
      </div>
    </form>
  )
}
