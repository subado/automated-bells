import { isRouteErrorResponse, useRouteError } from 'react-router-dom'

export function ErrorPage() {
  const error = useRouteError()

  if (isRouteErrorResponse(error)) {
    return (
      <div className='h-screen flex flex-col items-center justify-center w-[100%] gap-y-5'>
        <h1 className='font-black text-[4vmin]'>Oops! {error.status}</h1>
        <p className='text-[3vmin]'>{error.statusText}</p>
        {error.data?.message && (
          <p className='italic text-gray-500 text-[2vmin]'>
            {error.data.message}
          </p>
        )}
      </div>
    )
  } else if (error instanceof Error) {
    return (
      <div className='h-screen flex flex-col items-center justify-center w-[100%] gap-y-5'>
        <h1 className='font-black text-[4vmin]'>Oops! Unexpected Error</h1>
        <p className='text-[3vmin]'>Something went wrong.</p>
        <p className='italic text-gray-500 text-[2vmin]'>{error.message}</p>
      </div>
    )
  } else {
    return <></>
  }
}
