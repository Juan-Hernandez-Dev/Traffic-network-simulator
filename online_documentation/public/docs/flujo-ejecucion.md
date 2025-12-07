# Flujo de Ejecución del Programa

Este documento explica el flujo general del programa y qué archivos son invocados según las acciones del usuario.

---

##  Inicio del Programa

### 1. Compilación y Ejecución

**Archivos involucrados**: `run.bat`, `CMakeLists.txt`

```
Usuario ejecuta: run.bat
├── CMakeLists.txt → Configura proyecto (lista de archivos, includes, flags)
├── cmake → Genera archivos de compilación
├── cmake --build → Compila todos los .cpp
└── build/menu_app.exe → Ejecuta el programa
```

### 2. Inicialización (main.cpp)

**Archivo**: `main.cpp`

```cpp
// Orden de inicialización:
1. Graph cityNetwork;              // Red de calles vacía
2. HashTable vehicleRegistry;      // Registro de vehículos vacío
3. NetworkController* networkController = new NetworkController(cityNetwork);
4. VehicleController* vehicleController = new VehicleController(vehicleRegistry, cityNetwork);
5. SelectionService, MessageService, FileService (instancias estáticas)
```

### 3. Construcción de Menús (main.cpp)

**Archivo**: `main.cpp`

```
MenuView mainMenu
├── [1] Network Management (roadNetworkMenu)
├── [2] Vehicle Management (vehicleMenu)
├── [3] Network Visualization (visualizationMenu)
├── [4] Network Analysis (algorithmsMenu)
└── [5] Exit
```

### 4. Bucle Principal

**Archivo**: `main.cpp` → `views/MenuView.cpp`

```
mainMenu.run() → Muestra menú y espera entrada del usuario
```

---

##  Flujos por Opción de Menú

---

##  1. Network Management

### 1.1 Load Network

**Flujo de archivos**:

```
main.cpp → NetworkController::handleLoadNetwork()
├── utils/inputUtils.h → getStringInput() [solicita nombre de archivo]
├── services/MessageService → showTitle()
├── services/FileService → loadNetwork()
│   ├── utils/fileUtils.h → sanitizeFilename() [limpia nombre]
│   ├── utils/fileUtils.h → getDataPath() [construye "data/nombre.csv"]
│   └── models/Graph → loadFromFile()
│       ├── Abre archivo CSV
│       ├── Lee líneas N;id;nombre → addNode()
│       ├── Lee líneas E;origen;destino;peso → addEdge()
│       └── Actualiza nextId
└── services/MessageService → showSuccess() o showError()
```

**Archivos de datos**: `data/*.csv`

---

### 1.2 Save Network

**Flujo de archivos**:

```
main.cpp → NetworkController::handleSaveNetwork()
├── utils/inputUtils.h → getStringInput() [solicita nombre de archivo]
├── services/MessageService → showTitle()
├── services/FileService → saveNetwork()
│   ├── utils/fileUtils.h → sanitizeFilename()
│   ├── utils/fileUtils.h → getDataPath()
│   └── models/Graph → saveToFile()
│       ├── Escribe "# NODES"
│       ├── Escribe líneas N;id;nombre
│       ├── Escribe "# EDGES"
│       └── Escribe líneas E;origen;destino;peso
└── services/MessageService → showSuccess()
```

**Archivos de datos**: `data/*.csv` (creado/actualizado)

---

### 1.3 Add Node

**Flujo de archivos**:

```
main.cpp → NetworkController::handleAddNode()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getStringInput() [solicita nombre del nodo]
├── models/Graph → addNodeAuto()
│   ├── Asigna ID automático (nextId)
│   ├── Busca slot libre en array nodes[]
│   ├── Crea nodo con id, name, adjacencyList=nullptr
│   ├── Incrementa nodeCount y nextId
│   └── Llama autoSave() → guarda a archivo actual si existe
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `Graph::nodes[]`, archivo actual si fue cargado

---

### 1.4 Add Edge

**Flujo de archivos**:

```
main.cpp → NetworkController::handleAddEdge()
├── services/MessageService → showTitle()
├── services/SelectionService → selectNodePair()
│   ├── utils/tableUtils.h → InteractivePaginatedTable [selección de origen]
│   │   └── Muestra tabla con ID, Name, Connections
│   └── utils/tableUtils.h → InteractivePaginatedTable [selección de destino]
├── services/SelectionService → selectEdgeDirection()
│   ├── services/UIService → Muestra tabla de confirmación
│   └── Usuario elige: Bidirectional / Forward / Reverse
├── utils/inputUtils.h → getDoubleInput() [solicita peso]
├── models/Graph → addEdge() [una o dos veces según dirección]
│   ├── Crea nuevo Edge(destino, peso)
│   ├── Inserta al inicio de adjacencyList
│   └── Llama autoSave()
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `Graph::nodes[].adjacencyList`, archivo actual

