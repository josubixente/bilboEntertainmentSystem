BILBO ENTERTAINMENT SYSTEM (BES)
por Josu Vicente, Íñigo Peleteiro y Aitor Sagarduy


Idea general:


La idea general del proyecto es hacer un sistema que junte varios sitios de entretenimiento de Bilbao, BES (Bilbao Entertainment System), entre los que se incluyen los cines, librerias y discotecas —con la posibilidad de añadir más lugares si fuera necesario—. 

La idea original era solamente hacer la parte del cine, para la que pensamos un sistema el cual mediante web scraping cogería datos de cines reales… —se explicará con más detalle abajo—. Sin embargo, rápidamente nos dimos cuenta de que esto sería imposible, o muy difícil, de aplicar a otros tipos de establecimientos. Por eso, las partes de la biblioteca, clubs… estarán más destinadas a una simulación, con datos reales sacados mediante web scraping también, pero sin la posibilidad de compras específicas a diferencia de como se puede hacer en el cine.

Al realizar compras —ya sean entradas, libros, comida…— se guardará en el inventario. Desde ahí se podrán ver todas las cosas que hayas comprado de una forma clara y organizada, además de información adicional —la fecha de compra, la descripción del artículo…—.

Para las partes que sean de “simulación”, se usarán unas tarjetas de crédito ficticias —cada una de ellas con una cantidad de dinero ya asignada—. Estas tarjetas se podrán ver desde la sección del inventario.

el proyecto usará la shell de tu ordenador ( comandos adaptados tanto para linux como para windows) donde usaremos ASCII para representar todo lo necesario para que el usuario pueda hacer sus reservas en los sitios públicos de Bilbao sin tener ningún problema





















CINE

La parte del cine del proyecto se encargará de manejar un simulador de la reserva de un cine (ejemplo base: Alhóndiga y Zubiarte) pudiendo reservar entradas de una lista de películas que se seleccionará entre cines —con los datos de las películas reales—, guardarlas en bases de datos…

Pasos en la reserva del cine:

Menú de selección: Tendrás que elegir la opción de reservar entradas, aunque se te dará la bienvenida con un texto hecho en ASCII —sacado de la lectura de un fichero— para que se lea “BILBO ENTERTAINMENT SYSTEM” (BES) en letras grandes y resultonas. Esta pantalla funcionará a modo de menú principal con el que también se podrá acceder a las diferentes partes del proyecto (biblioteca, clubs…).



Filtrar: Al no poder decantarnos por cómo se iban a mostrar los datos, decidimos poner dos opciones: “filtrar por cine” y “filtrar por película”.

Filtrar por cine: Dará una lista de todos los cines con los que nuestro programa opera para que se seleccione uno y mostrar las películas disponibles.
Ejemplo:
Zubiarte -> Policán (16:00) , Capitán América (18:00)…
Alhóndiga -> Capitán América (17:40), Better Man (16:00)…

Filtrar por película: Se mostrará una lista con todas las películas que hay en todos los cines y el nombre de los cines en los que se proyectará al lado.
Ejemplo:
Policán (Zubiarte)
Better Man (Alhóndiga)
Better Man (Zubiarte)

Selección de películas: Independientemente de que opción de filtrado se haya elegido, saltará un menú de selección de las películas a reservar —esta es la parte más importante de la sección del cine ya que es la que se encargará de que se muestre una lista actualizada y real de las películas.

Los dos cines con los que de momento vamos a tratar —si fuera necesario se podrían añadir más— son la Alhóndiga y Zubiarte. Cada uno opera de una manera diferente por lo que conseguir los datos también debe hacerse de forma diferente.

En el caso de la Alhóndiga, se le hará un “web scraping” a su página web, la cual al no usar Cloudflare, se podrá hacer de manera sencilla usando Beautiful Soup en Python 3.

Sin embargo, como Zubiarte sí que usa Cloudflare, en vez de hacer una petición, entraremos directamente con el navegador; para eso usaremos JavaScript. Los 2 lenguajes están bien implementados en el proyecto que usa C como base. 

Estas películas se añadirán a la base de datos “PELÍCULA”, usando el lenguaje de manejo de bases de datos SQL, donde por cada una, se guardará también su horario y cine —en el que se proyectará—.

Para poner la array de películas posibles usaremos un malloc para reservar memoria en cierto punto de esta y luego ir completando con las películas que hemos extraído del webscrapping.

A parte de los dos cines, la idea es también hacer una funcionalidad para poder comprarlo con películas de distintos tipos sacadas de la API publicadas, TMDB , para saber qué películas se encuentran actualmente en las más taquilleras mundiales, cuales son películas antiguas, o cuales películas no se encuentran actualmente en el cine

