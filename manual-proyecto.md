# Manual de Proyecto

### Enunciado
El proyecto consiste en realizar un remake del [Wolfenstein 3D  (1992)](https://es.wikipedia.org/wiki/Wolfenstein_3D). Será un juego multijugador, donde cada jugador será William B.J. Blazkowicz y verá al resto de los jugadores como oficiales Nazis.

El enunciado completo se puede encontrar [acá](enunciado.pdf).

### Evolución del proyecto

#### Cronograma propuesto

* **Semana 1**  
  * Carga de mapas, lógica de movimiento de los personajes (colisión con las paredes y otros objetos).   
  * Mostrar una imagen y una animación. Reproducir sonidos y música. Mostrar texto en pantalla.  
  * Ecuación de los rayos (donde intersecciona con cada celda)  
  * Draft del editor.
* **Semana 2**  
  * Lógica de las partidas.Lógica del ataque.
  * Modulo IA basico.
  * Vista 3D las paredes usando ray casting. Sin texturas ni objetos ni otros jugadores
  * Editor basico
* **Semana 3**  
  * Sistema de comunicación (cliente - servidor)
  * Modulo IA completo.
  * Vista 3D incluyendo las texturas de las paredes, objetos y jugadores.
  * Editor completo.
* **Semana 4**  
  * Servidor completo.
  * Configuración.
  * Cliente completo. Pantalla de login y de partidas.
* **Semana 5**  
  * Pruebas y corrección sobre estabilidad del servidor.
  * Detalles finales y documentación preliminar
  * Pruebas y corrección sobre estabilidad del cliente.
  * Detalles finales y documentación preliminar
  * Pruebas y corrección sobre estabilidad del cliente.
  * Detalles finales y documentación preliminar
* **Semana 6**  
  * Correcciones sobre
  * Testing y corrección de bugs
  * Documentación
* **Semana 7**  
  * Testing
  * Documentación
  * Armado del entregable

#### Cronograma real
Tratamos de seguir el cronograma propuesto pero hubo varios defasajes por complicaciones (como las mencionadas en la  próxima sección). Tampoco hicimos un seguimiento de la evolución semana por semana.

### Inconvenientes encontrados  
* Algunos de los inconvenientes encontrados estuvieron relacionados con la parte gráfica del juego. Por ejemplo, con el algoritmo de raycasting, cuyo desarrollo debió modificarse mas vez debido a problemas con los tipos de datos elegidos para su desarrollo. Ademas, al momento de renderizar a los sprites, también hubo inconvenientes con parámetros que estaban por fuera del rango de la pantalla del juego, con lo cual no podia verse en pantalla las entidades que debían. A esto se le debe agregar el tiempo de cpu que toma renderizar el mapa y todos sus contenidos, el cual es alto y produce una desincronizacion entre el procesado de comandos del lado del servidor y el procesado de actualizaciones del lado del cliente.  

* Por otro lado, se hallaron dificultades a la hora de serializar y deserializar las distintas entidades del juego. Al ser un protocolo binario, había que tener un especial cuidado a la hora de desarrollarlo. Su desarrollo se encuentra en las siguientes secciones. Ademas, se debió tener en cuenta que las computadoras que corren el juego pueden tener distinto endianness.  

* Además, algunos de los inconvenientes encontrados están relacionados con los propios problemas de concurrencia. Por ejemplo, cuando se deben recibir comandos de parte del servidor, estos provienen de distintos hilos, habiendo uno por cliente conectado en la partida. Estos comandos se guardan en una cola, pero esta esta protegida de las race conditions.  

* Otro de los inconvenientes hallados es el del renderizado de los enemigos, los cuales siempre se renderizan de frente a pesar de que pueden estar de espaldas nosotros, por ejemplo, y lo veriamos de frente. Esto se debe a que, como el juego original no estaba intencionado para funcionar en linea, con cliente/servidor, los enemigos siempre se ven enfrentados a nosotros ya que vendrian directo a atacarnos.  

### Análisis de puntos pendientes
* No hubo tiempo suficiente para hacer tests sobre el código realizado.

### Herramientas
Las herramientas utilizadas para este proyecto fueron las siguientes:

* **[Git](https://git-scm.com/):** se utilizó para el control de versiones y el alojamiento del código. 

* **[SDL2](https://www.libsdl.org/download-2.0.php):** fue usado para la parte gráfica del cliente del juego.

* **[qt](https://www.qt.io/):** fue usado para la parte gráfica del editor de mapas. 

* **[LUA](http://www.lua.org/):** fue el lenguaje utilizado para programar los enemigos controlados por la computadora. 

* **[CMake](https://cmake.org/):** utilizado para compilar el proyecto. 

* **[CPack](https://cmake.org/cmake/help/latest/module/CPack.html):** con cpack pudimos generar el instalador.

* **[GDB](https://www.gnu.org/software/gdb/):** fue utilizado para debuggear el código.

* **[Valgrind](valgrind.org):** sirvió para encontrar problemas, en particular utilizamos [kcachegrind](https://kcachegrind.github.io/html/Home.html) y [memcheck](https://valgrind.org/docs/manual/mc-manual.html)

* **[PlantUML](https://plantuml.com/es/):** para realizar los diagramas UML de la documentación

* **[CLion](https://www.jetbrains.com/clion/):** fue utilizado como IDE para desarrollar y para debuggear también

* **[Atom](https://atom.io/):** fue utilizado para escribir el código y la documentación

### Conclusiones
Este proyecto nos permitió trabajar en equipo, con todo lo que eso implica. Pudimos coordinar, planificar y hacer sesiones de desarrollo conjunto (pair-programming).

Además, al ser un proyecto tan grande, fue indispensable organizarse y dividir tareas de forma clara para evitar el retrabajo. 

El hecho de que el cuatrimestre haya sido virtual e interrumpido en la mitad, creo que trajo varias complicaciones. Por ejemplo, coordinar las distintas disponibilidades de tiempo para realizar videollamadas (y tener conexión estable de internet). Además, la interrupción del cuatrimestre hizo que se pierda el foco, y retomar fue complicado, a diferencia de si hubiesee sido todo continuo.

Algo positivo es que hubo mucha comunicación entre el equipo, así como con el tutor, y esto permitió agilizar mucho la resolución de los problemas con los que nos fuimos encontrando.
