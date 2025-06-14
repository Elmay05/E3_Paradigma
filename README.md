# E3_Paradigma
A01712114 - Omar Emilio Casillas Alday

# Descripción
La idea de este programa es simular la descarga de varios archivos de diferentes tamaños al mismo tiempo, sacar cuanto tarda en descargar y a que velocidad la descargó.
Importante mencionar qeu esto solo es una simulación del comportamiento que tendría un sistema al descargar muchos archivos.
Esto es importante ya que lo pensé como una parte de un tester para probar en comportamiento de una aplicación o sistema bajo muchas tareas en paralelo, de igual manera esta podría extenderse a herramientas que analizan el rendimiento de sistemas de archivos.

# Modelos
Mi programa primero define una función que simula la descarga de un archivo, entra el nombre del archivo y su supuesto peso, mide el tiempo que tomó la descarga, calcula la velocidad y muestra los resultados.
En el main se crea la lista de archivos con los supuestos tamaños, se crea 1 thread para cada archivo para trabajarlos de manera simultanea y espera a que los threads se terminen para acabar el programa.

<img src="https://github.com/user-attachments/assets/f5790380-00bc-4f1d-aad7-f6cb52de3d02" alt="Imagen de WhatsApp" width="400">


Respecto al paradigma, en este inicia el programa donde se crea el vector de thread, para cada uno de los archivos se crea un thread y se manda a hacer la función en estos, estos se ejecutan de manera concurrente y se terminan de ejecutar en el momento en el que todos los threads terminan con la función 

<img src="https://github.com/user-attachments/assets/f246c346-52c5-4f3b-b462-0f201dc631d3" alt="Imagen de WhatsApp 2" width="400">

Para este proyecto ocupamos el paradigma concurrente, este segun códigofacilito "El poder realizar múltiples cosas en el mismo tiempo, pero, no específicamente en paralelo", esa podría realizarse de manera paralela si el sistema lo permite, pero esto no lo controlo desde el codigo, la concurrencia no garantiza que las descargas se ejecuten al mismo tiempo, a comparacion del paralelo que este lo hace con varios nucleos.
https://codigofacilito.com/articulos/programacion-concurrente

# Implementación
Primero que nada incluimos las librerias adecuadas, iostream para entradas y salidas estandar, threads para poder utilizar los hilos para la concurrencia, chrono para trabajar con los tiempos y duraciones y vector para guardar los archivos y threads en vectores
```c++
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
```
Ahora podemos empezar creando nuestra función que simulará las descargas.
Tenemos una variable start que guardará el tiempo en el que entra a la función.
Ahora hacemos la simulación de espera, multiplicamos 500 (ya que al menos debe tardar algo en los archivos pequeños), por el supuesto tamaño del documento por 100 (tambien es un numero arbitrario para la simulación).
Tenemos la variable end donde se guarda el tiempo en el qeu se termina la espera de la descarga del archivo.
Una variable duración tipo double porque es mas precisa que un float, en esta guardamos la diferencia del tiempo final con el tiempo inicial.
Una variable speed donde guardaremos la velocidad a la que se descargó el archivo.
Por ultimo imprimimos los datos de descarga.
```c++
void simula_descarga(const string &nombre_doc, int size_doc){
    //auto sirve 
    //esta linea guarda el tiempo actual, ocupando un reloj muy presiso de la libreria chrono
    auto start = chrono::high_resolution_clock::now();
    //se pone un tiempo arbitrario para simular que hasta lo mas pequeño se tarda algo de tiempo en descargarse
    //igual el 100 fue elegido de manera arbitraria por MB
    this_thread::sleep_for(chrono::milliseconds(500 + size_doc * 100));

    //se usa auto ya que el tipo de este "chrono" es muy largo, y así evitamos ecribir mucho
    // este es el tipo real: std::chrono::time_point<std::chrono::high_resolution_clock>
    //esta linea calcula cuanto tiempo pasó en verdad
    auto end = chrono::high_resolution_clock::now();
    //Usamos double porque es mas preciso qeu float
    chrono::duration<double> duracion = end - start;
    //.count() extrae el valor numerico del objeto chrono (duración)
    double speed = size_doc/duracion.count();
    //imprimimos resumen 
    std::cout<<nombre_doc<<" se descargo correctamente en "<<duracion.count()<<"s ("<<speed<<"MB/s)"<<endl;

}
```
Por ultimo tenemos nuestro main donde creamos un vector de threads y otro donde guardemos el titulo y el peso del archivo, y comenzamos con nuestro for, el cual recorre cada elemento del vector de archivos y crea un thread en el que se ejecutará la función y así para cada elemento de docs.
Al final solo hacemos un join para esperar a que todos los threads se terminen de ejecutar.
```c++
int main(){
    //creamos el vector de threads
    vector<thread> threads;
    //creamos el vector con nuestros documentos y su supuesto peso
    //un pair es una estructura que guarda 2 valores juntos, como "pequeño paquete", para mas datos se usa structure o class, igual si se ocupa nombres mas claros
    vector<pair<string, int>> docs = {
        {"Foto.jpg", 3},
        {"video.mp4", 34},
        {"Actividad_03", 18},
        {"prolog.pl", 15}
    };
    //Ponemos los threads a trabajar con la función de arriba
    for (int i=0; i<docs.size();i++){
        threads.emplace_back(simula_descarga, docs[i].first, docs[i].second);
    }
    //antes de acabar el programa esperamos a que todos los threads se terminen de ejecutar
    for (int i = 0; i < threads.size();i++){
        threads[i].join();
    }

    return 0;
}
```
# Pruebas
Para corroborar que se ejecuten de manera simultanea, hacemos la prueba cambiando el peso de los archivos, se espera que el que pesa menos, sin importar si está antes o despues en el vector, se espera que los primeros en salir sean los archivos que pesan menos.