pagina web de TMDB → https://www.themoviedb.org

Selección de butacas: Una vez seleccionada la película y el cine, el usuario podrá elegir el número de butacas que quiere reservar, poniendo como máximo todas las butacas disponibles en la sala (no se pueden butacas negativas). Luego se enseñará una matriz de asientos (siendo los círculos los asientos que están disponibles) donde para reservar se tendrá que escribir por consola la fila y columna del asiento. Al reservar el asiento, el asiento quedará marcado con una “X” y no podrá volver a ser escogido.









El proceso se repetirá hasta que las butacas escogidas sean las mismas que las que han sido “puestas” —entiéndase por puestas el acto de escoger su posición y que cambie el “0” por una “X”—.

Detalles de compra: Una vez hecha la reserva, los asientos se reservarán en la base de datos “ASIENTO” para pasar al recibo que se le entregará al cliente con los detalles de la compra. Los recibos sirven para poder manejar mejor los asientos y a quien pertenecen en las funciones del administrador.



Tenemos también la idea de usar sockets, pero aún no se nos ha explicado muy bien su funcionamiento, así que en un futuro se verá cómo implementar su uso.

MANEJO DE LA INTERFAZ
C es el lenguaje con el que se programa Arduino, y junto con este varios componentes del hardware. Teniendo en cuenta esta información, no queríamos desaprovechar las ventajas en la robótica de este lenguaje, así que nuestra idea es poner dispositivos externos con los que podamos manejar la interfaz de forma alternativa a teclear por terminal, haciendo una experiencia diferente a una gestión habitual





LIBRERÍA

La sección de la librería, a decir verdad, es muy similar a la del cine, por lo que las explicaciones no estarán tan detalladas como en esa parte.

Como se ha mencionado antes, esta parte es meramente una simulación, por lo que no se podrá elegir de qué librería se van a coger los libros. En su lugar esto será una librería ficticia —nombre a decidir— compuesta por los datos de Casa del Libro. Estos datos, al igual que en el cine, se obtendrán mediante el Web Scraping. 

Al solo ser una única librería, los datos no se podrán filtrar de diferentes maneras, por lo que únicamente se mostrará el título del libro y su precio. Eso sí, al tener seleccionar un libro y pulsar la tecla “D”, se le mostrará al usuario una descripción del libro, también obtenida mediante el Web Scraping.

Todos esos datos se guardarán en la base de datos “LIBRO”, la cual incluirá: título, precio compra, precio alquilado y una descripción.

Al seleccionar el libro, se presentarán dos opciones: “comprar” y “alquilar”.

Comprar: Al indicar que se quiere comprar el libro, se tendrá que seleccionar la tarjeta de crédito —ficticia— y en caso de tener el saldo necesario, el libro pasará a formar parte del inventario de forma permanente.

Alquilar: Si, por el contrario, se alquila el libro, no se guardará en el inventario de forma permanente. En su lugar, el libro contará con una fecha límite de devolución. Gracias a la función “<time.h>” podremos comprobar si la fecha establecida —márgenes cortos de tiempo— coincide con la del ordenador del usuario. De ser el caso, se sancionará cobrando automáticamente el precio completo del libro a la tarjeta que haya sido usada para alquilarlo.

Independientemente de qué opción haya sido seleccionada, se llevará al usuario a la “pantalla” en la que se realizará el pago —el precio varía dependiendo de si se va a comprar o alquilar—. Se tendrá que elegir la tarjeta de crédito a utilizar de array de tarjetas. Al escoger una, se hará una comprobación de que hay saldo suficiente —el total de dinero dentro de la tarjeta - el precio del libro > 0—, de ser así, se restará el total y se actualizarán los datos de la tarjeta; “TARJETA” donde se guardaran los datos —número de tarjeta, titular, fecha de vencimiento, CVV— y el saldo.

¿QUE SOLUCIONAMOS?

A veces tener que acceder a tantas paginas web para consultar sobre las mismas cosas pero de distintas marcas o diferentes sitios es algo poco óptimo, a ti te interesa ver una película y te importa poco la compañía de cines donde la saquen, y así pasa con todos los servicios de entretenimiento por toda la ciudad de bilbao, pero ¿Y si hiciéramos un programa de manejo rápido para todas esas cosas, y así que el usuario pueda ver que planes hay en bilbao de manera rápida y sencilla?
Bilbo Entertainment System 

RECURSOS
lenguajes:
→ SQL
→ C
→ C++
→ JavaScript
→ Python
otros recursos:
→ TMDB
→ node
→ beautifulsoup


