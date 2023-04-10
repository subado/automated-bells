import type { InputHTMLAttributes } from 'react'

interface InputProps extends InputHTMLAttributes<HTMLInputElement> {
  label: string
  id: string
}

export function Input({ label, id, ...rest }: InputProps) {
  rest = {
    ...rest,
    className: `p-2 rounded tracking-wide placeholder:italic placeholder:text-slate-400 w-full border-2 bg-gray-100 font-semibold text-center ${
      rest.className || ''
    }`,
    placeholder: label,
    name: id,
  }

  return (
    <div className='flex flex-col gap-y-0 w-full'>
      <label className='text-slate-600 text-[115%] text-left' htmlFor={id}>
        {label}
      </label>
      <input id={id} {...rest} />
    </div>
  )
}
