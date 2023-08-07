import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { createBrowserRouter, RouterProvider } from 'react-router-dom'
import { ErrorScreen } from './components/Errors/Screen'
import { Ntp } from './components/Ntp'
import { Root } from './components/Root'
import { SchedulerConfig } from './components/SchedulerConfig'
import { TimeTables } from './components/TimeTables'
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
      {
        path: '/scheduler',
        element: <SchedulerConfig />,
      },
    ],
  },
])

const container = document.getElementById('root')
const root = createRoot(container!)
root.render(
  <StrictMode>
    <RouterProvider router={router} />
  </StrictMode>
)
