import { Route, Routes } from 'react-router-dom'
import { Root } from './components/Root'

function App() {
  return (
    <div className='flex flex-col items-center text-[4vmin]'>
      <Routes>
        <Route path='/' element={<Root />} />
      </Routes>
    </div>
  )
}

export default App
