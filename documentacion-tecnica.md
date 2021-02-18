# Documentación técnica


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
