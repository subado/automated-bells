import { isRouteErrorResponse, useRouteError } from 'react-router-dom'
import { ErrorPage } from './ErrorPage'

export function ErrorScreen() {
  const error = useRouteError()

  if (isRouteErrorResponse(error)) {
    return (
      <ErrorPage
        header={`${error.status}`}
        description={error.statusText}
        message={error.data.message}
      />
    )
  } else if (error instanceof Error) {
    return (
      <ErrorPage
        header={'Unexpected Error'}
        description={'Something went wrong.'}
        message={error.message}
      />
    )
  } else {
    return <></>
  }
}
