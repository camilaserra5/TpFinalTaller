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

### División de tareas

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
* **Semana 1 ()**  
  * Servidor/Cliente: que el cliente le envíe eventos básicos como tecla o movimiento
  * Que el servidor cargue el mapa (yaml)
  * Aplicación con qt para crear el yaml con una matriz de mxm (el mapa)
  * Dibujar sprits o jugadores
* **Semana 2**  
* **Semana 3**  
* **Semana 4**  
* **Semana 5**  
* **Semana 6**  
* **Semana 7**  

### Inconvenientes encontrados

### Análisis de puntos pendientes

### Herramientas
Las herramientas utilizadas para este proyecto fueron las siguientes:

#### [Git](https://git-scm.com/)


#### [SDL2](https://www.libsdl.org/download-2.0.php)

#### [qt](https://www.qt.io/)

#### [CLion](https://www.jetbrains.com/es-es/clion/)

### Conclusiones

## Documentación técnica

### Requerimientos de software

### Descripción general

### Módulo N

#### Descripción general

#### Clases

#### Diagramas UML

### Descripción de archivos y protocolos

### Programas intermedios y de prueba

## Manual de Usuario

### Instalación

#### Requerimientos de software
La instalación del programa se debe realizar mediante la compilación del código fuente del mismo.
Idóneamente el programa puede ser compilado en cualquier distribución de Linux, habiendo instalado previamente los siguientes paquetes:
● Gtkmm-3.0-dev
● Libsdl2-dev
● libsdl2-mixer-dev
Los tres son fácilmente accesibles en distribuciones de la familia Debian, a través de apt. Para simplificar esto, se entrega un script bash ​ installs.sh que se encarga de la instalación de dichos paquetes. Para compilar el programa, es necesario cmake, de versión ​ 2.5​ o mayor.

#### Requerimientos de hardware
Dado que el software entregado no tiene mayores exigencias en cálculos gráficos, no es necesario tener una placa gráfica dedicada. El programa fue testeado en máquinas con procesadores Intel ® de la familia i5 en adelante.

#### Proceso de Instalación
Para poder utilizar el juego hay que realizar los siguientes pasos:
* abrir una terminal (ctlr + alt + T)
* posicionarse en el directorio se quieran descargar los archivos

```bash
foo@bar:~$ cd /home/cami/wolfstein
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


### Apéndice de errores
