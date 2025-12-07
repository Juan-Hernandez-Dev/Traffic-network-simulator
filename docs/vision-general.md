# Sistema de Simulación de Tráfico Urbano - Descripción General del Proyecto

##  Resumen Ejecutivo

Simulador de tráfico urbano basado en consola que modela intersecciones como nodos de grafo y calles como aristas ponderadas. El sistema gestiona redes viales, calcula rutas óptimas, analiza conectividad y registra vehículos usando tablas hash para operaciones rápidas.

**Curso:** Estructuras de Datos II
**Institución:** Universidad Autónoma de Aguascalientes
**Fecha de Entrega:** 9 de diciembre de 2025
**Tamaño del Equipo:** 3-4 miembros

---

##  Objetivos del Proyecto

### Metas Principales

1. Construir una red vial funcional usando implementación personalizada de grafo
2. Calcular rutas más cortas entre intersecciones (algoritmo de Dijkstra)
3. Analizar conectividad de la red (recorridos BFS/DFS)
4. Gestionar vehículos eficientemente usando tabla hash personalizada
5. Proporcionar persistencia basada en archivos (formato CSV)

### Resultados de Aprendizaje

- Dominar estructuras de datos de grafos y algoritmos
- Implementar tablas hash con resolución de colisiones
- Aplicar análisis de complejidad algorítmica
- Desarrollar código C++ modular y mantenible
- Practicar estándares de documentación de software

---

## ️ Arquitectura del Sistema

### Componentes Principales

**1. Módulo de Grafo (Red Vial)**

- Nodos: Intersecciones con ID y nombre
- Aristas: Calles con pesos (distancia/tiempo)
- Representación: Lista de adyacencia (principal) + matriz de adyacencia (visualización)
- Operaciones: Insertar, eliminar, mostrar, recorrer

**2. Módulo de Algoritmos (Análisis de Rutas)**

- Dijkstra: Cálculo de ruta más corta
- BFS: Recorrido en amplitud para conectividad
- DFS: Búsqueda en profundidad para detección de componentes
- Contador de componentes conexos

**3. Módulo de Tabla Hash (Registro de Vehículos)**

- Búsqueda rápida por ID de vehículo
- Función hash personalizada (modular o multiplicativa)
- Resolución de colisiones (direccionamiento abierto o encadenamiento)
- Operaciones CRUD: Insertar, buscar, eliminar

**4. Módulo de E/S de Archivos (Persistencia)**

- Cargar red desde archivos CSV
- Guardar red modificada
- Validación de formato y manejo de errores

**5. Interfaz de Usuario (Consola)**

- Sistema de menús interactivo
- Validación de entrada
- Salida formateada (tablas, diagramas ASCII)
- Mensajes de error y confirmaciones

---

##  Alcance Funcional

### Lo que el Sistema HACE

 **Gestión de Red**

- Cargar/guardar redes viales desde/hacia archivos CSV
- Agregar/eliminar intersecciones (nodos)
- Agregar/eliminar calles (aristas ponderadas)
- Mostrar red como lista de adyacencia o matriz

 **Cálculo de Rutas**

- Encontrar ruta más corta entre dos puntos
- Reportar distancia total y secuencia de ruta
- Medir tiempo de cómputo

 **Análisis de Conectividad**

- Explorar nodos alcanzables desde origen (BFS/DFS)
- Contar componentes conexos en la red
- Identificar cuellos de botella (nodos de alto grado)

 **Gestión de Vehículos**

- Registrar vehículos con ID, placa, origen, destino
- Búsqueda rápida por ID de vehículo
- Eliminar vehículos del registro
- Mostrar estadísticas de tabla hash (factor de carga, tamaño)

 **Casos de Prueba Requeridos**

- C1: Calcular ruta de UAA a Glorieta Norte
- C2: Mostrar componentes conexos después de eliminar arista específica

### Lo que el Sistema NO HACE

 Simulación de tráfico en tiempo real
 Interfaz gráfica de usuario (GUI)
 Coordenadas GPS o renderizado de mapas
 Multi-threading o procesamiento paralelo
 Optimización de flujo de red
 Dependencias de bibliotecas externas (excepto STL básica)

---

## ️ Stack Tecnológico

### Lenguaje de Programación

**C++ (Estándar: C++11 o superior)**

- Justificación: Requisito del curso, rendimiento, control de memoria
- STL Permitida: `string`, `iostream`, `fstream`, `iomanip`, `cmath`, `ctime`
- Prohibido: `unordered_map`, `vector`, bibliotecas de grafos externas

