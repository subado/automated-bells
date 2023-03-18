import { Route, Routes } from 'react-router-dom'
import { Root } from './components/Root'
import { TableEditor } from './components/TableEditor'

function App() {
  return (
    <div className='flex flex-col items-center'>
      <Routes>
        <Route path='/' element={<Root />} />
        <Route path='/table/:title' element={<TableEditor />} />
      </Routes>
    </div>
  )
}

export default App
