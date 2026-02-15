//@ts-ignore
import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "The Bliss Platform",
  description: "This is the documentation and specification for The Bliss Platform",
  base: '/bliss-4i/',
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Articles', link: '/articles/' }
    ],

    sidebar: {
      '/articles/': [
        {
          text: 'Articles',
          items: [
            { text: "CLI Convention", link: '/articles/cli-convention.md' },
            { text: "LOG Convention", link: '/articles/log-convention.md' }
          ]
        }
      ]
    },

    socialLinks: [
      { icon: 'github', link: 'https://github.com/vuejs/vitepress' }
    ]
  }
})
