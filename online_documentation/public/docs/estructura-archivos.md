# Estructura de Archivos del Proyecto

Este documento describe qué hace cada archivo del proyecto, organizado por carpetas.

---

##  data/

Carpeta que almacena los datos persistentes del programa (redes y vehículos).

### `.movements.csv`

- **Propósito**: Registro histórico de movimientos de vehículos
- **Contenido**: Log de cada intento de movimiento (exitoso o fallido) con ID de vehículo, destino, estado, tiempo de viaje y razón de fallo
- **Uso**: Generado automáticamente cuando se mueve un vehículo usando la opción "Move Vehicle"

### `n.csv`

- **Propósito**: Archivo de red de ejemplo con nodos y aristas
- **Contenido**: Definición de nodos (N;id;nombre) y aristas (E;origen;destino;peso)
- **Uso**: Puede cargarse desde el menú "Load Network" para trabajar con una red predefinida

### `v.csv`

- **Propósito**: Archivo de vehículos de ejemplo
- **Contenido**: Lista de vehículos (V;id;placa;tipo;nodoActual;nodoDestino)
- **Uso**: Puede cargarse desde el menú "Load Vehicles" para trabajar con vehículos predefinidos

---

##  seeds/

Carpeta que contiene archivos semilla (plantillas) para generar datos de prueba.

### `red.csv`

- **Propósito**: Plantilla de red pequeña con 5 nodos
- **Contenido**: Red básica de Aguascalientes (UAA, Plaza Patria, Centro Histórico, etc.)
- **Uso**: Archivo de ejemplo para entender el formato de redes

### `seed1.csv`

- **Propósito**: Plantilla de red mediana con 6 nodos
- **Contenido**: Red extendida de Aguascalientes con Expo Plaza adicional
- **Uso**: Archivo de ejemplo más completo para pruebas

### `vehicles.csv`

- **Propósito**: Plantilla de vehículos de ejemplo
- **Contenido**: 5 vehículos de diferentes tipos (Sedan, Truck, Compact)
- **Uso**: Archivo de ejemplo para entender el formato de vehículos

---

##  src/

Carpeta principal del código fuente.

---

###  src/controllers/

Controladores que manejan la lógica de negocio y coordinan entre modelos, vistas y servicios.

#### `BaseController.h`

- **Propósito**: Clase base abstracta para todos los controladores
- **Funcionalidad**: Proporciona métodos comunes para mostrar mensajes (éxito, error, info, cancelación)
- **Uso**: Heredada por NetworkController y VehicleController

#### `NetworkController.h` / `NetworkController.cpp`

- **Propósito**: Controlador para gestión de redes (nodos y aristas)
- **Funcionalidades**:
  - Cargar/guardar redes desde archivos
  - Agregar/eliminar nodos
  - Agregar/eliminar aristas (con selección de dirección)
  - Generar archivos semilla de redes
- **Uso**: Invocado desde el menú "Network Management"

#### `VehicleController.h` / `VehicleController.cpp`

- **Propósito**: Controlador para gestión de vehículos
- **Funcionalidades**:
  - Cargar/guardar vehículos desde archivos
  - Agregar/eliminar/buscar vehículos
  - Mover vehículos (usa algoritmo Dijkstra)
  - Mostrar historial de movimientos
  - Mostrar estadísticas de la tabla hash
- **Uso**: Invocado desde el menú "Vehicle Management"

---

###  src/models/

Modelos de datos y estructuras principales del programa.

#### `Edge.h`

- **Propósito**: Estructura de datos para representar una arista en el grafo
- **Contenido**: Nodo destino, peso (distancia/tiempo), puntero al siguiente edge (lista enlazada)
- **Uso**: Utilizada por Graph para implementar listas de adyacencia

#### `Node.h`

- **Propósito**: Estructura de datos para representar un nodo en el grafo
- **Contenido**: ID, nombre, lista de adyacencia (edges), estado activo
- **Uso**: Utilizada por Graph para almacenar nodos de la red

#### `Vehicle.h`

- **Propósito**: Estructuras para vehículos y movimientos
- **Contenido**:
  - `Vehicle`: ID, placa, tipo, nodo actual, nodo destino, estado activo
  - `Movement`: Registro de movimiento con ID vehículo, destino, estado, tiempo, razón de fallo
- **Uso**: Utilizada por HashTable para almacenar vehículos

#### `Graph.h` / `Graph.cpp`

- **Propósito**: Implementación del grafo dirigido ponderado (red de calles)
- **Funcionalidades**:
  - CRUD de nodos y aristas
  - Carga/guardado desde archivos CSV
  - Visualización (lista de adyacencia y matriz)
  - Auto-guardado cuando se carga un archivo
  - Validaciones de integridad
- **Estructura de datos**: Array estático de nodos (MAX_NODES=50) con listas de adyacencia
- **Uso**: Instancia global `cityNetwork` en main.cpp

#### `HashTable.h` / `HashTable.cpp`

