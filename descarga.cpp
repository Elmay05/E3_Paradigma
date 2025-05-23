#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

//Funcion para simular descarga
//const para que no se pueda modificar dentro de la función 
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

int main(){
    //creamos el vector de threads
    vector<thread> threads;
    //creamos el vector con nuestros documentos y su supuesto peso
    //un pair es una estructura qeu guarda 2 valores juntos, como "pequeño paquete", para mas datos se usa structure o class, igual si se ocupa nombres mas claros
    vector<pair<string, int>> docs = {
        {"Foto.jpg", 4},
        {"video.mp4", 45},
        {"Actividad_03", 9},
        {"prolog.pl", 2},
        {"documento.pdf", 12},
        {"musica.mp3", 7},
        {"datos.csv", 10},
        {"presentacion.pptx", 25},
        {"backup.zip", 50},
        {"script.js", 3}
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