Para poder correr el programa hay que hacerlo en un compilador de c++
Si decides hacerlo en cmd de WINDOWS tienes que poner "cd" + `<la dirección de tu carpeta donde tienes el archivo>`.
Despues ejecutas este comando
g++ descarga.cpp -o a.exe
Y ejecutas el programa escribiendo 
a.exe 

Primera iteración:

* {"Foto.jpg", 3}
* {"video.mp4", 34}
* {"Actividad_03", 18}
* {"prolog.pl", 15}
  
Se espera que salgan en este orden 
1. Foto.jpg
2. prolog.pl
3. Actividad_03
4. video.mp4
![Imagen con la primera iteración ](image.png)

Segunda iteración:
* {"Foto.jpg", 40}
* {"video.mp4", 5}
* {"Actividad_03", 20}
* {"prolog.pl", 2}
  
Se espera que salgan en este orden: 
1. prolog.pl
2. video.mp4
3. Actividad_03
4. Foto.jpg
![Imagen con la segunda iteración](image-1.png)

Tercera iteración:
* {"Foto.jpg", 4}
* {"video.mp4", 45}
* {"Actividad_03", 9}
* {"prolog.pl", 2}
* {"documento.pdf", 12}
* {"musica.mp3", 7}
* {"datos.csv", 10}
* {"presentacion.pptx", 25}
* {"backup.zip", 50}
* {"script.js", 3}

Se espera que salgan en este orden: 
1. prolog.pl
2. script.js
3. Foto.jpg
4. musica.mp3
5. Actividad_03
6. datos.csv
7. documento.pdf
8. presentación.pptx
9. video.mp4
10. backup.zip
![Imagen con la tercera iteración](image-2.png)

# Análisis
### Complejidad temporal
Para la simulación de la espera de tiempo, tiene una complejidad de O(n), donde n es el tamaño del archivo.
Gracias a los threads, la funcion para cada archivo se ejecuta de manera concurrente, el tiempo será casi igual al de la descarga mas lenta, dejandonos con la complejidad de O(n) (asumiendo que hay suficientes nucleos para cada thread, si no, la complejidad pasa a ser O(n*m) donde m es el numero de archivos)
### Otro paradigma 
Respecto a otras soluciones, le dije a Chat GPT que lo implementara el prolog, dejandome este codigo:
```prolog
% Regla para calcular el tiempo y la velocidad de descarga
% descarga(Nombre, Tamaño, Tiempo, Velocidad)
descarga(Nombre, Tam, Tiempo, Velocidad) :-
    Tiempo is (500 + Tam * 100) / 1000,
    Velocidad is Tam / Tiempo,
    format("~w se descargo correctamente en ~2f s (~2f MB/s)~n", [Nombre, Tiempo, Velocidad]).

% Predicado principal para ejecutar todas las descargas
descargas :-
    descarga("prolog.pl", 2, _, _),
    descarga("script.js", 3, _, _),
    descarga("video.mp4", 5, _, _),
    descarga("musica.mp3", 7, _, _),
    descarga("datos.csv", 10, _, _),
    descarga("documento.pdf", 12, _, _),
    descarga("Actividad_03", 20, _, _),
    descarga("presentacion.pptx", 25, _, _),
    descarga("Foto.jpg", 40, _, _),
    descarga("backup.zip", 50, _, _).
``` 
Este ocupa el paradigma logico, este paradigma no permite una ejecución paralela o concurrente como en c++ pero es util para la representar la lógica del problema mediante reglas.
En éste se simula como conjunto de echos y reglas, no existe un metodo para calcular el tiempo en prolog ni concurrencia, por ende todas las descargas se simulan de manera secuencial, cada una de éstas se evalua de manera independiente y el tiempo calculado es un estimado, la complejidad asintotica se estima por medio de los archivos a analizar, ya qeu cada llamada maneja operaciones matemáticas simples, por ello la complejidad es de O(n) siendo "n" la cantidad de archivos que se van a simular

