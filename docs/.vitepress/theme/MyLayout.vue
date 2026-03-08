// .vitepress/theme/MyLayout.vue
<script setup>
import DefaultTheme from 'vitepress/theme'
const { Layout } = DefaultTheme
</script>

<template>
  <Layout>
    <template #aside-bottom>
      <div class="custom-aside">
        <h1>AI Usage Disclaimer</h1>
        <p>I have used claude to paraphrase.</p>
      </div>
    </template>
  </Layout>
</template>

<style scoped>
.custom-aside {
  margin-top: 1rem;
  padding: 1rem;
  border-top: 1px solid var(--vp-c-divider);
  font-size: 14px;
}
</style>