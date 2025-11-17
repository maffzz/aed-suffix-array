# aed  hito 2  proyecto suffix array

este repositorio corresponde al **hito 2** de aed, donde se implementa y analiza la estructura de datos **suffix array**.

el trabajo continúa y mantiene la coherencia con el **hito 1** (informe te rico), en el que se presentan:

- definiciones formales del suffix array y estructuras relacionadas
- motivaci n y contexto te rico
- ventajas, desventajas y casos de uso

## contenido principal

- `suffix_array.cpp`
  - implementaci n del suffix array **sin estructuras de la stl** (solo arreglos y funciones propias).
  - construcci n del arreglo de sufijos a partir de un texto.
  - b squeda de patrones mediante **b squeda binaria** sobre el suffix array.
  - comentarios en espa ol que explican c mo el c digo refleja la definici n formal y las complejidades mencionadas en el informe del hito 1.

- carpeta `web/`
  - `index.html`: interfaz visual para **explorar el suffix array** paso a paso.
  - `style.css`: estilos con est tica clara y did ctica.
  - `app.js`: l gica en javascript que replica la construcci n del suffix array y la b squeda binaria para mostrar el proceso.

esta parte del proyecto conecta el c digo con el informe te rico del hito 1:

- se muestran todos los sufijos y su orden lexicogr fico.
- se visualiza el **suffix array** como una permutaci n de posiciones.
- se ilustra la b squeda de patrones con complejidad aproximada **o(m log n)**.

## visualizador web del suffix array

el visualizador permite:

- ingresar un texto (por ejemplo `banana`).
- ver todos los sufijos generados y luego ordenados lexicogr ficamente.
- observar el suffix array como arreglo de  ndices.
- seguir paso a paso la **b squeda binaria** de un patr n.

**link al visualizador desplegado:**

> _(reemplazar esta l nea por la url de github pages cuando el deploy est listo, por ejemplo:_ `https://usuario.github.io/repositorio/`_ )_

## estructura del proyecto

```text
proyecto/
├── suffix_array.cpp        # implementaci n principal en c++
├── web/                    # visualizador web del suffix array
│   ├── index.html
│   ├── style.css
│   └── app.js
└── .github/
    └── workflows/
        └── deploy-pages.yml  # workflow para publicar la carpeta web/ en github pages
```

## equipo

| integrante | rol / comentario |
|-----------|-------------------|
| nombre 1  |                   |
| nombre 2  |                   |
| nombre 3  |                   |

> completa la tabla con los nombres de los tres integrantes del equipo y, si quieres, el rol de cada uno (implementaci n c++, dise o del visualizador, redacci n del informe, etc.).