### Estructuras de Datos (Implementación Personalizada Requerida)

**Grafo**

```
Implementación: Lista de adyacencia con listas enlazadas
Almacenamiento de nodos: Arreglo estático (máx. 50 nodos)
Almacenamiento de aristas: Listas enlazadas dinámicas
Memoria: O(V + E) donde V=nodos, E=aristas
```

**Tabla Hash**

```
Implementación: Direccionamiento abierto o encadenamiento
Tamaño: Número primo (ej., 101)
Función hash: h(key) = key % size (o multiplicativa)
Resolución de colisiones: Sondeo lineal o encadenamiento separado
Factor de carga: α = n/m (monitoreado, no impuesto)
```

### Complejidad de Algoritmos

| Algoritmo      | Complejidad de Tiempo   | Complejidad de Espacio |
| -------------- | ----------------------- | ---------------------- |
| BFS            | O(V + E)                | O(V)                   |
| DFS            | O(V + E)                | O(V)                   |
| Dijkstra       | O(V²) o O((V+E)logV)\* | O(V)                   |
| Hash Insertar  | O(1) promedio           | O(n)                   |
| Hash Buscar    | O(1) promedio           | O(1)                   |
| Hash Eliminar  | O(1) promedio           | O(1)                   |

\*Depende de la implementación de cola de prioridad (arreglo vs heap binario)

### Formatos de Archivo

**Archivo de Red (red.csv)**

```csv
# NODES
N;0;UAA
N;1;Plaza_Patria
N;2;Centro_Historico

# EDGES (dirigidas)
E;0;1;3.5
E;1;2;2.8
E;0;2;6.2
```

**Archivo de Vehículos (vehiculos.csv)**

```csv
# VEHICLES
V;ABC123;Sedan;ABC-123-X;0;2;08:30
V;XYZ999;Truck;XYZ-999-Y;1;0;09:15
```

### Herramientas de Desarrollo

**Compilador:** g++ o clang++
**Sistema de Construcción:** CMake con script run.bat automatizado
**Control de Versiones:** Git (mínimo 4 commits requeridos)
**Editor de Texto:** Cualquiera (VS Code, Vim, CLion, Code::Blocks)
**Depurador:** gdb o depurador integrado en IDE
**Documentación:** LaTeX o Word (formato IEEE)

### Sistema de Manejo de Entrada

**Patrón de Envoltorio de Entrada** (Implementación Personalizada)

- Detección de ESC en todas las entradas del usuario
- Cancelación segura de tipos con `std::optional`
- Sin valores mágicos (-999999, cadenas vacías)
- Patrón consistente en todos los módulos
- Ver: `docs/input-wrapper-guide.md` para detalles

---

##  Lista de Entregables

### Entregables de Código

- [ ] Archivos de código fuente (.h y .cpp)
- [ ] Makefile o instrucciones de compilación
- [ ] Archivos CSV de muestra (red.csv, vehiculos.csv)
- [ ] README.md con instrucciones de uso
- [ ] Repositorio de GitHub (público o privado con acceso)

### Entregables de Documentación

- [ ] Reporte en PDF formato IEEE
- [ ] Sección de diseño: diagramas de estructuras de datos
- [ ] Sección de implementación: explicaciones de algoritmos
- [ ] Sección de pruebas: capturas de pantalla de consola
- [ ] Sección de resultados: casos de prueba obligatorios C1 y C2
- [ ] Conclusiones y trabajo futuro
- [ ] Rúbrica de contribución de miembros del equipo

### Requisitos de Demostración

- [ ] Demostración en vivo del 10-11 de diciembre de 2025
- [ ] Mostrar todas las opciones del menú funcionando
- [ ] Ejecutar casos de prueba obligatorios
- [ ] Manejar casos límite (entrada inválida, nodos inexistentes)
- [ ] Responder preguntas técnicas del profesor

---

##  Criterios de Evaluación (100 puntos)

| Criterio                       | Puntos  | Descripción                                                      |
| ------------------------------ | ------- | ---------------------------------------------------------------- |
| **Estructuras Personalizadas** | 25      | Grafo y tabla hash implementados sin bibliotecas externas        |
| **Corrección de Algoritmos**   | 25      | BFS/DFS/Dijkstra funcionan correctamente en casos límite         |
| **Operaciones Hash**           | 20      | Insertar/buscar/eliminar funcionan apropiadamente                |
| **E/S de Archivos + Menús**    | 15      | Análisis de CSV funciona, navegación de menú es intuitiva        |
| **Calidad de Código**          | 10      | Código limpio, modular y bien comentado                          |
| **Calidad de Reporte**         | 5       | Documentación clara con evidencia                                |
| **TOTAL**                      | **100** |                                                                  |

