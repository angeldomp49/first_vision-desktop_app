/*
Esta es una guia del proceso de configuraci�n de la libreria glfw para el manejo de OpenGL.

Lo primero a tomar en cuenta es que debemos descargar glfw desde su p�gina glfw.org luego
copiar el archivo glfw3.h y el glfw3.lib dentro del proyecto,
luego en las propiedades de la soluci�n en "C/C++" -> general -> directorio de inclusiones adicionales
agregar la carpeta en el cual se encuentra el archivo .h
luego en propiedades de la soluci�n -> Vinculador -> general -> directorios de bibliotecas adicionales 
agregar la carpeta en el cual se encuentra el archivo .lib
luego en propiedades de la soluci�n -> Vinculador -> entrada -> Dependencias adicionales
agregar los archivos adicionales en este caso el archivo glfw3.lib con su extensi�n y si no es reconocido por el sistema colocar
su ruta absoluta
tambi�n agregar opengl32.lib esta sin su ruta absoluta ya que debe estar incluida en las librerias por defecto de vs2019
copiar el codigo de ejemplo de la pagina de glfw.org
*/