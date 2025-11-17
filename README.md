# AED - Hito 2 - Proyecto Suffix Array

Este repositorio corresponde al **Hito 2** del curso de AED, donde se implementa y analiza la estructura de datos **Suffix Array**.

El trabajo continúa y mantiene la coherencia con el **Hito 1** (informe teórico), en el que se presentan:

- Definiciones formales del Suffix Array y estructuras relacionadas
- Motivación y contexto teórico
- Ventajas, desventajas y casos de uso

## Contenido principal

- `suffix_array.cpp`
  - Implementación del Suffix Array **sin estructuras de la STL** (solo arreglos y funciones propias).
  - Construcción del arreglo de sufijos a partir de un texto.
  - Búsqueda de patrones mediante **búsqueda binaria** sobre el Suffix Array.
  - Comentarios que explican cómo el código refleja la definición formal y las complejidades mencionadas en el informe del Hito 1.

- Carpeta `web/`
  - `index.html`: interfaz visual para **explorar el Suffix Array** paso a paso.
  - `style.css`: estilos con estética clara y didáctica.
  - `app.js`: lógica en javascript que replica la construcción del Suffix Array y la búsqueda binaria para mostrar el proceso.

Esta parte del proyecto conecta el código con el informe teórico del Hito 1:

- Se muestran todos los sufijos y su orden lexicográfico.
- Se visualiza el **Suffix Array** como una permutación de posiciones.
- Se ilustra la búsqueda de patrones con complejidad aproximada **O(m log n)**.

## Visualizador Web del Suffix Array

El visualizador permite:

- Ingresar un texto (por ejemplo `banana`).
- Ver todos los sufijos generados y luego ordenados lexicográficamente.
- Observar el Suffix Array como arreglo de índices.
- Seguir paso a paso la **búsqueda binaria** de un patrón.

**Link al visualizador desplegado:**

> _`https://maffzz.github.io/aed-suffix-array`_

## Estructura del proyecto

```text
proyecto/
├── suffix_array.cpp          # Implementaciín principal en C++
├── web/                      # Visualizador Web del Suffix Array
│   ├── index.html
│   ├── style.css
│   └── app.js
└── .github/
    └── workflows/
        └── deploy-pages.yml  # Workflow para publicar la carpeta web/ en GitHub Pages
```

## Grupo 5 ✨

| Nombre                                   | Carrera | Perfil de GitHub                              |
|------------------------------------------|---------|-----------------------------------------------|
| Martín Jesús Bonilla Sarmiento 🧠        | CS      | https://github.com/marbs23                   |
| Annemarie Alejandra Saldarriaga Núñez 💻 | CS      | https://github.com/AnnieSld                  |
| María Fernanda Lazón Meza 📊             | DS      | https://github.com/maffzz                    |
