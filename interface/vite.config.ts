import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  server: {
    proxy: {
      '/api': 'http://192.168.0.177',
    },
  },
  plugins: [
    react({
      babel: {
        babelrc: true,
      },
    }),
  ],
})
