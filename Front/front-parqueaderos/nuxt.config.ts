// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  devtools: { enabled: true },
  modules:['@nuxtjs/google-fonts'],
  googleFonts:{
    families:{
      Gabarito:[400,900]
    },
    display:'swap'
  },
  app: {
    pageTransition: { name: 'page', mode: 'out-in' }
  },
  runtimeConfig:{
    public:{
      API_URL: process.env.API_URL || 'http://localhost:3000'
    }
  }
})

