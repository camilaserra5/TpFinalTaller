# Manual de Usuario

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
foo@bar:~$ cd /home/user/wolfestein
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

**Importante!**: el mapa debe ser un recinto cerrado de paredes y todos los clientes deben utilizar el mismo ancho  y alto de pantalla.  
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
This is a normal paragraph following a header. GitHub is a code hosting platform for version control and collaboration. It lets you and others work together on projects from anywhere.

## Header 2

> This is a blockquote following a header.
>
> When something is important enough, you do it even if the odds are not in your favor.

### Header 3

```js
// Javascript code with syntax highlighting.
var fun = function lang(l) {
  dateformat.i18n = require('./lang/' + l)
  return true;
}
```

```ruby
# Ruby code with syntax highlighting
GitHubPages::Dependencies.gems.each do |gem, version|
  s.add_dependency(gem, "= #{version}")
end
```

#### Header 4

*   This is an unordered list following a header.
*   This is an unordered list following a header.
*   This is an unordered list following a header.

##### Header 5

1.  This is an ordered list following a header.
2.  This is an ordered list following a header.
3.  This is an ordered list following a header.

###### Header 6

| head1        | head two          | three |
|:-------------|:------------------|:------|
| ok           | good swedish fish | nice  |
| out of stock | good and plenty   | nice  |
| ok           | good `oreos`      | hmm   |
| ok           | good `zoute` drop | yumm  |

### There's a horizontal rule below this.

* * *

### Here is an unordered list:

*   Item foo
*   Item bar
*   Item baz
*   Item zip

### And an ordered list:

1.  Item one
1.  Item two
1.  Item three
1.  Item four

### And a nested list:

- level 1 item
  - level 2 item
  - level 2 item
    - level 3 item
    - level 3 item
- level 1 item
  - level 2 item
  - level 2 item
  - level 2 item
- level 1 item
  - level 2 item
  - level 2 item
- level 1 item

### Small image

![Octocat](https://github.githubassets.com/images/icons/emoji/octocat.png)

### Large image

![Branching](https://guides.github.com/activities/hello-world/branching.png)


### Definition lists can be used with HTML syntax.

<dl>
<dt>Name</dt>
<dd>Godzilla</dd>
<dt>Born</dt>
<dd>1952</dd>
<dt>Birthplace</dt>
<dd>Japan</dd>
<dt>Color</dt>
<dd>Green</dd>
</dl>

```
Long, single-line code blocks should not wrap. They should horizontally scroll if they are too long. This line should be long enough to demonstrate this.
```

```
The final element.
```
