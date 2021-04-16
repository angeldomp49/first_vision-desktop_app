
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



Para agregar glew despues que se descarga debe colocarse el archivo .dll en la carpeta C:Windows\System32
La carpeta del archivo .lib propiedades de la soluci�n -> Vinculador -> general -> directorios de bibliotecas adicionales 
El archivo .lib en propiedades de la soluci�n -> Vinculador -> entrada -> Dependencias adicionales
El archivo .h en la carpeta dentro del proyecto en donde est�n los archivos .h como con glfw



importante: seleccionar el perfil de 32 bits o x86 "NO X64", incluir las librerias User32.lib, Gdi32.lib, Shell32.lib, glew32s.lib "NOTE LA S AL FINAL"
y por �ltimo glfw.lib, esto en las dependencias adicionales.



En el caso del ejemplo del libro LearnOpenGL al colocar la version minima y maxima de opengl y el perfile core, el programa dejo de funcionar
por lo que se retir�



referencia para el ejercicio del triangulo: 

# Shape #
La clase Shape se encarga de gestionar los recursos necesarios para crear una figura, recibe los puntos y los inidices que apuntan a los puntos
también aspectos como la creación de buffers y elementos de buffer.

# Shader #

Se encarga de aspectos de la creación de un shader como la lectura del archivo de código fuente GSLS y su compilación

# ShaderProgram # 

Crea un programa para agregar shaders