- **Propósito**: Tabla hash para almacenar y gestionar vehículos
- **Funcionalidades**:
  - CRUD de vehículos con función hash (módulo 101)
  - Resolución de colisiones por sondeo lineal
  - Carga/guardado desde archivos CSV
  - Registro de movimientos en archivo .movements.csv
  - Estadísticas de la tabla (factor de carga, colisiones, etc.)
- **Estructura de datos**: Array estático de vehículos (HASH_SIZE=101, número primo)
- **Uso**: Instancia global `vehicleRegistry` en main.cpp

---

###  src/services/

Servicios reutilizables que encapsulan funcionalidades específicas.

#### `FileService.h` / `FileService.cpp`

- **Propósito**: Servicio centralizado para operaciones de archivos
- **Funcionalidades**:
  - Sanitización de nombres de archivo (seguridad)
  - Carga/guardado de redes y vehículos
  - Generación de archivos semilla
  - Construcción de rutas (data/ y seeds/)
  - Validación de existencia de archivos
- **Uso**: Utilizado por controladores para todas las operaciones de I/O

#### `MessageService.h` / `MessageService.cpp`

- **Propósito**: Servicio para mostrar mensajes consistentes con colores
- **Funcionalidades**:
  - Mensajes de error, éxito, advertencia, info
  - Títulos y encabezados de sección
  - Mensajes de estado (cargando, guardando, procesando)
  - Divisores y separadores
- **Uso**: Utilizado en toda la aplicación para feedback al usuario

#### `UIService.h` / `UIService.cpp`

- **Propósito**: Servicio para componentes interactivos de UI
- **Funcionalidades**:
  - Selector genérico con navegación por teclado
  - Diálogos de confirmación (Sí/No)
  - Tablas de información y comparación
  - Indicadores de progreso
  - Espera de tecla
- **Uso**: Utilizado por SelectionService y controladores

#### `ValidationService.h` / `ValidationService.cpp`

- **Propósito**: Servicio para validación de entradas
- **Funcionalidades**:
  - Validación de nombres de nodos, pesos, placas, nombres de archivo
  - Validación de rangos (enteros y decimales)
  - Detección de caracteres inválidos
  - Almacenamiento de último error
- **Uso**: Puede ser utilizado por controladores para validar datos (actualmente no implementado completamente)

#### `SelectionService.h` / `SelectionService.cpp`

- **Propósito**: Servicio para selecciones interactivas complejas
- **Funcionalidades**:
  - Selección de nodos con tabla paginada
  - Selección de vehículos con tabla paginada
  - Selección de pares de nodos (origen-destino)
  - Selección de dirección de arista (bidireccional, forward, reverse)
  - Selección de tipo de vehículo
- **Uso**: Utilizado extensivamente por controladores para todas las selecciones

---

###  src/views/

Vistas para presentación de datos (no incluidas en los archivos leídos, pero mencionadas en CMakeLists.txt).

#### `MenuView.cpp` / `MenuItem.h`

- **Propósito**: Sistema de menús jerárquicos navegables
- **Funcionalidad**: Menú principal y submenús con navegación por teclado
- **Uso**: Implementa toda la interfaz de menús del programa

#### `NetworkView.cpp`

- **Propósito**: Visualización de redes (lista de adyacencia y matriz)
- **Funcionalidad**: Formatea y muestra la estructura del grafo
- **Uso**: Invocado desde Graph::showAdjacencyList() y showAdjacencyMatrix()

#### `VehicleView.cpp`

- **Propósito**: Visualización de vehículos
- **Funcionalidad**: Muestra tabla de todos los vehículos registrados
- **Uso**: Invocado desde HashTable::showAllVehicles()

---

### Algoritmos (src/)

#### `Algorithms.h`

- **Propósito**: Declaraciones de algoritmos de grafos y estructuras de resultados
- **Contenido**:
  - `PathResult`: Resultado de búsqueda de camino (encontrado, distancia, ruta, tiempo)
  - `TraversalResult`: Resultado de recorrido (nodos visitados, pasos, completado)
  - Declaraciones de dijkstra(), bfs(), dfs()
  - Funciones de visualización de resultados
- **Uso**: Incluido por controladores y archivos de algoritmos

#### `Dijkstra.cpp`

- **Propósito**: Implementación del algoritmo de Dijkstra para camino más corto
- **Funcionalidad**:
  - Encuentra el camino más corto entre dos nodos
  - Calcula distancia total y tiempo de viaje (asume 60 km/h)
  - Visualización paso a paso con animación (puede cancelarse con ESC)
  - Reconstrucción del camino desde nodo destino
- **Uso**: Invocado desde "Find Shortest Path" y "Move Vehicle"

#### `BFS.cpp`

- **Propósito**: Implementación de Breadth-First Search (búsqueda en anchura)
- **Funcionalidad**:
  - Recorre el grafo nivel por nivel desde un nodo inicial
  - Visualización paso a paso con cola y estados de nodos
  - Puede cancelarse con ESC
- **Uso**: Invocado desde "Breadth-First Search" en menú de análisis

#### `DFS.cpp`

- **Propósito**: Implementación de Depth-First Search (búsqueda en profundidad)
- **Funcionalidad**:
  - Recorre el grafo explorando lo más profundo posible en cada rama
  - Visualización paso a paso con pila y estados de nodos
  - Puede cancelarse con ESC
