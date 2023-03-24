interface IErrorProps {
  header: string
  description: string
  message: string
}

export function ErrorPage({ header, description, message }: IErrorProps) {
  return (
    <div className='h-screen flex flex-col items-center justify-center w-[100%] gap-y-5'>
      <h1 className='font-black text-[4vmin]'>Oops! {header}</h1>
      <p className='text-[3vmin]'>{description}</p>
      <p className='italic text-gray-500 text-[2vmin]'>{message}</p>
    </div>
  )
}