---

### 1.5 Remove Node

**Flujo de archivos**:

```
main.cpp → NetworkController::handleRemoveNode()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getIntInput() [solicita ID del nodo]
├── models/Graph → removeNode()
│   ├── Busca nodo por ID
│   ├── Elimina todas las aristas que apuntan a este nodo (recorre todos los nodos)
│   ├── Elimina lista de adyacencia del nodo (clearEdges)
│   ├── Marca nodo como inactivo
│   ├── Decrementa nodeCount
│   └── Llama autoSave()
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `Graph::nodes[]`, archivo actual

---

### 1.6 Remove Edge

**Flujo de archivos**:

```
main.cpp → NetworkController::handleRemoveEdge()
├── services/MessageService → showTitle()
├── services/SelectionService → selectNodePair() [allowSame=true]
│   ├── Selección de nodo origen
│   └── Selección de nodo destino
├── Muestra tabla de confirmación con origen y destino
├── utils/inputUtils.h → Confirmación (y/n)
├── models/Graph → removeEdge()
│   ├── Busca edge en adjacencyList del nodo origen
│   ├── Elimina edge de la lista enlazada
│   └── Llama autoSave()
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `Graph::nodes[].adjacencyList`, archivo actual

---

### 1.7 Generate Seed File

**Flujo de archivos**:

```
main.cpp → NetworkController::handleGenerateSeed()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getStringInput() [solicita nombre]
├── services/FileService → generateNetworkSeed()
│   ├── utils/fileUtils.h → sanitizeFilename()
│   ├── utils/fileUtils.h → getSeedPath() [construye "seeds/nombre.csv"]
│   └── Escribe archivo con red de ejemplo (6 nodos, 9 aristas)
└── services/MessageService → showSuccess()
```

**Archivos creados**: `seeds/*.csv`

---

##  2. Vehicle Management

### 2.1 Load Vehicles

**Flujo de archivos**:

```
main.cpp → VehicleController::handleLoadVehicles()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getStringInput() [solicita nombre de archivo]
├── services/FileService → loadVehicles()
│   ├── utils/fileUtils.h → sanitizeFilename()
│   ├── utils/fileUtils.h → getDataPath()
│   └── models/HashTable → loadFromFile()
│       ├── Abre archivo CSV
│       ├── Lee líneas V;id;placa;tipo;nodoActual;nodoDestino
│       ├── Para cada vehículo: addVehicle()
│       │   ├── Calcula índice con hashFunction(id) = id % 101
│       │   ├── Resuelve colisiones con sondeo lineal
│       │   └── Inserta en table[index]
│       └── Actualiza nextId
└── services/MessageService → showSuccess()
```

**Archivos de datos**: `data/*.csv`

---

### 2.2 Save Vehicles

**Flujo de archivos**:

```
main.cpp → VehicleController::handleSaveVehicles()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getStringInput() [solicita nombre de archivo]
├── services/FileService → saveVehicles()
│   ├── utils/fileUtils.h → sanitizeFilename()
│   ├── utils/fileUtils.h → getDataPath()
│   └── models/HashTable → saveToFile()
│       ├── Escribe "# VEHICLES"
│       └── Escribe líneas V;id;placa;tipo;nodoActual;nodoDestino
└── services/MessageService → showSuccess()
```

**Archivos de datos**: `data/*.csv` (creado/actualizado)

---

### 2.3 Add Vehicle

**Flujo de archivos**:

