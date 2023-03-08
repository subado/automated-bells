import React from 'react'

fetch('http://192.168.0.177/tables', {
  method: 'GET',
})
  .then((req) => {
    return req.json()
  })
  .then((data) => {
    console.log(data)
  })

function App() {
  return <div className='container mx-auto pt-5 max-w-2xl'></div>
}

export default App
