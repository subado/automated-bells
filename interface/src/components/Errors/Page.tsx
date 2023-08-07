interface IErrorProps {
  header: string
  description: string
  message: string
}

export function ErrorPage({ header, description, message }: IErrorProps) {
  return (
    <div className='h-screen flex flex-col items-center justify-center w-full gap-y-5'>
      <h1 className='font-black'>Oops! {header}</h1>
      <p>{description}</p>
      <p className='italic text-gray-500'>{message}</p>
    </div>
  )
}
