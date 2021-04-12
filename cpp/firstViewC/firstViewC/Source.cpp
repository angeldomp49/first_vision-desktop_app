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