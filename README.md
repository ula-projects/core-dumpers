![ULA Letterhead](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSXElDjQaaj2Y2EYZLl7dD6p46m7cTohT-xMw&s)

# CoreDumpers

**Programacion 3**
**Prof. Alejandro Mujica**
**Estudiantes:**

- Nerio Balza
- Diego Osorio

## 📜 Acerca de CoreDumpers  

CoreDumpers es un proyecto de videojuego en **C++** utilizando **SFML 3.0**, donde los jugadores exploran un mundo circular dividido en bloques destructibles, con gravedad hacia el núcleo del planeta.

## ⚙️ Dependencias  

Antes de compilar el proyecto, asegúrate de tener instaladas las siguientes dependencias:

- **GCC** o **Clang** (compilador de C++)
- **SFML 3.0** (biblioteca multimedia)
- **Make** (para ejecutar el Makefile)
- **Dependencias de SFML** (puedes instalarlas con el gestor de paquetes de tu sistema)
- **Dependencias estándar de C++** (como `libstdc++` en Linux)

### 🔍 Instalación de dependencias  

#### **Linux (Debian/Ubuntu)**

```bash
sudo apt update
sudo apt install build-essential make
```

#### **Linux (Arch)**

```bash
sudo pacman -S gcc make
```

#### **Windows (MSYS2)**

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-sfml
```

#### **MacOS**

```bash
brew install sfml
```

## 🛠️ Compilación  

El proyecto incluye un **Makefile**, por lo que la compilación es sencilla. En la carpeta del proyecto solo ejecuta:

```bash
make
```

Esto generará el ejecutable en la carpeta del proyecto.

## 🚀 Ejecución  

Una vez compilado, puedes ejecutar el juego con:

```bash
./CoreDumpers
```

Si estás en **Windows**, usa:

```powershell
CoreDumpers.exe
```

## 📝 Notas adicionales  

Si tienes problemas con las dependencias, revisa los archivos `.so` o `.dll` faltantes con:

```bash
ldd ./CoreDumpers
```

Asegurate de instalar la version de SFML 3.0, Para más información sobre la instalación, visita [Visita SFML-Dev](https://www.sfml-dev.org/download/sfml/3.0.0/) y sigue el instructivo correspondiente a tu sistema operativo.

Si necesitas ayuda, ¡abre un _issue_ en el repositorio!
