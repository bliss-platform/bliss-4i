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

    search: {
      provider: 'local'
    },

    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Articles', link: '/articles/' },
      { text: 'Packager', link: '/packager/' },
      { text: 'Language', link: '/language/' }
    ],

    //@ts-ignore
    sidebar: {
      '/articles/': [
        {
          text: 'Articles',
          items: [
            { text: "CLI Convention", link: '/articles/cli-convention.md' },
            { text: "LOG Convention", link: '/articles/log-convention.md' },
            { text: "Data and Action Oriented Programming", link: '/articles/DAOP.md' }
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
          items: [
            { text: "Introduction", link: '/language/index.md' },
            { text: "Project Structure", link: '/language/project_structure.md' },
            { text: "Core Concepts", link: '/language/core_concepts.md', items: [
                { text: "Expressions and Statements", link: '/language/core_concepts/expression_and_statements.md' },
                { text: "Data Types", link: '/language/core_concepts/data_types.md' }
            ]},
            { text: "Language Reference", link: '/language/language_reference.md', items: [
                { text: "Variables", link: '/language/language_reference/variables.md' },
                { text: "Functions", link: '/language/language_reference/functions.md' },
                { text: "Directives", link: '/language/language_reference/directives.md' },
                { text: "Control Flow", link: '/language/language_reference/control_flow.md' },
                { text: "Data", link: '/language/language_reference/data.md' },
            ]},
            { text: "Module System", link: '/language/module_system.md', items: [
                { text: "External Packages", link: '/language/module_system/external_packages.md' },
                { text: "Internal References", link: '/language/module_system/internal_references.md' } 
            ]},
            {text: "Summary", link: '/language/summary.md'}
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