De igual manera se le pidió qeu lo implementara en paradigma de scripting dejandonos el siguiente codigo en python:
```python
import time

# Lista de documentos como tuplas (nombre, tamaño en MB)
docs = [
    ("Foto.jpg", 4),
    ("video.mp4", 45),
    ("Actividad_03", 9),
    ("prolog.pl", 2),
    ("documento.pdf", 12),
    ("musica.mp3", 7),
    ("datos.csv", 10),
    ("presentacion.pptx", 25),
    ("backup.zip", 50),
    ("script.js", 3)
]

# Recorremos la lista y simulamos la descarga de cada uno
for nombre, tamaño in docs:
    inicio = time.perf_counter()
    time.sleep(0.5 + tamaño * 0.1)  # espera simulada: 500ms + 100ms por MB
    fin = time.perf_counter()
    duracion = fin - inicio
    velocidad = tamaño / duracion
    print(f"{nombre} se descargó correctamente en {duracion:.2f}s ({velocidad:.2f}MB/s)")
```
Al ocupar paradigma de scripting, todo se ejecuta en el cuerpo principal del script, usa solo un for, sleep y print en su implementación, está automatizada en orden y se entiende facilmente sin conocimiento de paradigmas complejos, tiene complejidad asintotica de O(n) siendo n la canidad de archivos qeu hay en el arreglo.
### Comparación 
La implementación en C++ con threads permite simular varias descargas de manera concurrente, creando un buen escenario y realista para la simulación de un speed tester de velocidad, esta es mas compleja pero mas cercana a la realidad gracias a los hilos y el temporizador, de igual manera ofrece un mayor nivel de control sobre el rendimiento y la interacción con el sistema.


Por otro lado, prolog es mas teórica y declarativa al manejar un paradigma logico, esto tiene como ventaja (como lo dice el nombre del paradigma) el poder representar la estructura logica del problema ya que se centra mas en "¿Qué se busca lograr?" que en como hacerlo, Sin embargo, presenta algunas limitaciones importantes para una simulación práctica, como la falta de recursos de concurrencia o temporizador real, impidiendonos replicar el comportamiento de descargas simultaneas.

En el tercer codigo, Python forma parte del paradigma de scripting, cuyo objetivo es resolver problemas de forma rápida y directa sin necesidad de estructuras complejas. La implementación es sencilla: la lista se define y los elementos y se inicializan mediante un ciclo for, todo desde el script principal, sin funciones externa. Puede usar esta opción para tareas automatizadas, pruebas rápidas o mantenimiento.

El paradigma concurrente se utiliza mas en momentos en los que se ocupa ejecutar múltiples tareas ayudando al mejoramiento del rendimiento, sobre todo el aplicaciones en el que el timepo es crucial, este te permite interacción directa con recursos del sistema.
Mientras que el paradigma logico se utiliza mas cuando lo qeu se busca la verificación de conocimiento, razonamiento automático o explorar y representar la logica de un problema sin preocuparse por el control del flujo, esta es ideal para prototipar soluciones o validar ideas.
En cambio, paradigma de scripting suele utilizarse mas en tareas de configuración o mantenimiento ya que se utiliza para problemas que se quieren resolver rapidamente sin tener que crear codigos complejos o aplicaciones enormes, buscan automatizar cualquier tarea que pudiera realizarse por medio del shell.


# Bibliografía
(S/f). Codigofacilito.com. Recuperado el 22 de mayo de 2025, de https://codigofacilito.com/articulos/programacion-concurrente
