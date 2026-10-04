# wxlib app template

Plantilla mínima para crear aplicaciones de escritorio con wxWidgets y `wxlib`.
Incluye el arranque de `wxApp`, una clase `AppProject final : public Project`,
un menú y una pestaña inicial. El nombre de la aplicación se toma del comando
`project(...)` de CMake.

## Convertir esta carpeta en un repositorio plantilla

1. Copia **el contenido de esta carpeta** a la raíz de un repositorio nuevo,
   por ejemplo `wxlib-app-template`. No copies el repositorio `APP_Systems`
   entero ni su carpeta `.git`.
2. Sube ese repositorio a GitHub.
3. En GitHub, activa **Settings → Template repository**.

Esta plantilla no contiene el submódulo `wxlib`. Se añade a cada repositorio
nuevo con el script de inicialización para que GitHub no pierda la referencia
al submódulo al crear un repositorio desde la plantilla.

## Crear una aplicación nueva

1. En GitHub, elige **Use this template → Create a new repository**.
2. Clona el repositorio nuevo y entra en su carpeta.
3. Ejecuta en PowerShell:

   ```powershell
   .\scripts\initialize.ps1 -Name MiNuevaApp
   git add CMakeLists.txt .gitmodules seconds/wxlib
   git commit -m "Initialize app and add wxlib"
   ```

   El nombre debe empezar por una letra y contener solo letras, números o
   guiones bajos. La clase C++ se llama siempre `AppProject`, por lo que no
   hace falta renombrar los archivos de código.

4. Configura CMake indicando dónde está `wxWidgetsConfig.cmake` en ese equipo:

   ```powershell
   cmake -S . -B build -DwxWidgets_DIR="C:/ruta/a/wxWidgets/lib/cmake/wxWidgets"
   cmake --build build --config Debug
   ```

   Abre también la carpeta en VS Code con CMake Tools si prefieres configurar
   y compilar desde el editor.

Cuando alguien clone una aplicación ya creada, debe recuperar el submódulo:

```powershell
git clone --recurse-submodules git@github.com:andrelorenzo/MiNuevaApp.git
```

## Dónde empezar a programar

- `src/main.cpp`: ventana principal y ciclo de vida de wxWidgets.
- `src/app_project.hpp` y `src/app_project.cpp`: interfaz, menús y eventos.
- `CMakeLists.txt`: archivos fuente y dependencias nuevas.

`project_.create(root_, 0)` no inicia el temporizador de `Project`. Si la
aplicación necesita una tarea periódica, cambia `0` por el intervalo en
milisegundos e implementa `timer()` en `AppProject`.

La plantilla no incluye icono. Si añades uno, puedes usar `appIcon()` de
`wxlib`, que busca el recurso `APP_ICON` de Windows o `assets/app.ico` junto
al ejecutable.
