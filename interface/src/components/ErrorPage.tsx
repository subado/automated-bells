import { isRouteErrorResponse, useRouteError } from 'react-router-dom'

export function ErrorPage() {
  const error = useRouteError()

  if (isRouteErrorResponse(error)) {
    return (
      <div className='h-screen flex flex-col text-[10vmin] items-center justify-center w-[100%] font-black'>
        <h1>Oops! {error.status}</h1>
        <p>{error.statusText}</p>
        {error.data?.message && (
          <p>
            <i>{error.data.message}</i>
          </p>
        )}
      </div>
    )
  } else if (error instanceof Error) {
    return (
      <div className='h-screen flex flex-col text-[10vmin] items-center justify-center w-[100%] font-black'>
        <h1>Oops! Unexpected Error</h1>
        <p>Something went wrong.</p>
        <p>
          <i>{error.message}</i>
        </p>
      </div>
    )
  } else {
    return <></>
  }
}
