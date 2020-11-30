# [75.42] Taller de programación I
## Trabajo práctico final: Wolfenstein 3D
(nosotras) para compilar crear una carpeta build en el proyecto, entrar en esa carpeta, abrir una terminal y ejecutar cmake .. 

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
* **Semana 1**  
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

#### Requerimientos de hardware

#### Proceso de Instalación

### Configuración

### Forma de uso

### Apéndice de errores
