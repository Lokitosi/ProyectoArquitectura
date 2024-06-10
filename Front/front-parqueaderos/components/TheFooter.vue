<template>
  <footer class="footer">
    <div class="container">
      <p> &copy; {{ getCurrentYear }} ParkingApp</p>
    </div>
  </footer>
</template>

<script>
export default {
  computed: {
    getCurrentYear() {
      return new Date().getFullYear();
    }
  }
};
</script>

<style scoped>
.footer {
  align-self: flex-end;
  width: 100%;
  background-color: #333;
  color: white;
  padding: 1rem 0;
  text-align: center;
}

.container {
  max-width: 960px;
  margin: 0 auto;
}
</style>