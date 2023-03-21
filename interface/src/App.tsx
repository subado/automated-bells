import { Route, Routes } from 'react-router-dom'
import { Root } from './components/Root'
import { TableEditor } from './components/TableEditor'

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
