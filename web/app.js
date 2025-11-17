// función para construir el suffix array en javascript (usando las ideas del código en c++)
// aquí sí podemos usar las funciones básicas de arrays de js, pero manteniendo la lógica clara

function construirSuffixArray(texto) {
  const n = texto.length;
  const sufijos = [];

  // generar todos los sufijos junto con su posición
  for (let i = 0; i < n; i++) {
    sufijos.push({
      sufijo: texto.slice(i),
      posicion: i,
    });
  }

  // ordenar lexicográficamente por el sufijo
  sufijos.sort((a, b) => (a.sufijo < b.sufijo ? -1 : a.sufijo > b.sufijo ? 1 : 0));

  // construir el arreglo de índices
  const sa = sufijos.map((s) => s.posicion);
  return { sufijos, sa };
}

// comparación de patrón con sufijo que comienza en pos
function compararPatronConSufijo(texto, pos, patron) {
  const sub = texto.slice(pos, pos + patron.length);
  if (sub === patron) return 0;
  return sub < patron ? -1 : 1;
}

// búsqueda binaria sobre el suffix array, devolviendo el rastro de decisiones para visualizar
function buscarPatronConTraza(texto, sa, patron) {
  let izquierda = 0;
  let derecha = sa.length - 1;
  const pasos = [];

  while (izquierda <= derecha) {
    const medio = Math.floor((izquierda + derecha) / 2);
    const pos = sa[medio];
    const comparacion = compararPatronConSufijo(texto, pos, patron);

    pasos.push({
      izquierda,
      derecha,
      medio,
      pos,
      comparacion,
      sufijo: texto.slice(pos),
    });

    if (comparacion === 0) {
      return { encontrado: true, posicion: pos, pasos };
    } else if (comparacion < 0) {
      izquierda = medio + 1;
    } else {
      derecha = medio - 1;
    }
  }

  return { encontrado: false, posicion: -1, pasos };
}

// funciones de ui

function $(id) {
  return document.getElementById(id);
}

function limpiarContenedores() {
  $("textoRender").textContent = "";
  $("sufijosLista").innerHTML = "";
  $("sufijosOrdenados").innerHTML = "";
  $("suffixArray").innerHTML = "";
  $("estadoBusqueda").innerHTML = "";
  const res = $("resultado");
  res.textContent = "";
  res.classList.remove("ok", "fail");
}

function renderConstruccion(texto, data) {
  const { sufijos, sa } = data;

  // texto original
  $("textoRender").textContent = texto;

  // sufijos generados (en orden original)
  const listaOriginal = $("sufijosLista");
  listaOriginal.innerHTML = "";
  for (let i = 0; i < texto.length; i++) {
    const item = document.createElement("div");
    item.className = "list-item";

    const idx = document.createElement("span");
    idx.className = "index";
    idx.textContent = i;

    const suf = document.createElement("span");
    suf.className = "sufijo";
    suf.textContent = texto.slice(i);

    const pos = document.createElement("span");
    pos.className = "posicion";
    pos.textContent = `pos = ${i}`;

    item.appendChild(idx);
    item.appendChild(suf);
    item.appendChild(pos);
    listaOriginal.appendChild(item);
  }

  // sufijos ordenados
  const listaOrdenada = $("sufijosOrdenados");
  listaOrdenada.innerHTML = "";
  sufijos.forEach((s) => {
    const item = document.createElement("div");
    item.className = "list-item";

    const idx = document.createElement("span");
    idx.className = "index";
    // aquí mostramos la posición original del sufijo en el texto
    // para dejar claro que solo se cambia el orden, no los índices
    idx.textContent = s.posicion;

    const suf = document.createElement("span");
    suf.className = "sufijo";
    suf.textContent = s.sufijo;

    const pos = document.createElement("span");
    pos.className = "posicion";
    pos.textContent = `pos = ${s.posicion}`;

    item.appendChild(idx);
    item.appendChild(suf);
    item.appendChild(pos);
    listaOrdenada.appendChild(item);
  });

  // suffix array (solo índices)
  const saGrid = $("suffixArray");
  saGrid.innerHTML = "";
  sa.forEach((v) => {
    const cell = document.createElement("div");
    cell.className = "sa-cell";
    cell.textContent = v;
    saGrid.appendChild(cell);
  });
}

