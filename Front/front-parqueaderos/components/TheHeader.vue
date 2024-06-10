<template>
  <header>
    <nav>
      <ul>
        <li><NuxtLink to="/"><h3>ParkingApp</h3></NuxtLink></li>
        <li><NuxtLink to="/Dashboard/adminDashboard">Gestión</NuxtLink></li>
      </ul>
    </nav>
  </header>
</template>

<script>
</script>

<style scoped>
header {
  background: #53a08e;
  padding: 1rem;
  color: white;
}
nav ul {
  list-style: none;
  padding: 0;
  display: flex;
  justify-content: flex-end;
}
nav ul li {
  margin-left: 1rem;
}
nav ul li:first-child {
  margin-left: 0;
  margin-right: auto;
  text-align: left;

}

nav ul li a {
  color: white;
  text-decoration: none;
}

h3{
  font-family: 'gabarito';
  font-weight: 800;
}
</style>
