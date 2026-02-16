//@ts-ignore
import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "The Bliss Platform",
  description: "This is the documentation and specification for The Bliss Platform",
  base: '/bliss-4i/',

  head: [
    ['link', { rel: 'icon', href: '/bliss-4i/favicon.ico' }]
  ],

  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Articles', link: '/articles/' },
      { text: 'Packager', link: '/packager/' },
      { text: 'Language', link: '/language/' }
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
      ],

      '/packager/': [
        {
          text: 'Packager',
          items: [
            { text: "Packager Specification", link: '/packager/specification.md' }
          ]
        }
      ],

      '/language/': [
        {
          text: 'Language',
          items: [
            { text: "Data and Action Oriented Programming", link: '/language/DAOP.md' }
          ]
        }
      ]
    },

    socialLinks: [
      { icon: 'github', link: 'https://github.com/bliss-platform/bliss-4i' },
      { icon: 'linkedin', link: 'https://www.linkedin.com/company/bliss-org' }
    ]
  }
})