function renderBusqueda(texto, sa, patron, traza) {
  const { encontrado, posicion, pasos } = traza;

  const lista = $("estadoBusqueda");
  lista.innerHTML = "";

  const pasoActualBox = $("pasoActual");
  pasoActualBox.textContent = "";

  pasos.forEach((p, idx) => {
    const li = document.createElement("li");
    const step = document.createElement("span");
    step.className = "step";
    step.textContent = `paso ${idx + 1}: intervalo [${p.izquierda}, ${p.derecha}], medio = ${p.medio}`;

    const detail = document.createElement("span");
    detail.className = "detail";

    let cmpTexto = "igual";
    if (p.comparacion < 0) cmpTexto = "menor";
    if (p.comparacion > 0) cmpTexto = "mayor";

    detail.textContent = `se compara el patrón "${patron}" con el sufijo que comienza en pos ${p.pos}: "${p.sufijo}" → el sufijo es ${cmpTexto}`;

    li.appendChild(step);
    li.appendChild(detail);
    lista.appendChild(li);
  });

  if (pasos.length > 0) {
    const ultimo = pasos[pasos.length - 1];
    let cmpTexto = "igual";
    if (ultimo.comparacion < 0) cmpTexto = "menor";
    if (ultimo.comparacion > 0) cmpTexto = "mayor";

    pasoActualBox.textContent = `último paso: miramos el sufijo que empieza en pos ${ultimo.pos} ("${ultimo.sufijo}") y vemos que es ${cmpTexto} respecto al patrón.`;
  }

  const res = $("resultado");
  res.classList.remove("ok", "fail");

  if (!patron) {
    res.textContent = "ingresa un patrón para iniciar la búsqueda";
    return;
  }

  if (encontrado) {
    res.textContent = `patrón encontrado en la posición ${posicion} del texto`;
    res.classList.add("ok");
  } else {
    res.textContent = "patrón no encontrado en el texto";
    res.classList.add("fail");
  }

  // resaltar la celda de sa que contiene la posición encontrada (si existe)
  const cells = document.querySelectorAll(".sa-cell");
  cells.forEach((c) => c.classList.remove("highlight"));
  if (encontrado) {
    sa.forEach((val, idx) => {
      if (val === posicion && cells[idx]) {
        cells[idx].classList.add("highlight");
      }
    });
  }
}

function inicializarUI() {
  const btnConstruir = $("btnConstruir");
  const btnBuscar = $("btnBuscar");
  const textoInput = $("texto");
  const patronInput = $("patron");

  let ultimoTexto = "";
  let ultimoSA = [];

  btnConstruir.addEventListener("click", () => {
    const texto = textoInput.value.trim();
    limpiarContenedores();

    if (!texto) {
      $("resultado").textContent = "ingresa un texto para construir el suffix array";
      return;
    }

    const datos = construirSuffixArray(texto);
    ultimoTexto = texto;
    ultimoSA = datos.sa;

    renderConstruccion(texto, datos);

    btnBuscar.disabled = false;

    const res = $("resultado");
    res.textContent = "suffix array construido. ahora puedes ingresar un patrón y presionar 'buscar patrón'";
  });

  btnBuscar.addEventListener("click", () => {
    if (!ultimoTexto || !ultimoSA.length) {
      return;
    }

    const patron = patronInput.value.trim();
    const traza = buscarPatronConTraza(ultimoTexto, ultimoSA, patron);
    renderBusqueda(ultimoTexto, ultimoSA, patron, traza);
  });
}

window.addEventListener("DOMContentLoaded", inicializarUI);
