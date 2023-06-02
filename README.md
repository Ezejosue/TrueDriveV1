# TrueDriveV1

Una aplicación de gestión de taxis para una empresa de transporte.

## Descripción

Esta aplicación permite gestionar la flota de taxis de una empresa de transporte, incluyendo la adición de nuevos taxis y conductores, la asignación de taxis a clientes, el seguimiento de los taxis en ruta y la reasignación de taxis a la lista de espera después de completar un recorrido. La aplicación también permite a los clientes solicitar taxis especificando la categoría necesaria (Ejecutiva o Tradicional), el punto de salida, el destino y el costo del viaje.

## Requisitos del sistema

- C++11 o superior.
- Compilador compatible con C++11.
- Sistema operativo compatible con la biblioteca estándar de C++.

## Características

- Registro de taxis con información detallada (placa, número de motor, modelo, año, etc.).
- Registro de conductores con información personal (nombre, apellido, número de identificación, seguro social, etc.).
- Categorización de taxis como ejecutivos o tradicionales.
- Validación de año mínimo para la asignación de categorías.
- Solicitud de viaje por parte del cliente.
- Asignación de taxis disponibles a los clientes según la categoría solicitada.
- Registro de viajes finalizados o cancelados, con detalles del taxi, conductor, cliente, punto de salida, destino y costo.
- Almacenamiento de los datos en archivos de texto para persistencia.

## Tecnologías utilizadas

- C++

## Instrucciones de instalación y ejecución

1. Clona o descarga el repositorio en tu máquina local.
2. Abre el proyecto en tu entorno de desarrollo de C++.
3. Compila el código fuente.
4. Ejecuta el programa resultante.

## Uso del programa

1. Al iniciar el programa, se mostrará un menú principal con las siguientes opciones:
   - Agregar conductor: Permite agregar un nuevo conductor al sistema.
   - Agregar taxi: Permite agregar un nuevo taxi al sistema.
   - Ver taxis disponibles: Muestra la lista de taxis disponibles en espera.
   - Ver taxis en ruta: Muestra la lista de taxis asignados a clientes.
   - Solicitar taxi: Permite solicitar un taxi ingresando los detalles del viaje.
   - Finalizar viaje: Permite finalizar un viaje registrado previamente.
   - Cancelar viaje: Permite cancelar un viaje registrado previamente.
   - Salir: Cierra el programa.

2. Sigue las instrucciones en pantalla para interactuar con el programa y utilizar las diferentes funcionalidades.

3. Los datos de los taxis, conductores y viajes se almacenarán en archivos de texto (`taxis.txt`, `conductores.txt` y `viajes.txt`) para que puedan ser cargados nuevamente en futuras ejecuciones del programa.


## Contribución

Este proyecto ha sido creado como parte de un ejercicio práctico, pero si deseas contribuir, puedes hacerlo a través de un fork del repositorio y una solicitud de extracción (pull request) con tus cambios.

## Licencia

Este proyecto está bajo la Licencia MIT - consulta el archivo [LICENSE.md](LICENSE.md) para obtener más detalles.
 
