<template>
<div class="dashboard-container">
  <h3> Gestión del parqueadero</h3>
  <p>Estado del parqueadero:</p>
  <table>
      <th>#Parqueadero</th>
      <th>Estado;</th>
      <th></th>
    <tbody>
    <tr>
      <td>Parqueadero #1</td>
      <td>Disponible</td>
      <td><button @click="managePositions(0)" :class="{'closed': ledStates[0] === 'Reserved'}">{{ledStates[0] === 'Reserved'? 'Librerar' : 'Reservar'}}</button></td>
    </tr>
    <tr>
      <td>Parqueadero #2</td>
      <td>Disponible</td>
      <td><button @click="managePositions(2)" :class="{'closed': ledStates[2] === 'Reserved'}">{{ledStates[2] === 'Reserved'? 'Librerar' : 'Reservar'}}</button></td>
    </tr>
    <tr>
      <td>Parqueadero #3</td>
      <td>Disponible</td>
      <td><button @click="managePositions(1)" :class="{'closed': ledStates[1] === 'Reserved'}">{{ledStates[1] === 'Reserved'? 'Librerar' : 'Reservar'}}</button></td>
    </tr>
    </tbody>
  </table>
  <h3> Gestion manual</h3>
  <p>apertura de talanqueras</p>
  <div class="row">
      <button @click="manageServos(0)" :class="{'closed': actions[0] == 'Cerrar'}">{{actions[0]}} talanquera de entrada</button>
      <button @click="manageServos(1)" :class="{'closed': actions[1] == 'Cerrar'}">{{actions[1]}} talanquera de salida</button>
  </div>
  <p v-for="data in servoStates">{{data}}</p>
  <nuxt-link to="/"> Volver </nuxt-link>
</div>
</template>

<script setup lang="ts">

definePageMeta({
  pageTransition: {
    name: 'rotate'
  }
})

const config = useRuntimeConfig()
const servoStates = ref(["close","close"])
const actions = ref(["Abrir","Abrir"])
const ledStates = ref(["Free", "Free", "Free"])

function managePositions(id: number):void {
  let currentState = ledStates.value[id];

  if(currentState === "Free") {
    makeReservation(id);
    ledStates.value[id] = "Reserved";
  } else {
    freeReservation(id);
    ledStates.value[id] = "Free";
  }
}


function makeReservation(id: number):void  {
  useFetch(config.public.API_URL +"RP"+id,
      {
        method: "POST"
      })
}

function freeReservation(id: number):void {
  useFetch(config.public.API_URL + "FP"+id, {
    method: "POST"
  })
}

function manageServos(id: number):void{
  let currentState = servoStates.value[id]
  if(currentState === "close"){
    openGate(id)
    servoStates.value[id] = "open"
    actions.value[id]="Cerrar"
  }else{
    closeGate(id)
    servoStates.value[id] = "close"
    actions.value[id]="Abrir"
  }
}

async function openGate(id: number): Promise<void> {
  useFetch(config.public.API_URL +"OS"+id,
      {
        method: "POST"
      })
}
async function closeGate(id: number): Promise<void> {
  useFetch(config.public.API_URL +"CS"+id,
      {
        method: "POST"
      })
}


</script>

<style scoped>
.dashboard-container {
  width: 100vw;
  height: 100vh;
  padding: 10px;
}

table {
  border-collapse: collapse;
  width: 95%;
}

td,th {
  border: 1px solid #ddd;
  padding: 8px;
}

h3{
  font-size: 30px;
  margin-bottom: 30px;
}

p{
  padding-bottom: 20px;
}

tr:nth-child(even){background-color: #f2f2f2;}

tr:hover {background-color: #ddd;}

th {
  padding-top: 12px;
  padding-bottom: 12px;
  text-align: left;
  background-color: #04AA6D;
  color: white;
}

.row{
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: space-evenly;
}
.closed{
  background-color: red;
}

</style>