```
main.cpp → VehicleController::handleAddVehicle()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getValidString() [solicita placa]
├── services/SelectionService → selectVehicleType()
│   └── services/UIService → showSelector() [Sedan, Compact, Truck]
├── services/SelectionService → selectNode() [ubicación actual]
│   └── utils/tableUtils.h → InteractivePaginatedTable
├── models/HashTable → addVehicleAuto()
│   ├── Asigna ID automático (nextId)
│   ├── Calcula índice con hashFunction(nextId)
│   ├── Resuelve colisiones si es necesario
│   ├── Inserta vehículo en table[index]
│   ├── Incrementa vehicleCount y nextId
│   └── Llama autoSave()
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `HashTable::table[]`, archivo actual

---

### 2.4 Move Vehicle (Uses Dijkstra)

**Flujo de archivos**:

```
main.cpp → VehicleController::handleMoveVehicle()
├── services/MessageService → showTitle()
├── services/SelectionService → selectVehicle()
│   └── utils/tableUtils.h → InteractivePaginatedTable [muestra vehículos]
├── models/HashTable → searchVehicle() [obtiene puntero al vehículo]
├── services/SelectionService → selectNode() [selecciona destino]
├── src/Dijkstra.cpp → dijkstra() [calcula camino más corto]
│   ├── Inicializa dist[], prev[], visited[]
│   ├── dist[origen] = 0
│   ├── Bucle principal:
│   │   ├── Encuentra nodo no visitado con menor distancia
│   │   ├── Marca como visitado
│   │   ├── Actualiza distancias de vecinos
│   │   └── utils/keyUtils.h → sleepWithEscCheck() [animación]
│   ├── Reconstruye camino desde destino usando prev[]
│   └── Retorna PathResult{found, totalDistance, path, travelTime}
├── Si encontrado:
│   ├── Actualiza vehicle->currentNodeId = destId
│   ├── models/HashTable → logMovement() [escribe a data/.movements.csv]
│   │   └── Formato: vehicleId;destNodeId;status;travelTime;failReason
│   └── src/Algorithms.h → displayPath() [muestra resultado]
└── Si no encontrado:
    ├── models/HashTable → logMovement() [status="failed"]
    └── services/MessageService → showError()
```

**Archivos modificados**:

- `HashTable::table[]` (currentNodeId actualizado)
- `data/.movements.csv` (log agregado)
- Archivo actual de vehículos (autoSave)

---

### 2.5 Search Vehicle

**Flujo de archivos**:

```
main.cpp → VehicleController::handleSearchVehicle()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getIntInput() [solicita ID]
├── models/HashTable → searchVehicle()
│   ├── Calcula índice con hashFunction(id)
│   ├── Sondeo lineal hasta encontrar o slot vacío
│   └── Retorna puntero a Vehicle o nullptr
└── Muestra información del vehículo o error
```

**Estructuras consultadas**: `HashTable::table[]`

---

### 2.6 Remove Vehicle

**Flujo de archivos**:

```
main.cpp → VehicleController::handleRemoveVehicle()
├── services/MessageService → showTitle()
├── utils/inputUtils.h → getIntInput() [solicita ID]
├── models/HashTable → removeVehicle()
│   ├── Busca vehículo con hashFunction + sondeo lineal
│   ├── Marca vehicle.active = false
│   ├── Decrementa vehicleCount
│   └── Llama autoSave()
└── services/MessageService → showSuccess()
```

**Estructuras modificadas**: `HashTable::table[]`, archivo actual

---

### 2.7 Show All Vehicles

**Flujo de archivos**:

```
main.cpp → VehicleController::handleShowAll()
└── models/HashTable → showAllVehicles()
    └── views/VehicleView → showAllVehicles()
        ├── Recorre table[] buscando vehicles activos
        └── Muestra tabla con ID, Plate, Type, Current Node, Destination
```

**Estructuras consultadas**: `HashTable::table[]`, `Graph::nodes[]`

---

### 2.8 Show Movement History

**Flujo de archivos**:

```
main.cpp → VehicleController::handleShowMovementHistory()
└── models/HashTable → showMovementHistory()
    ├── Abre data/.movements.csv
    ├── Lee líneas: vehicleId;destNodeId;status;travelTime;failReason
    └── Muestra tabla con historial completo
```

**Archivos consultados**: `data/.movements.csv`

---

### 2.9 Show Hash Info

**Flujo de archivos**:

```
main.cpp → VehicleController::handleShowHashInfo()
└── models/HashTable → showHashInfo()
    ├── Calcula estadísticas:
    │   ├── usedSlots (slots con vehicle.active o id != -1)
    │   ├── loadFactor = vehicleCount / HASH_SIZE
    │   ├── availableCapacity = HASH_SIZE - vehicleCount
    │   ├── usagePercent = vehicleCount / HASH_SIZE * 100
    │   └── collisions = usedSlots - vehicleCount
    └── Muestra tabla con métricas y estados