### Notas de Calificación

- Errores de compilación: -20 puntos
- Fallas de segmentación: -15 puntos
- Casos de prueba obligatorios faltantes: -10 puntos cada uno
- Entrega tardía: -10 puntos por día
- Plagio: 0 puntos + consecuencias académicas

---

##  Métricas de Éxito

### Producto Mínimo Viable (70 puntos)

- Grafo con 10+ nodos cargados desde archivo
- BFS/DFS funcionan en grafo conectado
- Dijkstra encuentra ruta más corta
- Tabla hash almacena 5+ vehículos
- Menú navega sin fallos

### Producto de Crédito Completo (90 puntos)

- Todo lo anterior + manejo apropiado de errores
- Ambos casos de prueba obligatorios funcionan
- Código es modular y documentado
- Reporte incluye todas las secciones requeridas

### Producto Excepcional (100 puntos)

- Todo lo anterior + manejo de casos límite
- Dijkstra optimizado con heap binario
- Visualización de mapa ASCII
- Documentación de grado profesional
- Historial de Git limpio con commits significativos

---

## ️ Errores Comunes a Evitar

1. **Usar contenedores STL para estructuras principales** (unordered_map, vector para lista de adyacencia)
2. **No manejar errores de E/S de archivos** (archivo faltante, formato incorrecto)
3. **Fugas de memoria** en implementaciones de listas enlazadas
4. **Dijkstra fallando en grafos desconectados**
5. **Tabla hash no manejando colisiones**
6. **Navegación de menú pobre** (no hay forma de regresar, falla con entrada inválida)
7. **Validación faltante** (agregar arista a nodos inexistentes)
8. **Inicio tardío** (comenzar 2 días antes de la fecha límite)

---

##  Cronograma Recomendado

### Semana 1 (25 de noviembre - 1 de diciembre)

- Día 1-2: Sistema de menú + Estructura de grafo
- Día 3-4: CRUD de grafo + E/S de archivos
- Día 5-7: Implementación BFS/DFS

### Semana 2 (2 - 8 de diciembre)

- Día 1-2: Algoritmo de Dijkstra
- Día 3-4: Implementación de tabla hash
- Día 5-6: Casos de prueba + corrección de errores
- Día 7: Documentación + reporte

### Semana 3 (9 - 11 de diciembre)

- 9 de diciembre: Entrega
- 10-11 de diciembre: Revisiones presenciales

---

##  Recursos Externos

### Referencias de Algoritmos

- Algoritmo de Dijkstra: Cormen et al., "Introduction to Algorithms"
- Recorridos de grafos: GeeksforGeeks, Visualgo
- Tablas hash: Herramientas de visualización de tablas hash

### Estándares de Codificación

- Guía de Estilo de C++ de Google
- Directrices Principales de C++

### Documentación

- Plantilla de artículo IEEE
- Guía de sintaxis Markdown
- Mejores prácticas de Git

---

##  Canales de Soporte

**Horario de Oficina del Profesor:** Por determinar
**Foro del Curso:** Por determinar
**Comunicación del Equipo:** WhatsApp/Discord/Slack
**Control de Versiones:** GitHub (recomendado)

---

##  Integridad Académica

- El código debe ser trabajo original del equipo
- El pseudocódigo de algoritmos de libros de texto es aceptable
- Citar cualquier referencia externa utilizada
- La colaboración entre equipos está prohibida
- Asistencia de IA (ChatGPT, Copilot) permitida para depuración, no para implementaciones completas

---

##  Lista de Verificación Final Antes de la Entrega

- [ ] El código compila sin advertencias
- [ ] Todas las opciones del menú funcionan
- [ ] Ambos casos de prueba se ejecutan exitosamente
- [ ] Sin fugas de memoria (ejecutar valgrind si está disponible)
- [ ] Los archivos CSV se cargan correctamente
- [ ] README explica cómo ejecutar el programa
- [ ] El reporte tiene todas las secciones requeridas
- [ ] GitHub tiene 4+ commits con buenos mensajes
- [ ] La rúbrica de miembros del equipo está completa
- [ ] Los archivos están nombrados correctamente (apellido_proyecto.zip)