- **Uso**: Invocado desde "Depth-First Search" en menú de análisis

---

##  utils/

Utilidades y funciones auxiliares reutilizables.

### `colors.h`

- **Propósito**: Definiciones de códigos ANSI para colores en consola
- **Contenido**: RESET, BOLD, RED, GREEN, YELLOW, CYAN, GRAY
- **Uso**: Incluido en toda la aplicación para colorear salida

### `fileUtils.h`

- **Propósito**: Utilidades para manejo de nombres de archivo
- **Funcionalidad**:
  - `sanitizeFilename()`: Limpia nombres de archivo (elimina caracteres peligrosos, path traversal)
  - `getDataPath()`: Construye ruta a data/
  - `getSeedPath()`: Construye ruta a seeds/
- **Uso**: Utilizado por FileService (funcionalidad migrada)

### `inputUtils.h`

- **Propósito**: Sistema robusto de entrada con detección de ESC
- **Funcionalidad**:
  - `readInputWithEsc()`: Lectura de entrada carácter por carácter con soporte ESC
  - `getStringInput()`, `getIntInput()`, `getDoubleInput()`: Entradas tipadas con validaciónhInput()`: Ejecuta operación solo si entrada no fue cancelada
  - Funciones legacy para compatibilidad
- **Uso**: Utilizado en toda la aplicación para entrada de usuario

### `keyUtils.h`

- **Propósito**: Utilidades para detección de teclas
- **Funcionalidad**:
  - `isEscPressed()`: Detecta si se presionó ESC (no bloqueante)
  - `sleepWithEscCheck()`: Pausa con posibilidad de cancelar con ESC
- **Uso**: Utilizado en algoritmos para animaciones cancelables

### `tableUtils.h`

- **Propósito**: Tabla interactiva paginada con navegación
- **Funcionalidad**:
  - `InteractivePaginatedTable`: Clase para mostrar datos en tabla navegable
  - Navegación con WASD o flechas
  - Paginación automática
  - Entrada directa de ID
  - Soporte para 2-3 columnas
- **Uso**: Utilizado por SelectionService para todas las selecciones

---

##  Archivos raíz

### `main.cpp`

- **Propósito**: Punto de entrada del programa
- **Funcionalidad**:
  - Inicializa instancias globales (cityNetwork, vehicleRegistry)
  - Crea controladores (NetworkController, VehicleController)
  - Construye sistema de menús jerárquicos
  - Define funciones de menú (algunas delegadas a controladores, otras locales)
  - Ejecuta bucle principal del menú
- **Estructura**:
  - Variables globales: Graph, HashTable, controladores, servicios
  - Funciones de menú: generateVehicleSeedFile, showAdjacencyList/Matrix, algoritmos, gestión de vehículos
  - main(): Construcción de menús y ejecución
- **Uso**: Compilado como ejecutable principal

### `CMakeLists.txt`

- **Propósito**: Configuración de compilación con CMake
- **Contenido**:
  - Proyecto: MenuSystem v1.0
  - Estándar: C++20
  - Archivos fuente: main.cpp + todos los .cpp de src/
  - Directorios de inclusión: raíz, src/, src/models/, src/controllers/, src/views/, src/services/
  - Flags de compilación: /W4 (MSVC) o -Wall -Wextra -pedantic (GCC/Clang)
- **Uso**: Ejecutar con `cmake -B build -S .` y `cmake --build build`

### `run.bat`

- **Propósito**: Script de compilación y ejecución automatizada (Windows)
- **Funcionalidad**:
  - Mata procesos previos del ejecutable
  - Limpia ejecutable anterior
  - Configura proyecto con CMake (MinGW Makefiles)
  - Compila proyecto
  - Ejecuta el ejecutable generado
  - Manejo de errores en cada paso
- **Uso**: Ejecutar `run.bat` desde línea de comandos

### `.gitignore`

- **Propósito**: Especifica archivos/carpetas ignorados por Git
- **Contenido**: build/, docs/ (nota: docs/ existe pero está en .gitignore)
- **Uso**: Evita subir archivos generados al repositorio

---

## Resumen de Dependencias

```
main.cpp
├── controllers/ (NetworkController, VehicleController)
│   ├── models/ (Graph, HashTable)
│   ├── services/ (FileService, MessageService, SelectionService)
│   └── utils/ (inputUtils, colors)
├── models/ (Graph, HashTable, Node, Edge, Vehicle)
│   ├── views/ (NetworkView, VehicleView)
│   └── utils/ (colors)
├── services/ (FileService, MessageService, UIService, SelectionService, ValidationService)
│   ├── models/ (Graph, HashTable)
│   └── utils/ (colors, tableUtils, inputUtils)
├── views/ (MenuView, MenuItem, NetworkView, VehicleView)
├── algorithms/ (Dijkstra, BFS, DFS, Algorithms.h)
│   ├── models/ (Graph)
│   └── utils/ (colors, keyUtils)
└── utils/ (colors, fileUtils, inputUtils, keyUtils, tableUtils)
```

