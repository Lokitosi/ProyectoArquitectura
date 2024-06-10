<template>
  <div class="container">
    <h1 class="slide-right">ParkingApp</h1>
    <p class="slide-left">La mejor manera de ver el estado de su parqueadero y controlarlo</p>
    <img src="../assets/img/parqueadero.png" alt="img parqueadero" />
    <nuxt-link to="/Dashboard/adminDashboard" class="slide-right">Ver estado del parqueadero</nuxt-link>
  </div>
</template>

<script setup lang="ts">

</script>

<style scoped>
.container{
  margin: 20px;
  display: flex;
  flex-direction: column;
}
h1{
  font-size: 70px;
  text-align: center;
}

img{
  margin: 30px 0;
  border-radius: 10px;
}

p{
  padding-top: 20px;
}



@media only screen and (min-width: 768px) {
  img{
    width: 500px;
    height: auto;
    align-self: center;
  }

}
</style>