import type { InputHTMLAttributes } from 'react'

interface InputProps extends InputHTMLAttributes<HTMLInputElement> {
  label: string
  id: string
}

export function Input({ label, id, ...rest }: InputProps) {
  rest = {
    ...rest,
    className: `p-2 tracking-wide placeholder:italic placeholder:text-slate-400 w-full border-2 bg-gray-100 font-bold text-center ${
      rest.className || ''
    }`,
    placeholder: label,
    name: id,
  }

  return (
    <div className='inline-flex flex-row gap-x-2 items-center w-full'>
      <label className='font-semibold text-center w-1/5' htmlFor={id}>
        {label}
      </label>
      <input id={id} {...rest} />
    </div>
  )
}
