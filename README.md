# [75.42] Taller de programación I
## Trabajo práctico final: Wolfenstein 3D

**Fontenla, Maria Sol**  
103870  
**msfontenla@fi.uba.ar**

**Izquierdo Osorio,  Stephanie**  
104196  
**sizquierdo@fi.uba.ar**

**Segura, Agustina**  
104222  
**asegura@fi.uba.ar**

**Serra, Camila**  
97422  
**cserra@fi.uba.ar**

___

## Introducción

* [Manual de Proyecto](#)
  + [Enunciado](#)
  + [División de tareas](#)
  + [Evolución del proyecto](#)
    + [Cronograma propuesto](#)
    + [Cronograma real](#)
  + [Inconvenientes encontrados](#)
  + [Análisis de puntos pendientes](#)
  + [Herramientas](#)
  + [Conclusiones](#)
* [Documentación técnica](#doc)
  + [Requerimientos de software](#)
  + [Descripción general](#)
  + [Módulo N](#)
    + [Descripción general](#)
    + [Clases](#)
    + [Diagramas UML](#)
    + [Descripción de archivos y protocolos](#)
  + [Programas intermedios y de prueba](#)
* [Manual de Usuario](#manual)
  + [Instalación](#)
    + [Requerimientos de software](#)
    + [Requerimientos de hardware](#)
    + [Proceso de Instalación](#)
  + [Configuración](#)
  + [Forma de uso](#)
  + [Apéndice de errores](#)


## Manual de Proyecto

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

### Análisis de puntos pendientes
* No hubo tiempo suficiente para hacer tests sobre el código realizado.

### Herramientas
Las herramientas utilizadas para este proyecto fueron las siguientes:

#### [Git](https://git-scm.com/)

#### [SDL2](https://www.libsdl.org/download-2.0.php)

#### [qt](https://www.qt.io/)

#### [CLion](https://www.jetbrains.com/es-es/clion/)

### Conclusiones


___


## Documentación técnica

### Requerimientos de software

### Descripción general
El programa cuenta de 4 módulos: cliente, servidor, editor y commons. El módulo de commons es utilizado por los otros 3 para cosas como los mapas, los sockets y la seri  alización. A continuación se muestra en mayor detalle las responsabilidades de cada uno.

### Módulo 1 - Cliente
#### Descripción general
El cliente fue hecho con SDL2. En primer lugar, al usuario se le muestra una pantalla de login. En la misma, se podrá conectar al servidor que quiera y luego crear una partida o elegir entre las existentes.

Una vez que la partida empiece, el jugador podrá ver la pantalla con el juego.

Cuando termine, se mostrará una tercer pantalla con el ranking.

#### Clases y Diagramas UML
![](http://www.plantuml.com/plantuml/png/dP8nJmCn38Nt_8gCC00x0wg465g1X61WJcDp1DtPfvnpyFF9fOgQj3aXM3BOd-ttbBUPn7W9Gwy-7A1-PvOzVojbhB3NOKAlnWWuwqP3eWVZg2hSzmv9iAezShUbDqV0NmtsOOxFAnAWN-k-e4Ktd_Ht0JkkAa-6yDC0-pJ4arABNdrrbsJgMtrzOzFInOsRZU11__94AckFu073YyiZcOrbAFA5hpZZ0ntfqZ9Wgxo-YFU2X7uBkz0jRaeLvO9ogbBluBytdpqBM-xvppV7FFdxwVD_Z_CfTl5g6yi1Q8Cf2UtMQIGA2l3iRm7hO6oG80pz3m00)

Client_event_reciver: Es el hilo que se encarga de recibir las actualizaciones, deserializarlas y volverlas a meter en la cola protegida.

![](http://www.plantuml.com/plantuml/png/TL4xJWGn3ErzYfH3mGKeq2943rm0PMsli9IDHrvdX3Wz2KsKsKmpqlWzlqzykdaqBzS4tq8SBgf-rX-0YAuMoeqDraeGb3Lc3wz9EFlRLZ-VZ2pR3dytTKLDEanVq4jCyXjHDD_n6Ptfet1XW6OO7fzdFk4fMCdBGuicMtIUXacgQ-1QwWlLhEAa46RCwjBJDcr6EOjrzLwbqmwJIRue44-MvzRZarG1ujfS_YSMbYRNYuva6FwE8yLXYNYkTfHlF4oJon99R1baUyRz9OcF4Cu47PvVyLH9vPh-0000)

Client_event_sender: Es el hilo que se encarga de sacar de la cola bloqueando los comandos, serializador y mandarlos.
![](http://www.plantuml.com/plantuml/png/VL7DIiGm4BxdAUQu7dm13x8etXKVG68wguDf9cGdHNnwluL0DspQImFz_fFZsNonEaVtBHFJITK-zTSv7qmBrJCNbq6G8Dade-SedEnbmUUTqmIqWv-YXXz9Ns-LA_T2dNsQjFltMjGqQ5HtoQ7xnrjxUg1Iq-7kqaSMRpne45KpCNPy12q5A69kM73lsy4vQrvzEz3rr8rceMsQUCDbsABT1FGOBJxAdo-7PdMzivctSwk3f5ChqCk8Hk7hbKFAQH54m-4gTsMubRkVFP22uO3iFDeHHvtZFm00)

ManejadorEventos: se encarga de manejar la lógica de recibir eventos del teclado como avanzar, rotar, disparar, etc. Una vez que capta el evento, acá se crea el comando y se lo agrega en la cola de eventos.
![](http://www.plantuml.com/plantuml/png/dP6nJWCn38PtFqN6wu34nC20MWGRI20Ue78JjpKaSUGuXQ4FJteIekYeL7Mu6-pl__uecLT3jPOYR3cGMulOIhu0q9keQvKKIWVOSy5ixXaplMCGVTnHDga0S63SrTravMwTjZpC3YhUeT4q74MAesguzABAb8F0HDFLRmzFtTR_onU9SLpyMliO-dVY23J2WOxnISU9R20ZR_Wp6KRN332QYxIslV9cQ_jMza4-yx_I-oZ-W_FcjL6ZRYojReSaEqvyO8xkvWy9WKuiA5PoXPGbd5yOk1PKr0lh5kStUKmhbeKclA0hXtCVfaQYCjnSpyRGaN82mxmJBSLl)

Juego: es el hilo encargandor de realizar el loop, es decir, de limpiar, actualizar el modelo, renderizar y presentar. A su vez se encarga de
realizar el algoritmo de raycasting.
![](http://www.plantuml.com/plantuml/png/TP8nJmCn38Nt_8gCHQ8I4mC3AX8BI4Y5WRLo4_S8kiQHurIKNuzFFQAaLRSxFp-_BvPNMO2bx4Vp5JpQ7P5iwSSOS49iIqOsIHk22mcYsDU20tMLD_8uzgLFZ08HkffTCmawGVzUi62dVS2HZ9coxFBn564VB9Uuk9aumW44v-IHA5bKveqZve3HapaPr7b2KMjYSfY1dvmK6CClk40HSpjknfujwZu3r2cq5Op86mz2hVNi9Vrlom5jlF5uROB77gi-gLa671ra2N5GaghguYRnW1nsmG6_H47EwAQynHuIt5eVia1qGJ-_om2U-D8_e3p_jodQKT68QqvBWT4ZwuDu3Oo-QPd1kvvMda_YgbxjTMTNx9r-IPX7nBIulxDBgmC5j4VpweRh7QsqgaV_1m00)


### Módulo 2 - Servidor
#### Descripción general
El servidor se encarga de recibir a todos los clientes, crear y manejar las distintas partidas.

#### Clases y Diagramas UML
Cuando un cliente se conecta, se le mandan las partidas que no empezaron serializadas. Luego, se recibe si el cliente va a crear una nueva o unirse a la existente, y en base a eso se sigue la lógica.
![](http://www.plantuml.com/plantuml/png/jLHDRzim3BtxL-Ze04jt7x2WnSu31gptWfQOb9jC6PISVVpwoOuQoOvQ0mDwI60_yecFV9JlVG09Os-RPpAeZiw5plrk6j31YHezIZF41D8q00VL0_42UD0u131kcVRu_CKISbY0tvt-YKleAp3-cDZV9j20Nn9GpZGTtJIJ4BK_pFNL9tNtqQUOqewFTBhx0xsTHDCP0bvaJd-Ha-f6LaTidY3-BFc0t0vEmYwJaZw3QqGBnhUAs5JXDXABCVvAn696YP2Hb5Z3PsDQFqlueFfrYIoyEDywDwWBvUaCbenhL0xl3zTHm8n9kulnTRigFUmFfPm1KMB8u6rwQlDgUb4oDdN5Bxssqq7LVahQafTcKOWjg-N4LwpmA0IM_fRzrWrLjzXAoP1J3RvrKYQLAuXyfYXZo4tNymGrTVIsFojbn4SdFMXo_8fFO8CYepwhaKayRazkTlRbVNDsQG_ojQrFCyMlkx-T1IV14yX5AhRi-avmj-s0mTgseFMeDdjVLtr8aHVh_cUHwdMwqMkGzV7lDfOOHpRhErhUT4iT2iWZIaySCH-TdoWb8M-gHf7vOXciV90IcZ_AzyXcxEq_)

Una vez que la partida está completa, se da inicio y el servidor la maneja de la siguiente manera:
![](http://www.plantuml.com/plantuml/png/VLH1Rjmm3Bpp5Jvw3m5wwY6786tGOu6sUK2WbIOjKriqP7bHz4TzHpzMxcvSByCeHv4pmn57zkrSGwdBED0FJkWUHUfUVX65MALqoun2am8uyXHoxUvH3fp45Z-7ZAUWrRk1aIiS0-NJGHlto0cbrVs62DO37OTsLpV_PtNNNLbolpjwuaEes5pG839ryJnsfhMkR6VAgpZRZg8oNufKYJA8yf4F74gFSKBy-sVdy5StxhBNf_LQxnQoNWAAV8XI2cjLoC6EPZuE4dzo_lvrmG8rDCcq2PicMQXodQ3obRk4WN-7o98feQ7rgfSFbrpLcb7uT2wR9OCXosXOulmePNI6h98Zlangrcf_8RKZBH1TAZgDPfpcTRO2DQ1ceWRdRHT4tlEsmAr96qmvNiglpckq7Dp96DIWAYJu5B7sQSKr3SHdO8BZld5vn8gqlkYGEIGk3obKwP_rpk4blBdnXFPtVU8tC-4ahtkHVKN6sOkDP8EHFThVbb-8ewzWcmEU49VgCcYjTfKmi-S1cFhtxyxRkoIk8BhLpZ8E_m00)


### Módulo 3 - Common

#### Descripción general
Este módulo consta de las cosas que son comunes tanto entre Servidor y Cliente, como con el Editor.
En este se encapsula la logica de las armas, los movimientos, el mapa, la serializacion entre otras cosas. 

#### Clases y Diagramas UML
Serialización: para la serialización se creo la clase ISerializable, la cual luego extienden todas las clases que necesiten ser serializadas. Por ejemplo, los comandos, las actualizaciones y el mapa.
![](http://www.plantuml.com/plantuml/png/bPAnJiCm48RtF8Kdr0uii4KLQbKwK06gH7VanaTgbFZGnOu0yV3OLLo5sf5njlZ-xtBnVSjESzAcROgZ5C3U4FK1FulYuGL8yaP-yqC3RF5pxHwsghGv7LOILJJ3rjXo9J1Mj3MbGO50keTD0oqeZLsypSRE9N1heCQ9MRQcjWcAuuzOKto69_uHHtROoSdVSfo2T_V17ISj1P-OsvxrqerrKIvPBybT7kkqACiUAesqg8wSxbZdWpIRJs8zIi44ZB9XewjpLM3OASmhqnw0zhYsRoiY_ZKpKkdRcrSzbC8cvq3bcJq-ksni7kxgy-AFDV--YG1Bn0Vnqi6eXMbiP6GwFCYP3fv4JSUijUcGDpYT36HE8rviLkRkBTzSlyfyTdgxsPqk5fxFUmVoMQz5FkbDoUT6ykJ3CP_okumKouUNe8Hfcry0)



### Módulo 4 - Editor

#### Descripción general
Esta aplicación está hecha con qt. Es un editor de mapas, donde el usuario puede crear y editar mapas para luego utilizar en el juego.

#### Clases y Diagramas UML
El editor consta de 3 clases principales.

* **MainWindow**
Es la ventana principal de la aplicación. Extiende de QMainWindow. Esta es la encargada de crear a las otras dos clases que manejan, una la lista de tiles disponibles, y orta el mapa en sí. También tiene toda la lógica de crear un nuevo mapa, guardarlo y cargar un mapa existente.

* **MapWidget**
Es el mapa en sí. Extiende de QWidget. Maneja los eventos de drop sobre el mapa guardando el tipo y la posición.

* **MapTilesList**
Es la lista de los tiles disponibles para utilizar. Extiende la clase QListWidget. Consta de una lista de tiles, y maneja los eventos de drag y doble click sobre un tile.

El guardado y mostrar un mapa existente, se hacen fundamentalmente con la clase **MapTranslator**. Esta clase vive en el módulo commons. Lo que hace es que a partir de la clase Map la pasa a YAML y viceversa.


### Descripción de archivos y protocolos  
El protocolo desarrollado trata a los bytes para su lectura como big endian. Ademas, este protocolo serializa, en general, de la siguiente manera: primero se envia el tamanio del parametro que ese esta serializando, y luego se serializa el parametro. Esto es porque, al ser binario, se requiere saber cuantos bytes corresponden a cada entidad para su deserializacion. De esta manera, se deserializa cada entidad de manera ordenada, evitando posibles errores.  

### Programas intermedios y de prueba
Originalmente, el programa lo realizamos en una sola aplicación simulando el cliente y el servidor, para no tener que tratar con la serialización. Una vez que eso estuvo más estable, involucramos los distintos hilos y la conexión mediante socket.
___

## Manual de Usuario

### Instalación

#### Requerimientos de software
La instalación del programa se debe realizar mediante la compilación del código fuente del mismo.
Idóneamente el programa puede ser compilado en cualquier distribución de Linux, habiendo instalado previamente los siguientes paquetes. Los mismos son fácilmente accesibles a través de apt.
* gtkmm-3.0-dev
* libsdl2-dev
* libsdl2-mixer-dev
* lua5.3 liblua5.3-dev
* libsdl2-ttf-dev
* libyaml-cpp-dev


#### Requerimientos de hardware
El programa fue probado en computadoras sin una placa gráfica especial, y con procesadores intel i5 e i7.

#### Proceso de Instalación
Para poder utilizar el juego hay que realizar los siguientes pasos:
* abrir una terminal (ctlr + alt + T)
* posicionarse en el directorio se quieran descargar los archivos

```bash
foo@bar:~$ cd /home/user/wolfstein
```
* clonar el repositorio (**alternativa**: [descargarlo](https://github.com/solfonte/TpFinalTaller/archive/main.zip) desde github y descomprimirlo en la carpeta deseada)

```bash
foo@bar:~$ git clone git@github.com:solfonte/TpFinalTaller.git
```
* crear una carpeta **build** y posicionarse

```bash
foo@bar:~$ mkdir build
foo@bar:~$ cd build
```
* compilar el código fuente

```bash
foo@bar:~$ cmake ..
foo@bar:~$ cd common
foo@bar:~$ sudo make install
foo@bar:~$ cd ..
foo@bar:~$ make
```
##### Ejecutar el cliente!

```bash
foo@bar:~$ cd client
foo@bar:~$ ./client
```
##### Ejecutar el servidor!

```bash
foo@bar:~$ cd server
foo@bar:~$ ./server config.yaml
```
##### Ejecutar el editor!

```bash
foo@bar:~$ cd editor
foo@bar:~$ ./editor
```


### Configuración
Para levantar el servidor correctamente, se necesita un archivo con la configuración del mismo. Este deberá ser una archivo yaml de la siguiente manera:
``` yaml
port: 8080

```

### Forma de uso
#### Editor
Una vez levantado el editor se verá la siguiente ventana:
![editor](editor1.png)


##### Crear un nuevo mapa
Para crear un nuevo mapa, ir a Archivo -> Nuevo (o ctrl + N). Se abrirá la siguiente ventana que permite elegir el tamaño deseado del mismo.
![editor](editor2.gif)  

Una vez que tengamos el tamaño apropiado, para completarlo se pueden arrastrar las imágenes desde la lista izquierda. Haciendo doble click, se podrá pintar la superficie deseada:
![editor](editor3.gif)   

**Importante!**: el mapa debe ser un recinto cerrado de paredes.  
##### Guardar el mapa
Para guardar el mapa una vez que ya este listo ir a Archivo -> Guardar. El mapa deberá ser un archivo .yaml o .yml

##### Abrir un mapa existente
Para editar un mapa ya existente, ir a Archivo -> Abrir. Seleccionar el archivo correspondiente y listo!

#### Servidor
Una vez instalado correctamente, y ya teniendo el archivo de configuración, sólo falta levantar el servidor desde su carpeta, y listo!
```bash
foo@bar:~$ ./servidor config.yaml
```

#### Cliente
Una vez levantado el cliente, se verá la pantalla de log in para conectarse al servidor deseado. Ingresar ip y puerto correspondiente:
![cliente](cliente1.gif)

Una vez conectado al servidor, se listaran las partidas existentes (en las que haya lugar disponible). Se puede unir a una, o de lo contrario crear una partida propia.
![cliente](cliente2.png)

##### Crear una partida nueva
Para crear una partida nueva en el servidor, escribir una N y luego ingresar los datos correspondientes:

* Nombre de la partida
* Cantidad de jugadores posibles
* Ruta del archivo del mapa de la partida (mapa generado por el editor)
* Nombre del jugador

![cliente](cliente3.gif)

##### Conectarse a una partida existente
Para unirse a una partida nueva, escribir el número correspondiente y luego enter. Luego ingresar el nombre, y esperar!
![cliente](cliente4.gif)

##### Teclas para jugar  

**->**: rotamos hacia la derecha.    
**<-**: rotar hacia la izquierda.  
**.**: disparar.  
**^**: desplazarse hacia delante.  
**v**: desplazarse hacia atras.  
**SPACE**: cambiar de arma.  
**m**: play/stop music.  

### Apéndice de errores
