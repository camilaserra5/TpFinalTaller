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

#### [Git](https://git-scm.com/)

#### [SDL2](https://www.libsdl.org/download-2.0.php)

#### [qt](https://www.qt.io/)

#### [CLion](https://www.jetbrains.com/es-es/clion/)

### Conclusiones





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