```

**Estructuras consultadas**: `HashTable::table[]`

---

### 2.10 Generate Vehicle Seed File

**Flujo de archivos**:

```
main.cpp → generateVehicleSeedFile()
├── services/MessageService → showTitle()
├── services/FileService → generateVehicleSeed()
│   ├── utils/fileUtils.h → sanitizeFilename()
│   ├── utils/fileUtils.h → getSeedPath()
│   └── Escribe archivo con 3 vehículos de ejemplo
└── services/MessageService → showSuccess()
```

**Archivos creados**: `seeds/*.csv`

---

##  3. Network Visualization

### 3.1 Show Adjacency List

**Flujo de archivos**:

```
main.cpp → showAdjacencyList()
└── models/Graph → showAdjacencyList()
    └── views/NetworkView → showAdjacencyList()
        ├── Recorre nodes[] activos
        ├── Para cada nodo, recorre su adjacencyList
        └── Muestra: [ID] Name -> [destID] destName (weight)
```

**Estructuras consultadas**: `Graph::nodes[]`, `Edge` (listas enlazadas)

---

### 3.2 Show Adjacency Matrix

**Flujo de archivos**:

```
main.cpp → showAdjacencyMatrix()
└── models/Graph → showAdjacencyMatrix()
    └── views/NetworkView → showAdjacencyMatrix()
        ├── Construye matriz nodeCount x nodeCount
        ├── Inicializa con 0 (sin conexión)
        ├── Recorre adjacencyList de cada nodo y llena pesos
        └── Muestra matriz con IDs en filas/columnas
```

**Estructuras consultadas**: `Graph::nodes[]`, `Edge` (listas enlazadas)

---

##  4. Network Analysis (Manual)

### 4.1 Find Shortest Path

**Flujo de archivos**:

```
main.cpp → findShortestPath()
├── services/MessageService → showTitle()
├── services/SelectionService → selectNodePair()
│   ├── Selección de nodo origen
│   └── Selección de nodo destino
├── src/Dijkstra.cpp → dijkstra(cityNetwork, sourceId, destId, verbose=true)
│   ├── [Mismo flujo que en Move Vehicle]
│   └── Retorna PathResult
└── src/Algorithms.h → displayPath()
    ├── Muestra si se encontró camino
    ├── Muestra distancia total y tiempo de viaje
    └── Muestra ruta: [ID] Name ---> [ID] Name ---> ...
```

**Estructuras consultadas**: `Graph::nodes[]`, `Edge`

---

### 4.2 Breadth-First Search

**Flujo de archivos**:

```
main.cpp → breadthFirstSearch()
├── services/MessageService → showTitle()
├── services/SelectionService → selectNode() [nodo inicial]
├── src/BFS.cpp → bfs(cityNetwork, startId, verbose=true)
│   ├── Inicializa visited[], queue
│   ├── queue.push(startId), visited[startId] = true
│   ├── Bucle mientras queue no vacía:
│   │   ├── current = queue.front(), queue.pop()
│   │   ├── Agrega current a result.visitedNodes
│   │   ├── Muestra estado actual (nodo visitado, cola, tabla de estados)
│   │   ├── utils/keyUtils.h → sleepWithEscCheck() [animación]
│   │   ├── Recorre adjacencyList de current
│   │   └── Agrega vecinos no visitados a queue
│   └── Retorna TraversalResult{visitedNodes, steps, completed}
└── src/Algorithms.h → displayTraversal()
    └── Muestra orden de visita: 1. [ID] Name, 2. [ID] Name, ...
```

**Estructuras consultadas**: `Graph::nodes[]`, `Edge`

---

### 4.3 Depth-First Search

**Flujo de archivos**:

```
main.cpp → depthFirstSearch()
├── services/MessageService → showTitle()
├── services/SelectionService → selectNode() [nodo inicial]
├── src/DFS.cpp → dfs(cityNetwork, startId, verbose=true)
│   ├── Inicializa visited[], stack
│   ├── stack.push(startId)
│   ├── Bucle mientras stack no vacía:
│   │   ├── current = stack.top(), stack.pop()
│   │   ├── Si ya visitado, continuar
│   │   ├── visited[current] = true
│   │   ├── Agrega current a result.visitedNodes
│   │   ├── Muestra estado actual (nodo visitado, pila, tabla de estados)
│   │   ├── utils/keyUtils.h → sleepWithEscCheck() [animación]
│   │   ├── Recorre adjacencyList de current
│   │   └── Agrega vecinos no visitados a stack (en orden inverso)
│   └── Retorna TraversalResult{visitedNodes, steps, completed}
└── src/Algorithms.h → displayTraversal()
    └── Muestra orden de visita
```

**Estructuras consultadas**: `Graph::nodes[]`, `Edge`

---

##  5. Exit

**Flujo de archivos**:

```
main.cpp → exitAction()
├── Muestra mensaje "Exiting application..."
└── exit(0) → Termina programa
```

**Limpieza automática**:

- Destructores de Graph y HashTable liberan memoria de listas enlazadas
- Controladores son eliminados (delete)

---

##  Resumen de Archivos de Datos

### Archivos Leídos

- `data/*.csv` - Redes y vehículos guardados por el usuario
- `seeds/*.csv` - Plantillas de ejemplo

### Archivos Escritos

- `data/*.csv` - Redes y vehículos guardados (Save Network/Vehicles)
- `data/*.csv` - Auto-guardado cuando se carga un archivo y se modifica
- `data/.movements.csv` - Log de movimientos de vehículos (append)
- `seeds/*.csv` - Archivos semilla generados (Generate Seed File)

### Formato de Archivos CSV

**Red (Network)**:

```
# NODES
N;id;nombre
N;0;UAA
N;1;Plaza_Patria

# EDGES
E;origen;destino;peso
E;0;1;3.5
E;1;0;3.5
```

**Vehículos (Vehicles)**:

```
# VEHICLES
V;id;placa;tipo;nodoActual;nodoDestino
V;0;ABC-123;Sedan;0;-1
V;1;XYZ-789;Truck;1;2
```

**Movimientos (Movements)**:

```
vehicleId;destNodeId;status;travelTime;failReason
0;5;success;12.5;
1;10;failed;0;No path found
```

---

##  Flujo de Auto-Guardado

Cuando se carga un archivo (Load Network o Load Vehicles), el programa habilita auto-guardado:

```
1. Usuario carga archivo: data/mi_red.csv
2. Graph::currentFile = "data/mi_red.csv"
3. Usuario agrega nodo
4. Graph::addNodeAuto() → autoSave()
5. autoSave() escribe a currentFile automáticamente
```

Esto asegura que los cambios se persistan sin necesidad de "Save" manual.

---

##  Flujo de Interfaz de Usuario

### Entrada de Datos

```
utils/inputUtils.h
├── getStringInput() → Lee carácter por carácter, detecta ESC
├── getIntInput() → Filtra solo números, detecta ESC
└── getDoubleInput() → Filtra números y punto, detecta ESC
```

### Selección Interactiva

```
utils/tableUtils.h → InteractivePaginatedTable
├── Muestra tabla con datos
├── Navegación: W/S o Up/Down (cambiar selección)
├── Navegación: A/D o Left/Right (cambiar página)
├── Entrada directa: 0-9 (ingresar ID)
├── Enter → Confirmar selección
└── ESC → Cancelar
```

### Animaciones de Algoritmos

```
src/Dijkstra.cpp, BFS.cpp, DFS.cpp
├── Bucle principal del algoritmo
├── system("cls") → Limpia pantalla
├── Muestra estado actual (nodo visitado, distancias, etc.)
├── utils/keyUtils.h → sleepWithEscCheck(500ms)
│   ├── Pausa 500ms en intervalos de 50ms
│   └── Detecta ESC en cada intervalo
└── Si ESC presionado → Aborta algoritmo
```

---

##  Patrón de Diseño General

```
Usuario interactúa con → MenuView (views/)
                           ↓
                    Invoca función en main.cpp
                           ↓
                    Delega a Controller (controllers/)
                           ↓
                    Controller usa Services (services/)
                           ├── FileService (I/O)
                           ├── MessageService (feedback)
                           ├── SelectionService (selecciones)
                           └── UIService (componentes UI)
                           ↓
                    Controller modifica Models (models/)
                           ├── Graph (red)
                           └── HashTable (vehículos)
                           ↓
                    Models usan Views para mostrar (views/)
                           ├── NetworkView
                           └── VehicleView
                           ↓
                    Todo usa Utils (utils/)
                           ├── colors.h (colores)
                           ├── inputUtils.h (entrada)
                           ├── tableUtils.h (tablas)
                           ├── keyUtils.h (teclas)
                           └── fileUtils.h (archivos)
```

Este patrón separa responsabilidades y hace el código mantenible y extensible.

