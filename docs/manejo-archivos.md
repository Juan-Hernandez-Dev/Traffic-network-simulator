# Sistema de Gestión de Archivos

## Descripción General

El sistema utiliza dos directorios separados para la gestión de archivos:

- `data/` - Archivos de trabajo del usuario (almacenamiento de historial)
- `seeds/` - Archivos de plantilla/muestra para configuración rápida

## Seguridad de Rutas de Archivos

### Sanitización Automática

Todas las entradas del usuario para nombres de archivos se sanitizan automáticamente para prevenir problemas de seguridad:

1. **Prevención de Recorrido de Directorios**

   - Elimina patrones `../` y `./`
   - Bloquea separadores de rutas (`/` y `\`)
   - Previene acceso a directorios padre

2. **Manejo de Extensiones**

   - El usuario ingresa el nombre de archivo SIN extensión
   - El sistema agrega automáticamente `.csv`
   - Cualquier extensión existente se elimina

3. **Filtrado de Caracteres**
   - Elimina caracteres peligrosos: `: * ? " < > |`
   - Recorta espacios en blanco
   - Garantiza nombres de archivo limpios y seguros

### Ejemplos

**Entrada del Usuario** → **Ruta Real**

- `red` → `data/red.csv`
- `../secret` → `data/secret.csv`
- `folder/file` → `data/folderfile.csv`
- `network.txt` → `data/network.csv`
- `my network` → `data/my network.csv`

## Comportamiento de Cargar Red

### Comportamiento Anterior (Problema)

- Cargar un archivo AGREGABA nodos a la red existente
- Las adiciones manuales persistían después de cargar
- Podía crear datos duplicados o mezclados

### Comportamiento Actual (Corregido)

- Cargar un archivo LIMPIA toda la red primero
- Garantiza que los datos cargados coincidan exactamente con el archivo
- Previene corrupción de datos por fuentes mezcladas

## Comportamiento de Guardar Red

### Validación

- No se puede guardar una red vacía
- Solicita al usuario el nombre del archivo (sin extensión)
- Guarda automáticamente en el directorio `data/`
- Preserva los pesos exactos de la entrada del usuario

### Formato de Archivo

```csv
# NODES
N;0;UAA
N;1;Plaza_Patria

# EDGES
E;0;1;3.5
```

## Generación de Archivos Semilla

### Propósito

- Crear redes de muestra para pruebas
- Proporcionar plantillas para nuevos usuarios
- Separar de los datos de trabajo

### Uso

1. Ir a: Gestión de Red Vial → Generar Archivo Semilla
2. Ingresar nombre de archivo (ej., `aguascalientes`)
3. Archivo creado en: `seeds/aguascalientes.csv`
4. Cargarlo usando: Cargar Red → `aguascalientes`

### Contenido Semilla Predeterminado

- 6 nodos (UAA, Plaza Patria, Centro Histórico, etc.)
- 9 aristas con pesos realistas
- Listo para usar en prueba de algoritmos

## Estructura de Directorios

```
project/
├── data/           # Archivos de trabajo del usuario (git-ignored recomendado)
│   ├── red.csv
│   ├── network1.csv
│   └── backup.csv
├── seeds/          # Archivos de plantilla (pueden ser commiteados a git)
│   ├── aguascalientes.csv
│   └── sample.csv
└── docs/
    └── file-management.md
```

## Mejores Prácticas

1. **Usar Semillas para Plantillas**

   - Generar archivos semilla para escenarios comunes
   - Compartir semillas con miembros del equipo
   - Mantener semillas en control de versiones

2. **Usar Data para Trabajo**

   - Guardar tus redes de trabajo en data/
   - Agregar data/ a .gitignore
   - Respaldar redes importantes regularmente

3. **Convenciones de Nombres de Archivo**

   - Usar nombres descriptivos: `city_center`, `highway_network`
   - Evitar caracteres especiales
   - No es necesario agregar la extensión `.csv`

4. **Cargar Archivos**
   - Siempre verificar el conteo de nodos después de cargar
   - Revisar lista de adyacencia para confirmar datos correctos
   - Recordar: cargar REEMPLAZA la red actual

## Notas de Seguridad

- Todas las operaciones de archivos están restringidas a los directorios del proyecto
- No se puede acceder a archivos del sistema o directorios padre
- La validación de entrada previene ataques de inyección de rutas
- Las extensiones de archivo son obligatorias (solo CSV)

## Manejo de Entrada

### Soporte de Cancelación con ESC

Todas las operaciones de archivos soportan cancelación con la tecla ESC:

- **Cargar Red**: Presionar ESC al ingresar el nombre de archivo para cancelar
- **Guardar Red**: Presionar ESC al ingresar el nombre de archivo para cancelar
- **Generar Semilla**: Presionar ESC al ingresar el nombre de archivo para cancelar

El sistema utiliza el patrón de envoltorio de entrada para un manejo limpio de cancelación. Ver `docs/input-wrapper-guide.md` para detalles técnicos.

### Experiencia del Usuario

```
Ingrese nombre de archivo (sin extensión): [Usuario escribe]
[Usuario presiona ESC]
Operación cancelada.
[Regresa al menú]
```

Sin operaciones parciales o estado corrupto - la cancelación es limpia e inmediata.
