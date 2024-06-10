<template>
  <div class="app">
    <TheHeader/>
    <NuxtPage class="page" />
    <TheFooter/>
  </div>
</template>


<script setup lang="ts">
import TheHeader from "~/components/TheHeader.vue";
import TheFooter from "~/components/TheFooter.vue";

</script>

<style>
*{
  margin: 0;
  font-family: 'gabarito';
  font-weight: 400;
}

.app{
  display: flex;
  flex-direction: column;
  height: 100vh;
}
.page{
  flex: 1;
}
a , button{
  border: 1px solid #a9cba6;
  padding: 10px;
  border-radius: 5px;
  color: white;
  background-color: #a9cba6;
  width: fit-content;
  align-self: center;
  text-decoration: none;
}

.page-enter-active,
.page-leave-active {
  transition: all 0.4s;
}
.page-enter-from,
.page-leave-to {
  opacity: 0;
  filter: blur(1rem);
}
.slide-right {
  animation: 3s slide-right;
}
@keyframes slide-right {
  from {
    margin-left: -100%;
  }
  to {
    margin-left: 0%;
  }
}

.slide-left {
  animation: 3s slide-left;
}
@keyframes slide-left {
  from {
    margin-left: 100%;
  }
  to {
    margin-left: 0%;
  }
}
</style>