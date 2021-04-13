/*
Esta es una guia del proceso de configuración de la libreria glfw para el manejo de OpenGL.

Lo primero a tomar en cuenta es que debemos descargar glfw desde su página glfw.org luego
copiar el archivo glfw3.h y el glfw3.lib dentro del proyecto,
luego en las propiedades de la solución en "C/C++" -> general -> directorio de inclusiones adicionales
agregar la carpeta en el cual se encuentra el archivo .h
luego en propiedades de la solución -> Vinculador -> general -> directorios de bibliotecas adicionales 
agregar la carpeta en el cual se encuentra el archivo .lib
luego en propiedades de la solución -> Vinculador -> entrada -> Dependencias adicionales
agregar los archivos adicionales en este caso el archivo glfw3.lib con su extensión y si no es reconocido por el sistema colocar
su ruta absoluta
también agregar opengl32.lib esta sin su ruta absoluta ya que debe estar incluida en las librerias por defecto de vs2019
copiar el codigo de ejemplo de la pagina de glfw.org
*/

/*
Para agregar glew despues que se descarga debe colocarse el archivo .dll en la carpeta C:Windows\System32
La carpeta del archivo .lib propiedades de la solución -> Vinculador -> general -> directorios de bibliotecas adicionales 
El archivo .lib en propiedades de la solución -> Vinculador -> entrada -> Dependencias adicionales
El archivo .h en la carpeta dentro del proyecto en donde están los archivos .h como con glfw
*/

/*
importante: seleccionar el perfil de 32 bits o x86 "NO X64", incluir las librerias User32.lib, Gdi32.lib, Shell32.lib, glew32s.lib "NOTE LA S AL FINAL"
y por último glfw.lib, esto en las dependencias adicionales.
*/

/*
En el caso del ejemplo del libro LearnOpenGL al colocar la version minima y maxima de opengl y el perfile core, el programa dejo de funcionar
por lo que se retiró
*/

/*
referencia para el ejercicio del triangulo: https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp
*/

/*

*/