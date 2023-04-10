import ReactDOM from 'react-dom/client'
import { createBrowserRouter, RouterProvider } from 'react-router-dom'
import { ErrorScreen } from './components/Errors/ErrorScreen'
import { Ntp } from './components/Ntp'
import { Root } from './components/Root'
import { TimeTables } from './components/TimeTables/TimeTables'
import { WiFi } from './components/WiFi'
import './index.css'

const router = createBrowserRouter([
  {
    path: '/',
    element: <Root />,
    errorElement: <ErrorScreen />,
    children: [
      {
        path: '/',
        element: <TimeTables />,
      },
      {
        path: '/ntp',
        element: <Ntp />,
      },
      {
        path: '/wifi',
        element: <WiFi />,
      },
    ],
  },
])

ReactDOM.createRoot(document.getElementById('root') as HTMLElement).render(
  <RouterProvider router={router} />
)
