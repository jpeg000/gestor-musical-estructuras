#include <iostream>
#include <limits>
using namespace std;

/*  Fecha de Inicio: 17/4/2025
    Integrantes:
    - Jose Pablo Avendaño Zúñiga
    - José Andres Villegas Murillo

    Descripción de Estructuras:

    Descripción de cada función:
*/
//Lista de canciones.
struct Canciones {
    string id; //ID de la canción.
    string titulo; // Título o nombre de la canción.
    int duracion; //Duración de la canción (en segundos).
    int year; //Año de lanzamiento de la canción.
    string idAlbum; //ID del album al que pertenece.
    string idArtista; //ID del artista al que pertenece.

    Canciones *siguiente; //Puntero a la siguiente canción.

    /* CONSTRUCTOR */
    Canciones(string idP, string tituloP, int duracionP, int yearP, string idAlbumP, string idArtistaP) {
        id = idP;
        titulo = tituloP;
        duracion = duracionP;
        year = yearP;
        idAlbum = idAlbumP;
        idArtista = idArtistaP;
        siguiente = NULL;
    }

};
//Lista de artistas
struct Artistas {
    string id; //ID del artista.
    string nombreArtistico; //Nombre artístico del artista.
    string nombreReal; //Nombre real del artista.
    string pais; //País del artista.
    string selloDiscografico; //El sello discográfico al que pertenece el artista.

    Artistas *siguiente, *anterior;  //Puntero al siguiente y al anterior artista.

    /* SUBLISTAS */
    struct Albumes *albumes; //Puntero que apunta a la sublista de albumes del artista.

    /* CONSTRUCTOR */
    Artistas(string idP, string nombreA, string nombreR, string paisP, string selloDisc) {
        id = idP;
        nombreArtistico = nombreA;
        nombreReal = nombreR;
        pais = paisP;
        selloDiscografico = selloDisc;
        siguiente = NULL;
        anterior = NULL;
        albumes = NULL;
    }
} *primerA; //Puntero cabeza.

//Lista de albumes.
struct Albumes {
    string id; //ID del album.
    string titulo; //Titulo o nombre del album.
    int year; //Año de lanzamiento del album.
    int numeroCanciones; //Numero de canciones del album.

    Albumes *siguiente; //Puntero al siguiente album.

    /* SUBLISTAS */
    struct Canciones *canciones; //Puntero a la sublista de canciones del arbol.

    /* CONSTRUCTOR */
    Albumes(string idP, string tituloP, int yearP, int numCanc) {
        id = idP;
        titulo = tituloP;
        year = yearP;
        numeroCanciones = numCanc;
        siguiente = NULL;
        canciones = NULL;
    }
};

//Lista de géneros musicales
struct GenerosMusicales {
    string id; //ID del género
    string nombre; //Nombre del género musical.
    string descripcion; //Descripción del género musical.

    GenerosMusicales *siguiente; //Puntero al siguiente género musical.

    /* SUBLISTAS */
    struct Canciones *canciones; //Puntero a la sublista de canciones que pertenecen a un género musical.

    /* CONSTRUCTOR */
    GenerosMusicales(string idP, string nombreP, string desc) {
        id = idP;
        nombre = nombreP;
        descripcion = desc;
        siguiente = NULL;
        canciones = NULL;
    }
} *primerG; //Puntero cabeza.

//Lista de playlist.
struct Playlist {
    string id; //ID de la playlist.
    string nombre; //Nombre de la playlist.
    string creador; //Creador de la playlist.
    int fecha; //Fecha de creación de la playlist.

    Playlist *siguiente; //Puntero a la siguiente playlist.

    /* SUBLISTAS */
    struct Canciones *canciones; //Puntero a la sublista de canciones de una playlist.

    /* CONSTRUCTOR */
    Playlist(string idP, string nombreP, string creadorP, int fechaP) {
        id = idP;
        nombre = nombreP;
        creador = creadorP;
        fecha = fechaP;
        siguiente = NULL;
        canciones = NULL;
    }
} *primerP; //Puntero cabeza.

//Lista doble circular de sellos discográficos.
struct SellosDiscograficos {
    string id; //ID del sello discográfico.
    string nombre; //Nombre del sello discográfico.
    string pais; //Pais del sello discográfico.
    int year; //Año de fundación del sello discográfico.

    SellosDiscograficos *siguiente, *anterior; //Puntero al siguiente sello y puntero al sello anterior.

    /* SUBLISTAS */
    struct enlaceSellosArtistas *sublistaArtista;

    /* CONSTRUCTOR */
    SellosDiscograficos(string idP, string nombreP, string paisP, int yearP) {
        id = idP;
        nombre = nombreP;
        pais = paisP;
        year = yearP;
        siguiente = NULL;
        anterior = NULL;
        sublistaArtista = NULL;
    }
} *primerS; //Puntero cabeza.

struct enlaceSellosArtistas { //Lista de enlace a los artistas pertenecientes a el sello discográfico.

    enlaceSellosArtistas *siguiente; //Puntero siguiente.
    struct Artistas *enlace; //Puntero a la lista de artistas.

    /* CONSTRUCTOR */
    enlaceSellosArtistas(struct Artistas *a) {
        siguiente = NULL;
        enlace = a;
    }
};

/*
=========
AUXILIARES
=========
*/

/*
Función para buscar si existe un artista específico.
Recibe como parámetro el ID del artista que se desea buscar.
*/
struct Artistas* buscarArtistas(string ide){
    if (primerA == NULL){ //Si la lista está vacía, no hay artistas registrados.
        return NULL;
    }
    struct Artistas* temp = primerA; //Puntero temporal para recorrer la lista de artistas.
    while (temp != NULL){ //Mientras el puntero no sea nulo.
        if (temp->id == ide){ 
            return temp; //Si se encontró el artista, retornar el nodo donde se encuentra.
        } else {
            temp = temp -> siguiente; //Si no es el artista esperado, pasar al siguiente.
        }
    }
    return NULL; //No se encontró el artista.
}
/*
Busca un artista en la lista de artistas por su nombre artístico.

Recibe como parámetro el nombre artístico del artista que se desea buscar. 
Si el artista con el nombre especificado existe en la lista, se retorna el puntero a ese artista.
Si no se encuentra el artista, se retorna NULL.

*/
struct Artistas* buscarArtistasPorNombre(string nombre) {
    struct Artistas* temp = primerA;  // Inicializa el puntero a la cabeza de la lista.
    while (temp != NULL) {  // Recorre la lista mientras no se llegue al final.
        if (temp->nombreArtistico == nombre) {  // Si el nombre artístico coincide.
            return temp;  // Retorna el puntero al artista encontrado.
        }
        temp = temp->siguiente;  // Avanza al siguiente artista.
    }
    return NULL;  // Si no se encuentra el artista, retorna NULL.
}
/*
Buscar un sello discográfico específico en la lista circular.
Recibe como parámetro el ID del sello a buscar.
Si encuentra el sello, devuelve un puntero al nodo correspondiente.
Si no lo encuentra, devuelve NULL.
*/
struct SellosDiscograficos* buscarSellos(string ide) {
    if (primerS == NULL) { // Si la lista está vacía, no hay sellos registrados.
        return NULL;
    }
    struct SellosDiscograficos* temp = primerS; // Puntero para recorrer la lista circular.
    do { // Recorrer la lista hasta regresar al primer elemento.
        if (temp->id == ide) { // Si encuentra el sello, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo.
    } while (temp != primerS); // Mientras no regrese al nodo inicial.
    return NULL; // El sello no está en la lista.
}
/*
Buscar un sello discográfico específico en la lista circular por nombre.
Recibe como parámetro el nombre del sello a buscar.
Si encuentra el sello, devuelve un puntero al nodo correspondiente.
Si no lo encuentra, devuelve NULL.
*/
struct SellosDiscograficos* buscarSelloPorNombre(string n) {
    if (primerS == NULL) { // Si la lista de sellos está vacía, retornar NULL.
        return NULL;
    }
    struct SellosDiscograficos* temp = primerS; // Puntero para recorrer la lista circular.
    do { // Recorrer la lista circular de sellos discográficos.
        if (temp->nombre == n) { // Si encuentra el nombre del sello, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo.
    } while (temp != primerS); // Mientras no se regrese al nodo inicial.
    return NULL; // El sello no está en la lista.
}

/*
Buscar un álbum específico en la lista de álbumes de un artista.
Recibe el ID del artista y el ID del álbum a buscar.
Si encuentra el álbum, devuelve un puntero al nodo correspondiente.
Si no lo encuentra o el artista no existe, devuelve NULL.
*/
struct Albumes* buscarAlbumes(string idArtista, string idAlbum) {
    struct Artistas* nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.
    if (nodoArtista == NULL) { // Si el artista no existe, retornar NULL.
        return NULL;
    }
    struct Albumes* temp = nodoArtista->albumes; // Puntero para recorrer la lista de álbumes.
    while (temp != NULL) { // Recorrer la lista de álbumes del artista.
        if (temp->id == idAlbum) { // Si encuentra el álbum, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar al siguiente álbum.
    }
    return NULL; // El álbum no está en la lista del artista.
}

/*
Buscar un género musical específico en la lista circular de géneros musicales.
Recibe como parámetro el ID del género a buscar.
Si encuentra el género, devuelve un puntero al nodo correspondiente.
Si no lo encuentra, devuelve NULL.
*/
struct GenerosMusicales* buscarGeneroMusical(string ide) {
    if (primerG == NULL) { // Si la lista de géneros está vacía, retornar NULL.
        return NULL;
    }
    GenerosMusicales* temp = primerG; // Puntero para recorrer la lista circular de géneros.
    do { // Recorrer la lista hasta regresar al primer elemento.
        if (temp->id == ide) { // Si encuentra el género, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo.
    } while (temp != primerG); // Mientras no regrese al nodo inicial.
    return NULL; // El género no está en la lista.
}
/*
Busca un género musical en la lista circular de géneros musicales por su nombre.
Recibe como parámetro el nombre del género que se desea buscar.
Si la lista está vacía, retorna NULL.
Si el género musical existe en la lista, retorna el puntero al nodo correspondiente.
Si el género musical no existe, retorna NULL.
La lista de géneros musicales se recorre de manera circular, es decir, se vuelve al primer nodo una vez que se llega al final de la lista.
*/
struct GenerosMusicales* buscarGeneroMusicalPorNombre(string nombreG) {
    // Verificar si la lista de géneros está vacía.
    if (primerG == NULL) {
        return NULL; // Si la lista está vacía, retornar NULL.
    }
    GenerosMusicales* temp = primerG; // Puntero para recorrer la lista circular de géneros.
    // Recorrer la lista hasta regresar al primer elemento.
    do {
        // Si se encuentra el género, retornar el nodo.
        if (temp->nombre == nombreG) {
            return temp;
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo.
    } while (temp != primerG); // Mientras no regrese al nodo inicial.

    return NULL; // El género no está en la lista.
}

/*
Buscar una canción específica dentro de un álbum de un artista.
Recibe el ID del artista, el ID del álbum y el ID de la canción a buscar.
Si encuentra la canción, devuelve un puntero al nodo correspondiente.
Si no lo encuentra, o el artista o el álbum no existen, devuelve NULL.
*/
struct Canciones* buscarCancion(string idArtista, string idAlbum, string idCancion) {
    struct Artistas* nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.
    if (nodoArtista == NULL) { // Si el artista no existe, retornar NULL.
        return NULL;
    }
    struct Albumes* nodoAlbum = nodoArtista->albumes; // Obtener la lista de álbumes del artista.
    if (nodoAlbum == NULL) { // Si el artista no tiene álbumes registrados, retornar NULL.
        return NULL;
    }
    struct Canciones* temp = nodoArtista->albumes->canciones; // Puntero para recorrer las canciones del álbum.
    while (temp != NULL) { // Recorrer la lista de canciones.
        if (temp->id == idCancion) { // Si encuentra la canción, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar a la siguiente canción.
    }
    return NULL; // La canción no está en el álbum del artista.
}

/*
Buscar una playlist específica en la lista de playlists.
Recibe como parámetro el ID de la playlist a buscar.
Si encuentra la playlist, devuelve un puntero al nodo correspondiente.
Si no lo encuentra, devuelve NULL.
*/
struct Playlist* buscarPlaylist(string ide) {
    if (primerP == NULL) { // Si la lista de playlists está vacía, retornar NULL.
        return NULL;
    }
    struct Playlist* temp = primerP; // Puntero para recorrer la lista de playlists.
    while (temp != NULL) { // Recorrer la lista de playlists.
        if (temp->id == ide) { // Si encuentra la playlist, retornar el nodo.
            return temp;
        }
        temp = temp->siguiente; // Avanzar a la siguiente playlist.
    }
    return NULL; // La playlist no está en la lista.
}

/*
Inserta un artista en un sello discográfico, vinculando al artista con el sello correspondiente.
Recibe como parámetros el ID del artista y el ID del sello discográfico.
Si el artista o el sello no existen, muestra un mensaje de error.
Si el artista ya está vinculado a ese sello, muestra un mensaje informando la duplicación.
Si el artista y el sello son válidos, se establece el enlace entre el artista y el sello discográfico.
*/
void insertarArtistaEnSello(string idArtista, string idSelloDisc) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.
    struct SellosDiscograficos *nodoSello = buscarSellos(idSelloDisc); // Buscar el sello por su ID.
    if (nodoArtista == NULL) { // Si el artista no existe, mostrar un mensaje de error.
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }
    if (nodoSello == NULL) { // Si el sello no existe, mostrar un mensaje de error.
        cout << "El sello discográfico ID " << idSelloDisc << " no está registrado." << endl;
        return;
    }
    enlaceSellosArtistas *temp = nodoSello->sublistaArtista; // Obtener la sublista de artistas del sello.
    while (temp != NULL) { // Recorrer la sublista para verificar si el artista ya está vinculado.
        if (temp->enlace->id == nodoArtista->id) {  // Si ya está vinculado al sello, mostrar mensaje.
            cout << "El artista ya está vinculado a este sello discográfico." << endl;
            return;
        }
        temp = temp->siguiente; // Continuar con el siguiente enlace en la sublista.
    }
    // Si no está vinculado, agregar al artista a la sublista de artistas del sello.
    enlaceSellosArtistas *enlace = new enlaceSellosArtistas(nodoArtista); 
    enlace->siguiente = nodoSello->sublistaArtista; // Apuntar al primer enlace actual.
    nodoSello->sublistaArtista = enlace; // Establecer el nuevo enlace como el primero en la lista.

    // Vincular el sello al artista.
    nodoArtista->selloDiscografico = nodoSello->nombre;

    cout << "El artista ha sido vinculado al sello discográfico correctamente." << endl;
}
/*
Elimina un artista de un sello discográfico.
Recibe como parámetros el ID del artista y el ID del sello discográfico.
Si el artista o el sello no existen, muestra un mensaje de error.
Si el artista está vinculado a ese sello, se elimina el vínculo y se ajustan las listas de artistas.
Si el artista no está vinculado a ese sello, muestra un mensaje informando la situación.
*/
void eliminarArtistaDeSello(string idArtista, string idSelloDisc) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.
    struct SellosDiscograficos *nodoSello = buscarSellos(idSelloDisc); // Buscar el sello por su ID.
    if (nodoArtista == NULL) { // Si el artista no existe, mostrar un mensaje de error.
        cout << "El artista con el ID " << idArtista << " no existe."<< endl;
        return;
    }

    if (nodoSello == NULL) { // Si el sello no existe, mostrar un mensaje de error.
        cout << "El sello discográfico ID " << idSelloDisc << " no está registrado."<< endl;
        return;
    }

    if (nodoArtista -> selloDiscografico != nodoSello -> nombre) { // Si el artista no está asociado al sello.
        cout << "El artista no esta asociado a ese sello discográfico." << endl;
        return;
    }
    struct enlaceSellosArtistas *actual = nodoSello -> sublistaArtista; // Obtener la sublista de artistas vinculados al sello.
    struct enlaceSellosArtistas *anterior = NULL; // Puntero para rastrear el nodo anterior.
    while (actual != NULL) { // Recorrer la sublista para encontrar al artista.
        if (actual -> enlace == nodoArtista) { // Si se encuentra al artista en la lista.
            if (anterior == NULL) { // Si el artista está al principio de la lista.
                nodoSello -> sublistaArtista = actual -> siguiente; // Actualizar la cabeza de la sublista.
            }
            else { // Si el artista está en cualquier otra posición.
                anterior -> siguiente = actual -> siguiente; // Saltar el nodo actual.
            }
            delete actual; // Liberar la memoria del nodo de enlace.
            nodoArtista -> selloDiscografico = ""; // Eliminar el vínculo del artista con el sello.
            cout << "El artista " << nodoArtista -> nombreArtistico <<
                " ha sido eliminado del Sello Artístico " << nodoSello -> nombre << "." << endl;
            return; // Salir de la función tras eliminar al artista.
        }
        anterior = actual; // Mover el puntero `anterior` al nodo actual.
        actual = actual -> siguiente; // Continuar con el siguiente nodo de la sublista.
    }

    cout << "El artista no está vinculado a este sello discográfico." << endl; // En caso de no encontrar al artista.
}
/*
=========
CANCIONES
=========
*/
/*
Inserta nuevas canciones en el álbum de un artista hasta alcanzar el número de canciones requerido para el álbum.
Recibe como parámetros el ID del artista y el ID del álbum. Luego, solicita al usuario los datos de cada canción (ID, título, duración y año).
Si el artista o el álbum no existen, muestra un mensaje de error.
Si la canción ya existe en el álbum, muestra un mensaje indicando que la canción ya está registrada.
Si la duración o el año de la canción es negativo, solicita nuevamente los datos hasta que sean válidos.
Las canciones se añaden al inicio de la lista de canciones del álbum.
*/ 


void insertarCancion(string idArtista, string idAlbum) {
    // Buscar el artista por su ID
    Artistas* nodoArtista = buscarArtistas(idArtista);
    // Buscar el álbum dentro del artista
    Albumes* nodoAlbum = buscarAlbumes(idArtista, idAlbum);

    // Verificar si el artista existe
    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    // Verificar si el álbum existe
    if (nodoAlbum == NULL) {
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    int cont = 0; // Inicialización correcta del contador
    string idCancion, titulo;
    int duracion, year;

    // Pedir canciones hasta alcanzar el número requerido en el álbum
    while (cont < nodoAlbum->numeroCanciones) {
        cout << "Ingrese el ID de la canción: " << endl;
        // Leer el ID de la canción, permitiendo espacios en blanco
        getline(cin >> ws, idCancion);

        // Verificar si la canción ya existe en el álbum
        Canciones* nodoCancion = buscarCancion(idArtista, idAlbum, idCancion);
        if (nodoCancion != NULL) {
            cout << "La canción con el ID " << idCancion << " ya existe en este álbum." << endl;
            continue; // Solicitar otra canción
        }

        // Pedir el título de la canción
        cout << "Ingrese el título de la canción: " << endl;
        // Leer el título, permitiendo espacios en blanco
        getline(cin >> ws, titulo);

        // Pedir la duración de la canción (solo números enteros positivos)
        cout << "Ingrese la duración de la canción (en segundos): " << endl;
        while (true) {
            cin >> duracion;
            if (cin.fail() || duracion < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada no válida. Ingrese un número entero no negativo: ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Pedir el año de la canción (solo números enteros positivos)
        cout << "Ingrese el año de la canción: " << endl;
        while (true) {
            cin >> year;
            if (cin.fail() || year < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada no válida. Ingrese un número entero no negativo: ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Crear un nuevo nodo para la canción
        Canciones* nuevaCancion = new Canciones(idCancion, titulo, duracion, year, idArtista, idAlbum);
        nuevaCancion->siguiente = nodoAlbum->canciones;
        nodoAlbum->canciones = nuevaCancion;

        cout << "La canción \"" << titulo << "\" fue agregada correctamente al álbum con ID " << idAlbum << "." << endl;

        // Incrementar el contador para la siguiente canción
        cont++;
    }
    cout << "¡Canciones agregadas exitosamente!"<<endl;
}



/*
Modifica el título de una canción existente dentro de un álbum de un artista.
Recibe como parámetros el ID del artista, el ID del álbum, el ID de la canción y el nuevo título.
Verifica si el artista y el álbum existen. Si alguno no existe, muestra un mensaje de error.
Verifica si la canción con el ID proporcionado existe en el álbum. Si no existe, muestra un mensaje de error.
Verifica que no haya otra canción con el mismo título en el mismo álbum antes de realizar la modificación.
Si la canción existe y no hay duplicados con el nuevo título, actualiza el título de la canción.
Si la modificación es exitosa, muestra un mensaje indicando el cambio de título realizado correctamente.
*/

void modificarTituloCancion(string idArtista, string idAlbum, string idCancion, string nuevoTitulo) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.
    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum); // Buscar el álbum dentro del artista.
    struct Canciones *nodoCancion = buscarCancion(idArtista, idAlbum, idCancion); // Buscar la canción por su ID.

    // Verificar que el artista exista.
    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    // Verificar que el álbum exista.
    if (nodoAlbum == NULL) {
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    // Verificar que la canción exista.
    if (nodoCancion == NULL) {
        cout << "La canción con el ID " << idCancion << " no existe." << endl;
        return;
    }

    // Verificar que no haya otra canción con el mismo título en el álbum.
    Canciones *temp = nodoAlbum->canciones;
    while (temp != NULL) {
        if (temp != nodoCancion && temp->titulo == nuevoTitulo) {
            cout << "Ya existe una canción con ese título en este álbum." << endl;
            return;
        }
        temp = temp->siguiente;
    }

    // Guardar el título antiguo y actualizar el nuevo título.
    string tituloAntiguo = nodoCancion->titulo;
    nodoCancion->titulo = nuevoTitulo;

    // Mensaje de éxito.
    cout << "El título de la canción " << tituloAntiguo << " ha sido cambiado por " << nuevoTitulo << " exitosamente." << endl;
}
/*
Elimina una canción de un álbum que pertenece a un artista.
Parámetros:
- idArtista: ID del artista al que pertenece el álbum.
- idAlbum: ID del álbum en el que se encuentra la canción.
- idCancion: ID de la canción a eliminar.
Si el artista, el álbum o la canción no existen, muestra un mensaje de error.
Si la canción es encontrada, la elimina de la lista de canciones del álbum y muestra un mensaje de confirmación.
*/
void eliminarCancion(string idArtista, string idAlbum, string idCancion) {
    Artistas* nodoArtista = buscarArtistas(idArtista); // Buscar el artista por ID.
    if (nodoArtista == NULL) { // Verificar si el artista no existe.
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    Albumes* nodoAlbum = buscarAlbumes(idArtista, idAlbum); // Buscar el álbum dentro del artista.
    if (nodoAlbum == NULL) { // Verificar si el álbum no existe.
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    Canciones* nodoCancion = buscarCancion(idArtista, idAlbum, idCancion); // Buscar la canción específica.
    if (nodoCancion == NULL) { // Verificar si la canción no existe.
        cout << "La canción con el ID " << idCancion << " no existe." << endl;
        return;
    }

    Canciones* actual = nodoAlbum->canciones;
    Canciones* anterior = NULL;

    while (actual != NULL) {
        // Si encuentra la canción a eliminar.
        if (actual->id == idCancion) {
            // Si la canción a eliminar es la primera de la lista.
            if (anterior == NULL) {
                nodoAlbum->canciones = actual->siguiente; // Actualizar el puntero a la siguiente canción.
            } else {
                anterior->siguiente = actual->siguiente; // Desvincular la canción de la lista.
            }

            delete actual; // Liberar la memoria de la canción eliminada.
            cout << "La canción con el ID " << idCancion << " se ha eliminado correctamente." << endl;
            return;
        }

        // Avanzar en la lista de canciones.
        anterior = actual;
        actual = actual->siguiente;
    }
}
/*
=========
ALBUMES
=========
*/

/*
Inserta un nuevo álbum al final de la lista de álbumes de un artista.
Recibe como parámetros el ID del artista, el ID del álbum, el título, el año de lanzamiento y el número de canciones.
Si el artista no existe, muestra un mensaje de error.
Si el álbum ya está registrado en el artista, muestra un mensaje de error.
Si el artista existe y el álbum no está registrado, lo agrega al final de la lista de álbumes.
*/
void insertarFinalAlbum(string idArtista, string idAlbum, string titulo, int year, int numCanciones) {

    Artistas* nodoArtista = buscarArtistas(idArtista); // Buscar el artista con el ID proporcionado.
    if (nodoArtista == NULL) { // Si el artista no existe, mostrar mensaje de error.
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }
    // Verificar si el álbum ya está registrado en el artista.
    if (buscarAlbumes(idArtista, idAlbum) != NULL) {
        cout << "El álbum ya está registrado en el artista." << endl;
        return;
    }

    // Crear el nuevo álbum.
    Albumes* nuevoAlbum = new Albumes(idAlbum, titulo, year, numCanciones);

    // Si el artista no tiene álbumes registrados, agregar el nuevo álbum como el primero.
    if (nodoArtista->albumes == NULL) {
        nodoArtista->albumes = nuevoAlbum;
    } else {
        // Recorrer la lista de álbumes hasta el último nodo.
        Albumes* temp = nodoArtista->albumes;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        // Insertar el nuevo álbum al final de la lista.
        temp->siguiente = nuevoAlbum;
    }

    // Confirmación de inserción exitosa.
    cout << "El álbum " << titulo << " se agregó exitosamente al artista " 
         << nodoArtista->nombreArtistico << "." << endl;
}

/*
Modifica el título de un álbum asociado a un artista.
Recibe como parámetros el ID del artista, el ID del álbum y el nuevo título.
Si el artista no existe, muestra un mensaje de error.
Si el álbum no existe, muestra un mensaje de error.
Si ya existe otro álbum con el mismo título para el artista, muestra un mensaje de error.
Si no hay conflictos, actualiza el título del álbum y muestra un mensaje de confirmación.
*/
void modificarTituloAlbum(string idArtista, string idAlbum, string tituloNuevo) {
    // Buscar el artista con el ID proporcionado.
    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    // Verificar si el artista no existe.
    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    // Buscar el álbum dentro de los álbumes del artista.
    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);

    // Verificar si el álbum no existe.
    if (nodoAlbum == NULL) {
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    // Verificar si ya existe un álbum con el mismo título para el artista.
    Albumes *temp = nodoArtista->albumes;
    while (temp != NULL) {
        if (temp != nodoAlbum && temp->titulo == tituloNuevo) {
            cout << "Ya existe un álbum con ese título para este artista." << endl;
            return;
        }
        temp = temp->siguiente;
    }

    // Actualizar el título del álbum.
    nodoAlbum->titulo = tituloNuevo;
    cout << "Se cambió el título del álbum correctamente." << endl;
}
/*
Elimina un álbum de la lista de álbumes de un artista y elimina todas las canciones asociadas a dicho álbum.
Recibe como parámetros el ID del artista y el ID del álbum a eliminar.
Si el artista o el álbum no existen, muestra un mensaje de error.
Si el álbum existe, elimina todas sus canciones y desvincula el álbum de la lista.
*/
void eliminarAlbum(string idArtista, string idAlbum) {
    Artistas* nodoArtista = buscarArtistas(idArtista); // Buscar el artista por su ID.

    if (nodoArtista == NULL) { // Verificar si el artista no existe.
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    Albumes* nodoAlbum = buscarAlbumes(idArtista, idAlbum); // Buscar el álbum por su ID.

    if (nodoAlbum == NULL) { // Verificar si el álbum no existe.
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    // Eliminar todas las canciones asociadas al álbum.
    Canciones* cancionActual = nodoAlbum->canciones;
    while (cancionActual != NULL) {
        string idCancion = cancionActual->id;
        cancionActual = cancionActual->siguiente;
        eliminarCancion(idArtista, idAlbum, idCancion); // Eliminar canción.
    }

    // Recorrer la lista de álbumes del artista para encontrar el álbum a eliminar.
    Albumes* actual = nodoArtista->albumes;
    Albumes* anterior = NULL;

    while (actual != NULL) {
        if (actual->id == idAlbum) { // Si encuentra el álbum a eliminar.
            if (anterior == NULL) { // Si es el primer álbum de la lista.
                nodoArtista->albumes = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual; // Liberar memoria del álbum eliminado.

            cout << "El álbum con el ID " << idAlbum << " y todas sus canciones se han eliminado exitosamente." << endl;
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}
/*
=========
ARTISTAS
=========
*/
/*
Inserta un artista en una lista ordenada alfabéticamente por su nombre artístico.
Recibe como parámetros el ID del artista, nombre artístico, nombre real, país y el nombre del sello discográfico.
Si el artista ya existe (por ID o nombre artístico), muestra un mensaje de error.
Si el sello no existe, muestra un mensaje de error.
El nuevo artista se inserta en la lista de artistas de forma ordenada alfabéticamente.
También se vincula el artista al sello discográfico proporcionado.
*/
void insertarArtistaOrdenAlfabeticamente(string id, string nombreArt, string nombreReal, string pais, string selloDisc) {
    // Verificar si el artista ya existe por ID.
    struct Artistas *existeArtistaPorId = buscarArtistas(id);
    if (existeArtistaPorId != NULL) {
        cout << "El artista con el ID " << id << " ya existe." << endl;
        return;
    }

    // Verificar si el artista ya existe por nombre artístico.
    struct Artistas *existeArtistaPorNombre = buscarArtistasPorNombre(nombreArt);
    if (existeArtistaPorNombre != NULL) {
        cout << "El artista con el nombre artístico " << nombreArt << " ya existe." << endl;
        return;
    }

    // Verificar si el sello discográfico existe.
    struct SellosDiscograficos *nodoSello = buscarSelloPorNombre(selloDisc);
    if (nodoSello == NULL) {
        cout << "El sello con el nombre " << selloDisc << " no existe." << endl;
        return;
    }

    // Crear el nuevo artista.
    struct Artistas *nuevoArtista = new Artistas(id, nombreArt, nombreReal, pais, selloDisc);

    // Si la lista de artistas está vacía, hacer que el nuevo artista sea el primero.
    if (primerA == NULL) {
        primerA = nuevoArtista;
        return;
    }

    // Si el nombre del nuevo artista es alfabéticamente menor que el primero, insertarlo al principio.
    if (nombreArt < primerA->nombreArtistico) {
        nuevoArtista->siguiente = primerA;
        primerA->anterior = nuevoArtista;
        primerA = nuevoArtista;
        return;
    }

    // Recorrer la lista para encontrar la posición correcta.
    Artistas *temp = primerA;
    while (temp->siguiente != NULL && temp->siguiente->nombreArtistico < nombreArt) {
        temp = temp->siguiente;
    }

    // Insertar el nuevo artista en la lista.
    nuevoArtista->siguiente = temp->siguiente;
    nuevoArtista->anterior = temp;

    if (temp->siguiente != NULL) { // Si no es el último nodo, actualizar el puntero del siguiente nodo.
        temp->siguiente->anterior = nuevoArtista;
    }
    temp->siguiente = nuevoArtista; // Enlazar el nuevo artista al nodo previo.

    // Vincular el nuevo artista al sello discográfico.
    insertarArtistaEnSello(id, nodoSello->id);
}
/*
Modifica el nombre artístico de un artista en la lista de artistas.
Recibe como parámetros el ID del artista y el nuevo nombre artístico.
Si el artista no existe, muestra un mensaje de error.
Si el nombre artístico ya está en uso por otro artista, muestra un mensaje de advertencia.
Si el nombre artístico actual del artista ya coincide con el nuevo nombre, muestra un mensaje indicando que no es necesario el cambio.
Si el nombre es válido, se actualiza el nombre artístico del artista con el nuevo valor proporcionado.
*/
void modificarNombreArtisticoDeArtista(string ide, string nombre) {
    Artistas* nodoArtista = buscarArtistas(ide); // Buscar el artista con el ID proporcionado.
    if (buscarArtistasPorNombre(nombre) != NULL) { // Verificar si el nuevo nombre ya está en uso.
        cout << "El nombre que se desea insertar ya está en uso por otro artista." << endl;
        return;
    }
    if (nodoArtista == NULL) { // Si el artista no se encuentra, mostrar un mensaje de error.
        cout << "El artista no existe." << endl;
        return;
    }
    if (nodoArtista->nombreArtistico == nombre) { // Verificar si el nombre ya coincide.
        cout << "El artista ya tiene este nombre artístico." << endl;
        return;
    }
    nodoArtista->nombreArtistico = nombre; // Actualizar el nombre artístico.
    cout << "Nombre artístico actualizado correctamente." << endl;
}

/*
Modifica el país de origen de un artista en la lista de artistas.
Recibe como parámetros el ID del artista y el nuevo país.
Si el artista no existe, muestra un mensaje de error.
Si el artista existe, se actualiza su país con el nuevo valor proporcionado.
*/
void modificarPaisDeArtista(string ide, string paisNuevo) {
    Artistas* nodoArtista = buscarArtistas(ide); // Buscar el artista con el ID proporcionado.
    if (nodoArtista == NULL) { // Si el artista no se encuentra, mostrar un mensaje de error.
        cout << "El artista no existe" << endl;
    } else { // Si el artista existe, actualizar el país.
        nodoArtista->pais = paisNuevo;
        cout << "País actualizado correctamente." << endl;
    }
}

/*
Modifica el sello discográfico asociado a un artista.
Recibe como parámetros el ID del artista y el ID del nuevo sello discográfico.
Si el artista no existe, muestra un mensaje de error.
Si el sello discográfico nuevo no existe, muestra un mensaje de error.
Si ambos existen, desvincula al artista del sello anterior y lo vincula al nuevo sello.
*/
void modificarSelloDiscograficoDeArtista(string idArtista, string idSelloNuevo) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista); // Buscar el artista por ID.
    struct SellosDiscograficos *nodoSelloNuevo = buscarSellos(idSelloNuevo); // Buscar el nuevo sello por ID.
    struct SellosDiscograficos *nodoSelloAnterior = buscarSelloPorNombre(nodoArtista->selloDiscografico); // Buscar el sello actual del artista.

    if (nodoArtista == NULL) { // Verificar si el artista no existe.
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    if (nodoSelloNuevo == NULL) { // Verificar si el nuevo sello no existe.
        cout << "El sello ID " << idSelloNuevo << " no existe." << endl;
        return;
    }

    // Eliminar el artista del sello anterior y vincularlo al nuevo sello.
    eliminarArtistaDeSello(idArtista, nodoSelloAnterior->id); 
    insertarArtistaEnSello(idArtista, idSelloNuevo); 

    cout << "El sello discográfico del artista " << nodoArtista->nombreArtistico << " se modificó exitosamente." << endl;
}
/*
Elimina un artista de la lista de artistas y desvincula su asociación con el sello discográfico.
Recibe como parámetro el ID del artista a eliminar.
Si el artista no existe, muestra un mensaje de error.
Si el artista existe:
- Elimina todos los álbumes asociados al artista.
- Desvincula al artista del sello discográfico.
- Elimina el nodo del artista de la lista y actualiza los punteros de los nodos adyacentes.
*/
void eliminarArtista(string ide) {
    Artistas* nodoArtista = buscarArtistas(ide); // Buscar el artista por ID.
    
    if (nodoArtista == NULL) { // Verificar si el artista no existe.
        cout << "El artista no existe" << endl;
        return;
    }

    // Eliminar todos los álbumes asociados al artista.
    Albumes* albumActual = nodoArtista->albumes;
    while (albumActual != NULL) {
        Albumes* siguienteAlbum = albumActual->siguiente;
        eliminarAlbum(ide, albumActual->id); // Eliminar el álbum.
        albumActual = siguienteAlbum;
    }

    // Desvincular el artista de su sello discográfico, si está vinculado.
    if (!nodoArtista->selloDiscografico.empty()) {
        SellosDiscograficos* sello = buscarSelloPorNombre(nodoArtista->selloDiscografico);
        if (sello != NULL) {
            eliminarArtistaDeSello(ide, sello->id);
        }
    }

    // Actualizar el enlace del nodo anterior (si existe).
    if (nodoArtista->anterior != NULL) {
        nodoArtista->anterior->siguiente = nodoArtista->siguiente;
    } else {
        primerA = nodoArtista->siguiente; // Si no hay anterior, actualizar el puntero de la cabeza.
    }

    // Actualizar el enlace del nodo siguiente (si existe).
    if (nodoArtista->siguiente != NULL) {
        nodoArtista->siguiente->anterior = nodoArtista->anterior;
    }

    delete nodoArtista; // Eliminar el nodo del artista.
    cout << "Artista eliminado correctamente." << endl;
}

/*
=========
SELLO DISCOGRAFICO
=========
*/
/*
Insertar un nuevo sello discográfico en la lista circular doblemente enlazada.
Recibe el ID, el nombre, el país y el año de fundación del sello.
Si el nombre ya existe, muestra un mensaje de error y no realiza la inserción.
Si se inserta correctamente, muestra un mensaje de confirmación.
*/
void insertarSellosDiscograficos(string id, string nombre, string pais, int anoFund) {
    if (buscarSellos(id) != NULL) { // Verificar si el ID del sello ya existe.
        cout << "El ID de este sello ya existe" << endl;
        return;
    }
    if (buscarSelloPorNombre(nombre) != NULL) { // Verificar si el nombre del sello ya existe.
        cout << "El nombre de este sello ya existe" << endl;
        return;
    }
    SellosDiscograficos* newSello = new SellosDiscograficos(id, nombre, pais, anoFund); // Crear el nuevo sello.
    if (primerS == NULL) { // Si la lista está vacía, el nuevo sello será el primero.
        primerS = newSello;
        newSello->siguiente = newSello;
        newSello->anterior = newSello;
    } else { // Si la lista no está vacía, insertar al final de la lista circular.
        SellosDiscograficos* temp = primerS->anterior; // Último nodo de la lista.
        temp->siguiente = newSello;
        newSello->anterior = temp;
        newSello->siguiente = primerS;
        primerS->anterior = newSello;
    }
    cout << "Sello discográfico agregado correctamente." << endl;
}
/*
Modificar el nombre de un sello discográfico dado su ID.
Recibe el ID del sello y el nuevo nombre deseado.
Si el ID no existe, muestra un mensaje de error.
Si el nuevo nombre ya está registrado, también muestra un mensaje de error.
Si la modificación es exitosa, muestra un mensaje de confirmación.
*/
void modificarNombredeSello(string ide, string newNombre) {
    SellosDiscograficos* SelloDisc = buscarSellos(ide); // Buscar el sello por su ID.
    if (SelloDisc == NULL) { // Si el sello no existe, mostrar mensaje y salir.
        cout << "El sello discográfico no existe" << endl;
        return;
    }
    if (SelloDisc->nombre == newNombre) { // Verificar si el nuevo nombre ya es el actual.
        cout << "El nombre ya está registrado para este sello" << endl;
        return;
    }
    if (buscarSelloPorNombre(newNombre) != NULL) { // Verificar si el nuevo nombre ya existe en otro sello.
        cout << "El nuevo nombre que se desea insertar ya existe" << endl;
        return;
    }
    SelloDisc->nombre = newNombre; // Modificar el nombre del sello.
    cout << "Nombre del sello discográfico modificado correctamente" << endl;
}
/*
Modificar el país de un sello discográfico dado su ID.
Recibe el ID del sello y el nuevo país deseado.
Si el sello no existe, muestra un mensaje de error.
Si el nuevo país es igual al actual, muestra un mensaje indicando que no hubo cambios.
Si la modificación es exitosa, muestra un mensaje de confirmación.
*/
void modificarPaisdeSello(string ide, string newPais) {
    SellosDiscograficos* SelloDisc = buscarSellos(ide); // Buscar el sello por su ID.
    if (SelloDisc == NULL) { // Si el sello no existe, mostrar mensaje de error.
        cout << "El sello discográfico no existe" << endl;
        return;
    }
    if (SelloDisc->pais == newPais) { // Verificar si el nuevo país ya es el actual.
        cout << "El país ya está registrado para este sello" << endl;
        return;
    }
    SelloDisc->pais = newPais; // Modificar el país del sello.
    cout << "País del sello discográfico modificado correctamente" << endl;
}
/*
Elimina un sello discográfico de la lista doblemente enlazada circular.
Recibe como parámetro el ID del sello a eliminar.
Si el sello no existe, muestra un mensaje de error.
Si el sello existe, elimina también todos los artistas asociados a ese sello.
Si el sello es el único en la lista, la deja vacía.
Si el sello no es único, actualiza los punteros de los nodos adyacentes para mantener la estructura de la lista.
Se eliminan los artistas pertenecientes al sello.
*/
void eliminarSelloDiscografico(string ide) {
    SellosDiscograficos* selloDisc = buscarSellos(ide); // Buscar el sello por su ID.
    if (selloDisc == NULL) { // Si el sello no existe, muestra un mensaje de error.
        cout << "El sello discográfico no está registrado" << endl;
        return;
    }
    // Eliminar todos los artistas asociados al sello.
    Artistas* artistaActual = primerA;
    while (artistaActual != NULL) {
        Artistas* siguienteArtista = artistaActual->siguiente;
        if (artistaActual->selloDiscografico == ide) {
            eliminarArtista(artistaActual->id);
        }
        artistaActual = siguienteArtista;
    }

    // Si el sello es el único en la lista, eliminarlo y poner la lista vacía.
    if (selloDisc->siguiente == selloDisc && selloDisc->anterior == selloDisc) {
        delete selloDisc;
        primerS = NULL;
    } else { // Si hay más sellos, eliminar el sello y actualizar los punteros de la lista.
        selloDisc->anterior->siguiente = selloDisc->siguiente;
        selloDisc->siguiente->anterior = selloDisc->anterior;
        if (selloDisc == primerS) { // Si el sello a eliminar es el primero, actualizar primerS.
            primerS = selloDisc->siguiente;
        }

        delete selloDisc; // Eliminar el nodo del sello.
    }

    cout << "Sello discográfico eliminado correctamente." << endl;
}


/*
=========
GENEROS MUSICALES
=========
*/
/*
Inserta un nuevo género musical en la lista circular de géneros musicales.
Recibe como parámetros el ID, el nombre y la descripción del género a insertar.
Si la lista está vacía, el nuevo género se convierte en el primero de la lista y se enlaza consigo mismo.
Si el género ya está registrado por su ID o si el nombre ya existe, muestra un mensaje de error y no inserta el nuevo género.
Si el género no existe en la lista, se inserta al final de la lista y se establece el enlace circular.
El género musical nuevo es añadido de manera que el último género de la lista apunte al primero, manteniendo la estructura circular.
*/
void insertarGeneroMusical(string ID, string nombre, string descripcion) {
    GenerosMusicales* newGenre = new GenerosMusicales(ID, nombre, descripcion); // Crear el nuevo género.

    // Si la lista está vacía, el nuevo género será el único en la lista.
    if (primerG == NULL) {
        primerG = newGenre;
        newGenre->siguiente = primerG; // Enlazar el único género con sí mismo.
        return;
    }

    // Comprobar si el género ya está registrado por su ID.
    if (buscarGeneroMusical(ID) != NULL) {
        cout << "El género musical ya está registrado" << endl;
        return;
    }

    // Comprobar si el nombre del género ya existe en la lista.
    if (buscarGeneroMusicalPorNombre(nombre) != NULL) {
        cout << "El nombre del género ya existe para otro género musical." << endl;
        return;
    }

    // Recorrer la lista hasta el último nodo.
    GenerosMusicales* temp = primerG;
    while (temp->siguiente != primerG) {
        temp = temp->siguiente;
    }

    // Insertar el nuevo género al final de la lista y hacerla circular.
    temp->siguiente = newGenre;
    newGenre->siguiente = primerG; // El último género apunta al primer género.
}


/*
Modifica la descripción de un género musical en la lista.
Recibe como parámetros el ID del género musical y la nueva descripción que se le asignará.
Si el género musical con el ID proporcionado no existe en la lista, muestra un mensaje de error.
Si el género existe, se actualiza la descripción con el nuevo valor proporcionado.
*/
void modificarDescripcionGeneroMusical(string ID, string descripcion) {
    GenerosMusicales* generoMusical = buscarGeneroMusical(ID); // Buscar el género musical por su ID.

    if (generoMusical == NULL) { // Verificar si el género no existe.
        cout << "El género musical no está registrado" << endl; // Mostrar error si no se encuentra el género.
    } else { 
        generoMusical->descripcion = descripcion; // Actualizar la descripción del género.
    }
}
/*
Elimina un género musical de la lista circular.
Recibe como parámetro el ID del género musical que se desea eliminar.
Si el género musical no existe, muestra un mensaje de error.
Si el género musical existe, se elimina de la lista y se actualizan los enlaces de los nodos adyacentes.
*/
void eliminarGeneroMusical(string ID) {
    GenerosMusicales* generoMusical = buscarGeneroMusical(ID); // Buscar el género musical por ID.
    
    if (generoMusical == NULL) { // Si no se encuentra el género en la lista, mostrar mensaje de error.
        cout << "El género musical no existe" << endl;
    } else {
        // Caso especial cuando hay solo un género musical en la lista.
        if (primerG->siguiente == primerG) { 
            delete primerG;
            primerG = NULL; // Si solo hay un nodo, se elimina y se actualiza la lista a vacía.
            cout << "Género musical eliminado" << endl;
            return;
        }

        GenerosMusicales* actual = primerG;
        GenerosMusicales* anterior = NULL;
        
        do {
            if (actual->id == ID) { // Si se encuentra el género con el ID indicado.
                if (actual == primerG) { // Si el género a eliminar es el primero de la lista.
                    GenerosMusicales* ultimo = primerG;
                    while (ultimo->siguiente != primerG) { // Encontrar el último nodo de la lista.
                        ultimo = ultimo->siguiente;
                    }
                    primerG = primerG->siguiente; // Actualizar primerG al siguiente nodo.
                    ultimo->siguiente = primerG; // El último nodo ahora apunta al nuevo primer nodo.
                } else {
                    anterior->siguiente = actual->siguiente; // El nodo anterior apunta al siguiente del nodo eliminado.
                }
                delete actual; // Eliminar el nodo del género musical.
                cout << "Género eliminado correctamente." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente; // Avanzar al siguiente nodo.
        } while (actual != primerG); // Recorrer la lista circular hasta encontrar el género o regresar al principio.
    }
}

/*
========
PLAYLIST
========
*/
/*
Agrega una nueva playlist.
Parámetros:
- id: ID único de la playlist.
- nombre: Nombre de la playlist.
- creador: Nombre del creador de la playlist.
- fecha: Fecha de creación de la playlist.
Si ya existe una playlist con el mismo ID, muestra un mensaje de error.
Si la lista de playlists está vacía, la nueva playlist se convierte en la primera.
Si no, la nueva playlist se inserta al inicio de la lista.
*/
void agregarPlaylist(string id, string nombre, string creador, int fecha) {
    Playlist* nodoPlaylist = buscarPlaylist(id); // Buscar la playlist por ID.
    if (nodoPlaylist != NULL) { // Verificar si la playlist ya existe.
        cout << "La playlist con ID: " << nodoPlaylist->id << " ya existe" << endl;
        return;
    }

    Playlist* newPlaylist = new Playlist(id, nombre, creador, fecha); // Crear la nueva playlist.

    // Si la lista de playlists está vacía, la nueva playlist se convierte en la primera.
    if (primerP == NULL) {
        primerP = newPlaylist;
        return;
    }

    // Insertar la nueva playlist al inicio de la lista.
    newPlaylist->siguiente = primerP;
    primerP = newPlaylist;
}
/*
Modifica el nombre de una playlist existente.
Parámetros:
- id: ID de la playlist a modificar.
- name: Nuevo nombre que se asignará a la playlist.

Si la playlist con el ID proporcionado no existe, muestra un mensaje de error.
Si la playlist existe, actualiza el nombre al nuevo valor proporcionado.
*/
void modificarNombrePlaylist(string id, string name) {
    Playlist* playlist = buscarPlaylist(id); // Buscar la playlist por ID.

    // Verificar si la playlist no existe.
    if (playlist == NULL) {
        cout << "La playlist no existe" << endl;
    } else {
        playlist->nombre = name; // Actualizar el nombre de la playlist.
    }
}
/*
Modifica el creador de una playlist existente.
Parámetros:
- id: ID de la playlist a modificar.
- creator: Nuevo nombre del creador que se asignará a la playlist.

Si la playlist con el ID dado no existe, muestra un mensaje de error.
Si la playlist existe, actualiza el nombre del creador al nuevo.
*/
void modificarCreadorPlaylist(string id, string creator) {
    Playlist* playlist = buscarPlaylist(id); // Buscar la playlist por ID.

    // Verificar si la playlist no existe.
    if (playlist == NULL) {
        cout << "La playlist no existe" << endl;
    } else {
        playlist->creador = creator; // Actualizar el creador de la playlist.
    }
}
/*
Elimina una playlist existente dada su ID.
Parámetros:
- id: ID de la playlist que se desea eliminar.
Si la playlist con el ID dado no existe, muestra un mensaje de error.
Si la playlist existe, la elimina de la lista y libera la memoria correspondiente.
*/
void eliminarPlaylist(string id) {
    Playlist* playlist = buscarPlaylist(id); // Buscar la playlist por ID.

    // Verificar si la playlist no existe.
    if (playlist == NULL) {
        cout << "La playlist no existe" << endl;
    } else {
        Playlist* actual = primerP;  // Apuntar al primer nodo de la lista de playlists.
        Playlist* anterior = NULL;

        // Recorrer la lista de playlists para encontrar la correspondiente al ID.
        while (actual != NULL) {
            if (actual->id == id) {
                // Si la playlist a eliminar es la primera de la lista.
                if (anterior == NULL) {
                    primerP = actual->siguiente; // Actualizar el puntero al primer nodo.
                } else {
                    anterior->siguiente = actual->siguiente; // Desvincular la playlist de la lista.
                }
                delete actual; // Liberar la memoria del nodo de la playlist eliminada.
                cout << "Playlist eliminada correctamente." << endl;
                return; // Salir de la función después de eliminar.
            }
            anterior = actual; // Mover el puntero anterior al nodo actual.
            actual = actual->siguiente; // Mover al siguiente nodo.
        }
    }
}

/*
=========
CONSULTAS
=========
*/

/*
Esta función determina cuál es el o los géneros musicales que tienen más canciones registradas.
Recorre la lista de géneros musicales y cuenta cuántas canciones están asociadas a cada género.
Si hay géneros con el mismo número máximo de canciones, todos serán listados.
En caso de no haber géneros o canciones, muestra un mensaje adecuado.
No recibe parámetros y no devuelve ningún valor.
Si no hay géneros registrados, se muestra un mensaje de error.
Si se encuentran géneros con canciones, se muestra el o los géneros con más canciones.
Si no hay canciones registradas en ningún género, se muestra un mensaje de advertencia.
*/
void generoMayorCanciones() {
    // Verificar si no hay géneros registrados.
    if (primerG == NULL) {
        cout << "No hay géneros registrados" << endl;
        return;
    }

    GenerosMusicales* temp = primerG;  // Apuntar al primer género en la lista.
    int max = 0;  // Variable para almacenar la cantidad máxima de canciones encontradas.
    bool primeraVuelta = true;  // Variable de control para asegurar una única vuelta inicial.

    // Recorre la lista de géneros y cuenta las canciones de cada uno.
    do {
        int contador = 0;  // Contador de canciones en el género actual.
        Canciones* temp2 = temp->canciones;  // Apuntar a las canciones del género actual.

        // Contar el número de canciones en este género.
        while (temp2 != NULL) {
            contador++;  // Incrementar el contador por cada canción.
            temp2 = temp2->siguiente;  // Mover al siguiente nodo de canciones.
        }

        // Actualizar el máximo si se encuentra un género con más canciones.
        if (contador > max) {
            max = contador;
        }

        temp = temp->siguiente;  // Mover al siguiente género.
        primeraVuelta = false;  // No es la primera vuelta.
    } while (temp != primerG && (temp != NULL || primeraVuelta));  // Continuar hasta que se vuelva al primer género.

    // Si no hay canciones registradas en ningún género.
    if (max == 0) {
        cout << "No hay canciones registradas en ningún género." << endl;
        return;
    }

    // Volver a recorrer los géneros para imprimir aquellos con el máximo número de canciones.
    temp = primerG;
    primeraVuelta = true;
    cout << "Géneros con más canciones (" << max << " canciones):" << endl;

    // Recorre la lista de géneros e imprime los que tienen la cantidad máxima de canciones.
    do {
        int contador = 0;  // Contador de canciones en el género actual.
        Canciones* temp2 = temp->canciones;  // Apuntar a las canciones del género actual.

        // Contar las canciones del género actual.
        while (temp2 != NULL) {
            contador++;  // Incrementar el contador por cada canción.
            temp2 = temp2->siguiente;  // Mover al siguiente nodo de canciones.
        }

        // Si el género tiene el máximo número de canciones, se imprime su nombre.
        if (contador == max) {
            cout << "- " << temp->nombre << endl;
        }

        temp = temp->siguiente;  // Mover al siguiente género.
        primeraVuelta = false;  // No es la primera vuelta.
    } while (temp != primerG && (temp != NULL || primeraVuelta));  // Continuar hasta que se vuelva al primer género.
}

/*
Encuentra y muestra el/los artista(s) que tienen el mayor número de álbumes registrados.

Si no hay artistas registrados, muestra un mensaje indicándolo.
Si ningún artista tiene álbumes registrados, muestra un mensaje indicando que no hay álbumes.
Si hay artistas con álbumes, muestra el nombre artístico de aquellos que poseen la mayor cantidad de álbumes.

El método recorre la lista de artistas y cuenta el número de álbumes de cada uno.
Primero, determina el número máximo de álbumes registrados por un solo artista.
Luego, imprime los nombres de los artistas que poseen esa cantidad máxima de álbumes.
*/

void artistaMaxAlbumes() {
    // Verificar si no hay artistas registrados.
    if (primerA == NULL) {
        cout << "No hay artistas registrados" << endl;
        return;
    }

    Artistas* temp = primerA;
    int max = 0;

    // Recorrer la lista de artistas para encontrar el número máximo de álbumes.
    while (temp != NULL) {
        int cont = 0;
        Albumes* temp2 = temp->albumes;

        // Contar los álbumes asociados al artista actual.
        while (temp2 != NULL) {
            cont++;
            temp2 = temp2->siguiente;
        }

        // Actualizar el máximo si el artista actual tiene más álbumes.
        if (cont > max) {
            max = cont;
        }

        temp = temp->siguiente;
    }

    // Verificar si ningún artista tiene álbumes.
    if (max == 0) {
        cout << "Ningún artista tiene álbumes registrados" << endl;
        return;
    }

    // Imprimir los artistas que tienen el número máximo de álbumes.
    cout << "Artistas con más álbumes (" << max << "):" << endl;
    temp = primerA;

    while (temp != NULL) {
        int cont = 0;
        Albumes* temp2 = temp->albumes;

        // Contar los álbumes del artista actual.
        while (temp2 != NULL) {
            cont++;
            temp2 = temp2->siguiente;
        }

        // Si el artista tiene la cantidad máxima de álbumes, imprimir su nombre artístico.
        if (cont == max) {
            cout << "- " << temp->nombreArtistico << endl;
        }

        temp = temp->siguiente;
    }
}
/*
Encuentra e imprime las canciones con la mayor duración registradas.
Si no hay canciones registradas, muestra un mensaje de error.
Recorre todos los álbumes de cada artista para determinar la canción más larga.
*/
void cancionMasLarga() {
    Artistas* temp = primerA;
    int maxTiempo = 0;

    // Primera pasada para encontrar la duración máxima
    while (temp != NULL) {
        Albumes* album = temp->albumes;
        while (album != NULL) {
            Canciones* cancion = album->canciones;
            while (cancion != NULL) {
                if (cancion->duracion > maxTiempo) {
                    maxTiempo = cancion->duracion;
                }
                cancion = cancion->siguiente;
            }
            album = album->siguiente;
        }
        temp = temp->siguiente;
    }

    if (maxTiempo == 0) {
        cout << "No hay canciones registradas" << endl;
        return;
    }

    // Segunda pasada para imprimir todas las canciones con la duración máxima
    cout << "Canciones con más duración (" << maxTiempo << " segundos):" << endl;
    temp = primerA;
    while (temp != NULL) {
        Albumes* album = temp->albumes;
        while (album != NULL) {
            Canciones* cancion = album->canciones;
            while (cancion != NULL) {
                if (cancion->duracion == maxTiempo) {
                    cout << "- " << cancion->titulo << endl;
                }
                cancion = cancion->siguiente;
            }
            album = album->siguiente;
        }
        temp = temp->siguiente;
    }
}
/*
Encuentra y muestra las playlists que contienen la mayor cantidad de canciones.
Si no hay playlists registradas, muestra un mensaje de advertencia.
Si ninguna playlist contiene canciones, muestra un mensaje indicando que están vacías.
En caso de haber múltiples playlists con la cantidad máxima de canciones, las lista todas.
*/
void playlistMaxCanciones() {
    if (primerP == NULL) {
        cout << "No hay playlists registradas" << endl;
        return;
    }

    Playlist* temp = primerP;
    int max = 0;

    // Paso 1: encontrar la cantidad máxima de canciones
    while (temp != NULL) {
        int contador = 0;
        Canciones* temp2 = temp->canciones;
        while (temp2 != NULL) {
            contador++;
            temp2 = temp2->siguiente;
        }
        if (contador > max) {
            max = contador;
        }
        temp = temp->siguiente;
    }

    if (max == 0) {
        cout << "No hay canciones en ninguna playlist" << endl;
        return;
    }

    cout << "Playlists con más canciones (" << max << " canciones):" << endl;
    temp = primerP;
    while (temp != NULL) {
        int contador = 0;
        Canciones* temp2 = temp->canciones;
        while (temp2 != NULL) {
            contador++;
            temp2 = temp2->siguiente;
        }
        if (contador == max) {
            cout << "- " << temp->nombre << endl;
        }
        temp = temp->siguiente;
    }
}
/*
Muestra la cantidad de álbumes registrados para cada artista. 
Si no hay artistas en el sistema, muestra un mensaje de advertencia.
Para cada artista encontrado, cuenta el número de álbumes asociados y lo muestra en pantalla.
*/
void albumesPorArtista() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados" << endl;
        return;
    }

    Artistas *artista = primerA;
    while (artista != NULL) {
        int cont = 0;
        Albumes *temp = artista->albumes;

        // Contar el número de álbumes del artista actual
        while (temp != NULL) {
            cont++;
            temp = temp->siguiente;
        }

        // Imprimir el resultado para el artista actual
        cout << artista->nombreArtistico << " tiene " << cont << " álbumes registrados" << endl;
        artista = artista->siguiente;
    }
}
/*
Encuentra y muestra el sello discográfico con el mayor número de artistas registrados.
Si no hay sellos discográficos en el sistema, muestra un mensaje de advertencia.
Si existe un sello con artistas, muestra el nombre del sello con el mayor número de artistas firmados.
*/
void selloDiscograficoConMasArtistas() {
    if (primerS == NULL) {
        cout << "No hay sellos discográficos registrados" << endl;
        return;
    }

    SellosDiscograficos *selloDiscografico = primerS;
    SellosDiscograficos *selloDiscMaxArtistas = NULL;
    int max = 0;

    // Recorrer todos los sellos discográficos en una lista doble y circular
    do {
        int contador = 0;
        enlaceSellosArtistas *enlace = selloDiscografico->sublistaArtista;

        // Contar el número de artistas asociados al sello actual
        while (enlace != NULL) {
            contador++;
            enlace = enlace->siguiente;
        }

        // Actualizar el sello con el mayor número de artistas
        if (contador > max) {
            max = contador;
            selloDiscMaxArtistas = selloDiscografico;
        }

        selloDiscografico = selloDiscografico->siguiente;
    } while (selloDiscografico != primerS);

    // Mostrar el sello con más artistas si existe
    if (selloDiscMaxArtistas != NULL) {
        cout << "El sello discográfico con más artistas firmados es "
             << selloDiscMaxArtistas->nombre << " (" << max << " artistas)" << endl;
    }
}

/*
Busca y muestra todas las canciones publicadas en un año específico.
Recibe como parámetro el año de lanzamiento (year1).
Si no hay artistas registrados o no hay canciones del año indicado, muestra mensajes correspondientes.
De lo contrario, imprime el título y el nombre artístico de cada canción publicada en el año dado.
*/
void cancionesPublicadasYear(int year1) {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay canciones" << endl;
        return;
    }

    Artistas *artistas = primerA;
    bool hayCanciones = false;

    // Recorrer todos los artistas registrados
    while (artistas != NULL) {
        Albumes *album = artistas->albumes;

        // Recorrer todos los álbumes del artista actual
        while (album != NULL) {
            Canciones *cancion = album->canciones;

            // Recorrer todas las canciones del álbum actual
            while (cancion != NULL) {
                // Si el año de la canción coincide con el año buscado
                if (cancion->year == year1) {
                    hayCanciones = true;
                    cout << "La canción \"" << cancion->titulo << "\" del artista \"" 
                         << artistas->nombreArtistico << "\" es del año " << year1 << "." << endl;
                }
                cancion = cancion->siguiente;
            }
            album = album->siguiente;
        }
        artistas = artistas->siguiente;
    }

    // Mensaje si no se encontraron canciones del año indicado
    if (!hayCanciones) {
        cout << "No se encontraron canciones del año " << year1 << "." << endl;
    }
}
/*
Busca y muestra todos los álbumes que tienen exactamente una cantidad específica de canciones.
Recibe como parámetro la cantidad de canciones (cantidad).
Si no hay artistas registrados o ningún álbum coincide con la cantidad indicada, muestra mensajes correspondientes.
De lo contrario, imprime el título del álbum y el nombre artístico del artista que lo posee.
*/
void albumesCantidadCanciones(int cantidad) {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay canciones" << endl;
        return;
    }

    Artistas *artistas = primerA;
    bool hayCanciones = false;

    // Recorrer todos los artistas registrados
    while (artistas != NULL) {
        Albumes *album = artistas->albumes;

        // Recorrer todos los álbumes del artista actual
        while (album != NULL) {
            // Verificar si el álbum tiene el número de canciones indicado
            if (album->numeroCanciones == cantidad) {
                cout << "El álbum \"" << album->titulo << "\" del artista \"" << artistas->nombreArtistico << "\" tiene " << cantidad << " canciones." << endl;
                hayCanciones = true;
            }
            album = album->siguiente;
        }
        artistas = artistas->siguiente;
    }

    // Mensaje si no se encontraron álbumes con la cantidad especificada
    if (!hayCanciones) {
        cout << "No hay álbumes con " << cantidad << " canciones." << endl;
    }
}

/*
========
REPORTES
========
*/

/*
Muestra la lista de artistas registrados, mostrando su ID, nombre artístico, nombre real, país y sello discográfico.
Recorre la lista de artistas comenzando desde el primer artista registrado y va imprimiendo la información de cada uno.
Si no hay artistas registrados, muestra un mensaje indicando que la lista está vacía.
*/
void imprimirListaArtistas() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados." << endl;
        return;
    }
    Artistas *temp = primerA;
    while (temp != NULL) {
        cout << "ID: " << temp->id << endl;
        cout << "Nombre artístico: " << temp->nombreArtistico << endl;
        cout << "Nombre real: " << temp->nombreReal << endl;
        cout << "País: " << temp->pais << endl;
        cout << "Sello discográfico: " << temp->selloDiscografico << endl;
        temp = temp->siguiente;
    }
}
/*
Muestra la lista de álbumes registrados de todos los artistas.
Recorre la lista de artistas y, para cada artista, recorre sus álbumes, mostrando la información del álbum:
ID, título, año de lanzamiento, número de canciones y el nombre artístico del artista.
Si no hay artistas registrados, muestra un mensaje indicando que no hay álbumes.
*/
void imprimirListaAlbumes() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay álbumes." << endl;
        return;
    }

    Artistas *artista = primerA;
    while (artista != NULL) {
        Albumes *album = artista->albumes;
        while (album != NULL) {
            cout << "ID del álbum: " << album->id << endl;
            cout << "Título: " << album->titulo << endl;
            cout << "Año: " << album->year << endl;
            cout << "Número de canciones: " << album->numeroCanciones << endl;
            cout << "Artista: " << artista->nombreArtistico << endl;
            album = album->siguiente;
        }
        artista = artista->siguiente;
    }
}
/*
Imprime la lista de todas las canciones registradas de todos los artistas y sus respectivos álbumes.
Recorre la lista de artistas, para cada uno de ellos recorre sus álbumes y dentro de estos, las canciones,
mostrando la información de cada canción: título, nombre artístico del artista, título del álbum, año de la canción y duración en segundos.
Si no hay artistas registrados, muestra un mensaje indicando que no hay canciones.
*/

void imprimirCanciones() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay canciones." << endl;
        return;
    }
    Artistas *artista = primerA;
    while (artista != NULL) {
        Albumes *album = artista->albumes;
        while (album != NULL) {
            Canciones *cancion = album->canciones;
            while (cancion != NULL) {
                cout << "Canción: \"" << cancion->titulo << "\" | Artista: \""
                     << artista->nombreArtistico << "\" | Álbum: \"" << album->titulo
                     << "\" | Año: " << cancion->year << " | Duración: "
                     << cancion->duracion << "s" << endl;
                cancion = cancion->siguiente;
            }
            album = album->siguiente;
        }
        artista = artista->siguiente;
    }
}


/*
Imprime la lista de todos los géneros musicales registrados y las canciones asociadas a cada uno.
Recorre la lista de géneros musicales y para cada género, imprime su ID, nombre y descripción.
Si el género tiene canciones asociadas, muestra los títulos de las canciones. Si no tiene canciones asociadas, muestra un mensaje indicándolo.
Si no hay géneros musicales registrados, muestra un mensaje indicando que no hay géneros disponibles.
*/
void imprimirListaGenerosMusicales() {
    if (primerG == NULL) {
        cout << "No hay géneros musicales registrados." << endl;
        return;
    }
    GenerosMusicales *genero = primerG;
    do {
        cout << "ID del género: " << genero->id << endl;
        cout << "Nombre del género: " << genero->nombre << endl;
        cout << "Descripción: " << genero->descripcion << endl;

        if (genero->canciones != NULL) {
            Canciones *cancion = genero->canciones;
            cout << "Canciones asociadas a este género:" << endl;
            while (cancion != NULL) {
                cout << "    Título de la canción: " << cancion->titulo << endl;
                cancion = cancion->siguiente;
            }
        } else {
            cout << "No hay canciones asociadas a este género." << endl;
        }
        cout << "--------------------------------------" << endl;
        genero = genero->siguiente;
    } while (genero != primerG);
}


/*
Imprime la lista de todas las playlists registradas y las canciones asociadas a cada una.
Recorre la lista de playlists y para cada playlist, imprime su ID, nombre, creador y fecha de creación.
Si la playlist tiene canciones asociadas, muestra los títulos de las canciones. Si no tiene canciones asociadas, muestra un mensaje indicándolo.
Si no hay playlists registradas, muestra un mensaje indicando que no hay playlists disponibles.
*/
void imprimirListaPlaylists() {
    if (primerP == NULL) {
        cout << "No hay playlists registradas." << endl;
        return;
    }
    Playlist *playlist = primerP;
    while (playlist != NULL) {
        cout << "ID de la playlist: " << playlist->id << endl;
        cout << "Nombre de la playlist: " << playlist->nombre << endl;
        cout << "Creador de la playlist: " << playlist->creador << endl;
        cout << "Fecha de creación: " << playlist->fecha << endl;

        if (playlist->canciones != NULL) {
            Canciones *cancion = playlist->canciones;
            cout << "Canciones en esta playlist:" << endl;
            while (cancion != NULL) {
                cout << "    Título de la canción: " << cancion->titulo << endl;
                cancion = cancion->siguiente;
            }
        } else {
            cout << "No hay canciones en esta playlist." << endl;
        }

        cout << "--------------------------------------" << endl;
        playlist = playlist->siguiente;
    }
}
/*
Imprime la lista de todos los sellos discográficos registrados y los artistas asociados a cada uno.
Recorre la lista de sellos discográficos y para cada sello, imprime su ID, nombre, país y año de fundación.
Si el sello tiene artistas asociados, muestra los nombres reales y artísticos de los artistas. Si no tiene artistas asociados, muestra un mensaje indicándolo.
Si no hay sellos discográficos registrados, muestra un mensaje indicando que no hay sellos disponibles.
*/
/*
Imprime la lista de todos los sellos discográficos registrados y los artistas asociados a cada uno.
Recorre la lista doble circular de sellos discográficos y para cada sello, imprime su ID, nombre, país y año de fundación.
Si el sello tiene artistas asociados, muestra los nombres reales y artísticos de estos artistas. Si no tiene artistas asociados, muestra un mensaje indicándolo.
Si no hay sellos discográficos registrados, muestra un mensaje indicando que no hay sellos disponibles.
*/

void imprimirSellosDiscograficos() {
    if (primerS == NULL) {
        cout << "No hay sellos discográficos registrados." << endl;
        return;
    }
    SellosDiscograficos *sello = primerS;
    do {
        cout << "ID del sello: " << sello->id << endl;
        cout << "Nombre del sello: " << sello->nombre << endl;
        cout << "País del sello: " << sello->pais << endl;
        cout << "Año de fundación: " << sello->year << endl;

        if (sello->sublistaArtista != NULL) {
            enlaceSellosArtistas *artistaEnlace = sello->sublistaArtista;
            cout << "Artistas asociados a este sello:" << endl;
            while (artistaEnlace != NULL) {
                cout << "    Nombre del artista: " << artistaEnlace->enlace->nombreReal
                     << " (alias: " << artistaEnlace->enlace->nombreArtistico << ")" << endl;
                artistaEnlace = artistaEnlace->siguiente;
            }
        } else {
            cout << "No hay artistas asociados a este sello." << endl;
        }
        cout << "--------------------------------------" << endl;
        sello = sello->siguiente;
    } while (sello != primerS);
}

/*
Función que imprime todas las listas en una única llamada.
*/
void imprimirListasPrincipales() {
    imprimirListaArtistas();
    imprimirListaAlbumes();
    imprimirListaGenerosMusicales();
    imprimirListaPlaylists();
    imprimirSellosDiscograficos();
}
/*
Genera un reporte detallado de todos los artistas registrados.  
La función recorre la lista de artistas y para cada uno imprime:
- Nombre real, nombre artístico, país y sello discográfico.
- Si el artista tiene álbumes registrados, se imprimen los títulos de los álbumes junto con el año de publicación.
  - Para cada álbum, si tiene canciones, se listan sus títulos; si no tiene canciones, se indica que no hay canciones en ese álbum.
  - Si el artista no tiene álbumes, se muestra un mensaje indicando que no tiene álbumes registrados.
Si no hay artistas registrados, se muestra un mensaje indicando que no hay artistas.
*/
void reporteArtistas() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados" << endl;
    } else {
        Artistas* temp = primerA;
        while (temp != NULL) {
            cout << "Nombre Real: " << temp->nombreReal << endl;
            cout << "Alias: " << temp->nombreArtistico << endl;
            cout << "País: " << temp->pais << endl;
            cout << "Sello Discográfico: " << temp->selloDiscografico << endl;
            if (temp->albumes != NULL) {
                cout << "Álbumes:" << endl;
                Albumes* alb = temp->albumes;
                while (alb != NULL) {
                    cout << alb->titulo << " (" << alb->year << ")" << endl;
                    if (alb->canciones != NULL) {
                        Canciones* c = alb->canciones;
                        while (c != NULL) {
                            cout << "      " << c->titulo << endl;
                            c = c->siguiente;
                        }
                    } else {
                        cout <<"No hay canciones en este álbum" << endl;
                    }
                    alb = alb->siguiente;
                }
            } else {
                cout << "No tiene álbumes registrados" << endl;
            }
            temp = temp->siguiente;
        }
    }
}

/*QUICKSORT para ordenamiento*/
Canciones* concat(Canciones* a, Canciones* b) {
    if (a == NULL) return b;
    Canciones* temp = a;
    while (temp->siguiente != NULL) {
        temp = temp->siguiente;
    }
    temp->siguiente = b;
    return a;
}

/*
Algoritmo de QuickSort adaptado a ordenar por duración de la canción.
*/
Canciones* quicksortCanciones(Canciones* head) {
    if (head == NULL || head->siguiente == NULL) {
        return head;
    }

    int pivot = head->duracion;

    Canciones* menores = NULL;
    Canciones* iguales = NULL;
    Canciones* mayores = NULL;

    Canciones* temp = head;
    while (temp != NULL) {
        Canciones* nuevo = new Canciones(*temp); 
        nuevo->siguiente = NULL;

        if (nuevo->duracion < pivot) {
            nuevo->siguiente = menores;
            menores = nuevo;
        } else if (nuevo->duracion == pivot) {
            nuevo->siguiente = iguales;
            iguales = nuevo;
        } else {
            nuevo->siguiente = mayores;
            mayores = nuevo;
        }
        temp = temp->siguiente;
    }

    menores = quicksortCanciones(menores);
    mayores = quicksortCanciones(mayores);

    Canciones* res = concat(menores, iguales);
    res = concat(res, mayores);
    return res;
}
/*
Imprime los álbumes de cada artista, junto con las canciones ordenadas por duración.
La función recorre la lista de artistas y para cada uno:
- Muestra el título del álbum y el nombre artístico del artista.
- Ordena las canciones del álbum por su duración utilizando el algoritmo quicksort.
- Imprime las canciones ordenadas por su duración junto con su duración en minutos.
Después de imprimir las canciones, la memoria de las canciones ordenadas es liberada.
Si no hay artistas registrados, muestra un mensaje indicando que no hay álbumes.
*/

void imprimirAlbumesConCancionesOrdenadasPorDuracion() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay álbumes." << endl;
        return;
    }
    Artistas *artista = primerA;
    while (artista != NULL) {
        Albumes *album = artista->albumes;
        while (album != NULL) {
            cout << "Álbum: " << album->titulo << " (" << album->year << "), Artista: " << artista->nombreArtistico << endl;
            Canciones *ordenadas = quicksortCanciones(album->canciones);
            Canciones *c = ordenadas;
            while (c != NULL) {
                cout << "  - " << c->titulo << " (" << c->duracion << " minutos)" << endl;
                c = c->siguiente;
            }

            while (ordenadas != NULL) {
                Canciones *temp = ordenadas;
                ordenadas = ordenadas->siguiente;
                delete temp;
            }
            cout << "-----------------------------------" << endl;
            album = album->siguiente;
        }
        artista = artista->siguiente;
    }
}


/*
====================
VALIDACIÓN DE INPUTS
====================
*/

/*
Inputs para Menú de Mantenimiento
*/

/*
- Canciones
*/

void inputInsertarCancion() {
    string idArtista, idAlbum;
    
    cout << "Ingrese el ID del artista: " << endl;
    cin >> idArtista;

    cout << "Ingrese el ID del álbum: " << endl;
    cin >> idAlbum;

    insertarCancion(idArtista,idAlbum);

    
}

void inputModificarTituloCancion() {
    string idArtista, idAlbum, idCancion, nuevoTitulo;

    cout << "Ingrese el ID del artista: ";
    getline(cin, idArtista);

    cout << "Ingrese el ID del album: ";
    getline(cin, idAlbum);

    cout << "Ingrese el ID de la canción a modificar: ";
    getline(cin, idCancion);

    cout << "Ingrese el nuevo título de la canción: ";
    getline(cin, nuevoTitulo);

    modificarTituloCancion(idArtista, idAlbum, idCancion, nuevoTitulo);
    cout << endl;
}

void inputEliminarCancion() {
    string idArtista, idAlbum, idCancion;

    cout << "Ingrese el ID del artista: ";
    getline(cin, idArtista);

    cout << "Ingrese el ID del album: ";
    getline(cin, idAlbum);

    cout << "Ingrese el ID de la canción a eliminar: ";
    getline(cin, idCancion);

    eliminarCancion(idArtista, idAlbum, idCancion);
    cout << endl;
}

/*Inputs para Artistas*/

void inputInsertarArtista() {
    string id, nombreArt, nombreReal, pais, selloDisc;

    cout << "Ingrese el ID del artista: ";
    cin >> id;
    cin.ignore(); 

    cout << "Ingrese el nombre artístico del artista: ";
    getline(cin, nombreArt);

    cout << "Ingrese el nombre real del artista: ";
    getline(cin, nombreReal);

    cout << "Ingrese el país del artista: ";
    getline(cin, pais);

    cout << "Ingrese el sello discográfico al que pertenece el artista: ";
    getline(cin, selloDisc);

    insertarArtistaOrdenAlfabeticamente(id, nombreArt, nombreReal, pais, selloDisc);
    cout << endl;
}

void inputModificarNombreArtistico(){
    string ID,nombre;

    cout << "Ingrese el ID del artista: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese el nuevo nombre artistico del artista: ";
    getline(cin,nombre);

    modificarNombreArtisticoDeArtista(ID,nombre);
    cout <<endl;
}

void inputModificarPaisDeArtista(){
    string ID,pais;

    cout << "Ingrese el ID del artista: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese el nuevo país del artista: ";
    getline(cin,pais);

    modificarPaisDeArtista(ID,pais);
    cout << endl;
}

void inputModificarSelloDiscográficoArtista(){
    string idArtista, idSello;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> idSello;

    modificarSelloDiscograficoDeArtista(idArtista,idSello);
    cout <<endl;
}

void inputEliminarArtista(){
    string ID;

    cout << "Ingrese el ID del artista: ";
    cin >> ID;

    eliminarArtista(ID);
    cout<<endl;
}

/*Inputs para albumes*/


void inputInsertarAlbum() {
    string idArtista, idAlbum, titulo;
    int year, numCanciones;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;
    cin.ignore();

    cout << "Ingrese el ID del álbum: ";
    cin >> idAlbum;
    cin.ignore();

    cout << "Ingrese el título del álbum: ";
    getline(cin, titulo);

    while (true) {
        cout << "Ingrese el año de lanzamiento del álbum: ";
        cin >> year;

        if (cin.fail() || year <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "El año es inválido, intente nuevamente." << endl;
        } else {
            cin.ignore();
            break;
        }
    }

    while (true) {
        cout << "Ingrese el número de canciones del álbum: ";
        cin >> numCanciones;

        if (cin.fail() || numCanciones <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "El número de canciones es inválido, intente nuevamente." << endl;
        } else {
            break;
        }
    }

    insertarFinalAlbum(idArtista, idAlbum, titulo, year, numCanciones);
    cout << endl;
}


void inputModificarTituloAlbum() {
    string idArtista, idAlbum, nuevoTitulo;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;
    cin.ignore();

    cout << "Ingrese el ID del álbum: ";
    cin >> idAlbum;
    cin.ignore();

    cout << "Ingrese el nuevo título del álbum: ";
    getline(cin, nuevoTitulo);

    modificarTituloAlbum(idArtista, idAlbum, nuevoTitulo);
    cout << endl;
}

void inputEliminarAlbum(){
    string idArtista, idAlbum;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;
    
    cout << "Ingrese el ID del álbum: ";
    cin >> idAlbum;

    eliminarAlbum(idArtista,idAlbum);
    cout <<endl;
    
}

/*Inputs generos musicales*/
void inputInsertarGenerosMusicales(){
    string ID, nombre, descripcion;

    cout << "Ingrese el ID del género musical: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese el nombre del género musical: ";
    getline(cin,nombre);

    cout << "Ingrese una descripcion del género musical: ";
    getline(cin,descripcion);

    insertarGeneroMusical(ID,nombre,descripcion);
    cout << endl;

}

void inputModificarDescripcionGeneroMusical(){
    string ID, descripcion;
    cout << "Ingrese el ID del género musical: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese una descripcion del género musical: ";
    getline(cin,descripcion);

    modificarDescripcionGeneroMusical(ID,descripcion);
    cout << endl;  
}

void inputEliminarGeneroMusical(){
    string ID;
    cout << "Ingrese el ID del género musical: ";
    cin >> ID;

    eliminarGeneroMusical(ID);
    cout << endl;
}

/*Input Sello Discográfico*/

void inputInsertarSelloDiscografico(){
    string id,nombre,pais;
    int year;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese el nombre del sello discográfico: ";
    getline(cin,nombre);

    cout << "Ingrese el país del sello discográfico: ";
    getline(cin,pais);

    cout << "Ingrese el año de fundación: ";
    cin >> year;
    if (year <= 0){
        cout << "El año ingresado es inválido, intente de nuevo"<<endl;
    }

    insertarSellosDiscograficos(id,nombre,pais,year);
    
}

void inputModificarNombredeSello(){
    string id, newNombre;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese el nuevo nombre del sello discográfico: ";
    getline(cin,newNombre);

    modificarNombredeSello(id,newNombre);
    cout << endl;
}

void inputModificarPaisdeSello(){
    string id, newPais;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese el nuevo país del sello discográfico: ";
    getline(cin,newPais);

    modificarPaisdeSello(id,newPais);
    cout << endl;
}

void inputEliminarSelloDiscografico(){
    string id;
    cout << "Ingrese el ID del sello discográfico: ";
    cin >> id;

    eliminarSelloDiscografico(id);
    cout << endl;
}

void inputInsertarArtistaEnSello(){
    string idArtista, idSello;

    cout << "Ingrese el ID del artista que desea agregar: ";
    cin >> idArtista;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> idSello;

    insertarArtistaEnSello(idArtista,idSello);
    cout << endl;
}

void inputEliminarArtistaDeSello(){
    string idArtista, idSello;

    cout << "Ingrese el ID del artista que desea agregar: ";
    cin >> idArtista;

    cout << "Ingrese el ID del sello discográfico: ";
    cin >> idSello;

    eliminarArtistaDeSello(idArtista,idSello);
    cout << endl;
}

/*Inputs para Playlist*/
void inputAgregarPlaylist(){
    string id, nombre,creador;
    int fecha;

    cout << "Ingrese el id de la playlist: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese el nombre de la playlist: ";
    getline(cin,nombre);

    cout << "Ingrese el nombre de su creador: ";
    getline(cin,creador);

    cout << "Ingrese la fecha de creación: ";
    cin >> fecha;

    agregarPlaylist(id,nombre,creador,fecha);
    cout << endl;
}

void inputModificarNombrePlaylist(){
    string ID,nombre;

    cout << "Ingrese el id de la playlist: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese el nombre de la playlist: ";
    getline(cin,nombre);

    modificarNombrePlaylist(ID,nombre);
    cout <<endl;
}

void inputModificarCreadorPlaylist(){
    string ID,creador;

    cout << "Ingrese el id de la playlist: ";
    cin >> ID;
    cin.ignore();

    cout << "Ingrese el nombre de su creador: ";
    getline(cin,creador);

    modificarCreadorPlaylist(ID,creador);
    cout << endl;
}

void inputEliminarPlaylist(){
    string ID;
    cout << "Ingrese el id de la playlist: ";
    cin >> ID;
    
    eliminarPlaylist(ID);
    cout << endl;
}


/*
Inputs para Menú de Consulta
*/
void inputCancionesPublicadasYear() {
    int input = 0;
    bool validacion = false;

    while (!validacion) {
        cout << "Ingrese un año: ";
        cin >> input;
        cout << endl;

        if (input >= 0) {
            validacion = true;
        }

        else {
            cout << "Inválido. Solo se permiten números positivos." << endl;
            cout << "Intente nuevamente." << endl;
        }
    }

    cancionesPublicadasYear(input);
}

void inputAlbumesCantidadCanciones() {
    int input = 0;
    bool validacion = false;

    while (!validacion) {
        cout << "Ingrese un número: ";
        cin >> input;
        cout << endl;

        if (input >= 0) {
            validacion = true;
        }

        else {
            cout << "Inválido. Solo se permiten números positivos." << endl;
            cout << "Intente nuevamente." << endl;
        }
    }

    albumesCantidadCanciones(input);
}

/*
========
MENÚS
========
*/

void menuCanciones() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento - Canciones ===" << endl;
        cout << "1. Insertar una canción" << endl;
        cout << "2. Modificar el título de una canción" << endl;
        cout << "3. Eliminar una canción existente" << endl;
        cout << "4. Regresar al Menu De Mantenimiento" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: inputInsertarCancion(); break;

            case 2: inputModificarTituloCancion(); break;

            case 3: inputEliminarCancion(); break;

            case 4: salir = true; break;

            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }

    }
}

void menuArtistas() {
    bool salir = false;
    while (!salir) {
        int opcion = 0;
        cout << endl << "=== Menú De Mantenimiento - Artistas ===" << endl;
        cout << "1. Insertar un artista." << endl;
        cout << "2. Modificar el nombre artístico de un artista." << endl;
        cout << "3. Modificar el país de un artista." << endl;
        cout << "4. Modificar el sello discográfico de un artista." << endl;
        cout << "5. Eliminar un artista." << endl;
        cout << "6. Regresar al menú de mantenimiento." << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;
            switch (opcion) {
                case 1: inputInsertarArtista(); break;
                case 2: inputModificarNombreArtistico(); break;
                case 3: inputModificarPaisDeArtista(); break;
                case 4: inputModificarSelloDiscográficoArtista(); break;
                case 5: inputEliminarArtista(); break;
                case 6: salir = true; break;
                default: cout << "Instrucción inválida. Intente nuevamente." << endl;
            
        }
    }
}


void menuAlbumes() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento - Albúmes ===" << endl;
        cout << "1. Insertar un album a un artista"<<endl;
        cout << "2. Modificar el título de un album"<<endl;
        cout << "3. Eliminar un album"<<endl;
        cout << "4. Regresar al menú de mantenimiento"<<endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;
            switch(opcion){
                case 1: inputInsertarAlbum(); break;
                case 2: inputModificarTituloAlbum(); break;
                case 3: inputEliminarAlbum(); break;
                case 4: salir = true; break;
                default: cout << "Instrucción inválida. Intente nuevamente." << endl;
            }
    }
}

void menuGenerosMusicales() {
    bool salir = false;
    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento - Generos Musicales ===" << endl;
        cout << "1. Insertar un género musical"<<endl;
        cout << "2. Modificar la descripción de un género musical"<<endl;
        cout << "3. Eliminar un género musical"<<endl;
        cout << "4. Regresar al menú de mantenimiento"<<endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch(opcion){
            case 1: inputInsertarGenerosMusicales; break;
            case 2: inputModificarDescripcionGeneroMusical(); break;
            case 3: inputEliminarGeneroMusical(); break;
            case 4: salir = true; break;
            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}

void menuPlaylists() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento - Playlists ===" << endl;
        cout << "1. Insertar una playlist"<<endl;
        cout << "2. Modificar el nombre de una playlist"<<endl;
        cout << "3. Modificar el creador de una playlist"<<endl;
        cout << "4. Eliminar una playlist"<<endl;
        cout << "5. Regresar al menú de mantenimiento"<<endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch(opcion){
            case 1: inputAgregarPlaylist();break;
            case 2: inputModificarNombrePlaylist(); break;
            case 3: inputModificarCreadorPlaylist(); break;
            case 4: inputEliminarPlaylist(); break;
            case 5: salir = true; break;
            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}

void menuSellosDiscograficos() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento - Sellos Discograficos ===" << endl;
        cout << "1. Insertar un sello discográfico"<<endl;
        cout << "2. Modificar el nombre de un sello discográfico"<<endl;
        cout << "3. Modificar el país de un sello discográfico"<<endl;
        cout << "4. Eliminar un sello discográfico"<<endl;
        cout << "5. Insertar un artista en un sello discográfico"<<endl;
        cout << "6. Eliminar un artista de un sello discográfico"<<endl;
        cout << "7. Regresar al menú de mantenimiento"<<endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch(opcion){
            case 1: inputInsertarSelloDiscografico(); break;
            case 2: inputModificarNombredeSello(); break;
            case 3: inputModificarPaisdeSello();break;
            case 4: inputEliminarSelloDiscografico(); break;
            case 5: inputInsertarArtistaEnSello(); break;
            case 6: inputEliminarArtistaDeSello(); break;
            case 7: salir = true; break;
            default: cout << "Instrucción inválida. Intente nuevamente." << endl;    
        }

    }
}

void menuMantenimiento() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Mantenimiento ===" << endl;
        cout << "1. Canciones" << endl;
        cout << "2. Artistas" << endl;
        cout << "3. Álbumes" << endl;
        cout << "4. Géneros Musicales" << endl;
        cout << "5. Playlists" << endl;
        cout << "6. Sellos Discográficos" << endl;
        cout << "7. Regresar al Menú General" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: menuCanciones(); break;

            case 2: menuArtistas(); break;

            case 3: menuAlbumes(); break;

            case 4: menuGenerosMusicales(); break;

            case 5: menuPlaylists(); break;

            case 6: menuSellosDiscograficos(); break;

            case 7: salir = true; break;

            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}

void menuConsultas() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Consultas ===" << endl;
        cout << "1. Genero Musical con más canciones" << endl;
        cout << "2. Artista con más albúmes publicados" << endl;
        cout << "3. Canción con mayor duración" << endl;
        cout << "4. Playlist con más canciones" << endl;
        cout << "5. Álbumes por cada artista" << endl;
        cout << "6. Sello Discográfico con más artistas" << endl;
        cout << "7. Canciones publicadas en un año específico" << endl;
        cout << "8. Álbumes que superan cierto número de canciones" << endl;
        cout << "9. Regresar al Menú General" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: generoMayorCanciones(); break;

            case 2: artistaMaxAlbumes(); break;

            case 3: cancionMasLarga(); break;

            case 4: playlistMaxCanciones(); break;

            case 5: albumesPorArtista(); break;

            case 6: selloDiscograficoConMasArtistas(); break;

            case 7: inputCancionesPublicadasYear(); break;

            case 8: inputAlbumesCantidadCanciones(); break;

            case 9: salir = true; break;

            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}

void menuReportes() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Menú De Reportes ===" << endl;
        cout << "1. Imprimir todas las listas principales" << endl;
        cout << "2. Reporte detallado de cada artista" << endl;
        cout << "3. Lista de todas las playlists con sus canciones" << endl;
        cout << "4. Álbumes con canciones ordenadas por duración" << endl;
        cout << "5. Sellos discográficos con sus artistas firmados" << endl;
        cout << "6. Regresar al Menú General" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: imprimirListasPrincipales(); break;  imprimirListaArtistas();

            case 2: imprimirListaArtistas(); break;

            case 3: imprimirListaPlaylists(); break;

            case 4: imprimirAlbumesConCancionesOrdenadasPorDuracion(); break;

            case 5: imprimirSellosDiscograficos(); break;

            case 6: salir = true; break;

            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}

void menuGeneral() {
    bool salir = false;

    while (!salir) {
        int opcion = 0;

        cout << endl << "=== Bienvenido al Menú General De MusiGest ===" << endl;
        cout << "1. Mantenimiento" << endl;
        cout << "2. Consultas" << endl;
        cout << "3. Reportes" << endl;
        cout << "4. Salir del Programa" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: menuMantenimiento(); break;

            case 2: menuConsultas(); break;

            case 3: menuReportes(); break;

            case 4: {
                cout << "-- Se ha salido del programa exitosamente --" << endl;
                salir = true;
                break;
            }

            default: cout << "Instrucción inválida. Intente nuevamente." << endl;
        }
    }
}


void cargarDatos(){
    insertarGeneroMusical("GNM1", "Rock", "Género musical caracterizado por el uso destacado de guitarras eléctricas, bajo, batería y vocales potentes, fusionando elementos del blues y el country.");  
    insertarGeneroMusical("GNM2", "Pop", "Género popular que se caracteriza por estructuras melódicas pegajosas y producciones accesibles.");  
    insertarGeneroMusical("GNM3", "Jazz", "Género marcado por la improvisación, el swing y complejas progresiones armónicas.");  
    insertarGeneroMusical("GNM4", "Blues", "Género de raíces afroamericanas, con letras melancólicas y estructuras de doce compases.");  
    insertarGeneroMusical("GNM5", "Reggae", "Género originario de Jamaica, con ritmos relajados y letras que abordan temas sociales y espirituales.");  
    insertarGeneroMusical("GNM6", "Hip-Hop", "Género basado en el rap y el uso de ritmos sincopados, con influencias del funk y el soul.");  
    insertarGeneroMusical("GNM7", "Electronic", "Género que utiliza sintetizadores y secuencias electrónicas, abarcando estilos como el techno y el house.");  
    insertarGeneroMusical("GNM8", "Classical", "Género de música académica, con composiciones extensas y complejas, predominante en Europa desde el siglo XVIII.");  
    insertarGeneroMusical("GNM9", "Country", "Género originario del sur de Estados Unidos, con letras sobre la vida cotidiana y uso frecuente de guitarras acústicas.");  
    insertarGeneroMusical("GNM10", "Metal", "Género derivado del rock, caracterizado por guitarras distorsionadas, ritmos potentes y letras intensas.");  
   
    agregarPlaylist("PL10", "Canciones Divertidas", "Alberto_elMejor1234", 23042022);
    agregarPlaylist("PL11", "Rock Clásico", "JuanRockero89", 15052021);
    agregarPlaylist("PL12", "Pop Latino", "MusicaLatina2022", 10122023);
    agregarPlaylist("PL13", "Relax y Meditación", "SerenidadTotal", 17082020);
    agregarPlaylist("PL14", "Electro Hits", "DJ_Manuel", 25062019);
    agregarPlaylist("PL15", "Indie Vibes", "AuroraMusic", 12072022);
    agregarPlaylist("PL16", "Baladas Románticas", "CorazonMelodico", 14022021);
    agregarPlaylist("PL17", "Jazz & Blues", "BlueSoul", 30112020);
    agregarPlaylist("PL18", "Clásicos de los 80s", "RetroWave", 8031990);
    agregarPlaylist("PL19", "Workout Power", "FitLife2023", 01012023);

    insertarSellosDiscograficos("SLL1", "Warner Records", "Estados Unidos", 2024);
    insertarSellosDiscograficos("SLL2", "Sony Music", "Japón", 2020);
    insertarSellosDiscograficos("SLL3", "Universal Music", "Estados Unidos", 2023);
    insertarSellosDiscograficos("SLL4", "EMI Records", "Reino Unido", 2019);
    insertarSellosDiscograficos("SLL5", "Atlantic Records", "Estados Unidos", 2022);
    insertarSellosDiscograficos("SLL6", "Capitol Records", "Estados Unidos", 2021);
    insertarSellosDiscograficos("SLL7", "Columbia Records", "Estados Unidos", 2020);
    insertarSellosDiscograficos("SLL8", "Def Jam Recordings", "Estados Unidos", 2023);
    insertarSellosDiscograficos("SLL9", "Motown Records", "Estados Unidos", 2022);
    insertarSellosDiscograficos("SLL10", "Island Records", "Reino Unido", 2021);

    insertarArtistaOrdenAlfabeticamente("ART1", "Billie Eilish", "Billie Eilish Pirate Baird O'Connell", "Estados Unidos", "EMI Records");
    insertarArtistaOrdenAlfabeticamente("ART2", "Taylor Swift", "Taylor Alison Swift", "Estados Unidos", "Universal Music");
    insertarArtistaOrdenAlfabeticamente("ART3", "Drake", "Aubrey Drake Graham", "Canadá", "Def Jam Recordings");
    insertarArtistaOrdenAlfabeticamente("ART4", "Dua Lipa", "Dua Lipa", "Reino Unido", "Warner Records");
    insertarArtistaOrdenAlfabeticamente("ART5", "The Weeknd", "Abel Makkonen Tesfaye", "Canadá", "Capitol Records");
    insertarArtistaOrdenAlfabeticamente("ART6", "Adele", "Adele Laurie Blue Adkins", "Reino Unido", "Columbia Records");
    insertarArtistaOrdenAlfabeticamente("ART7", "Ed Sheeran", "Edward Christopher Sheeran", "Reino Unido", "Atlantic Records");
    insertarArtistaOrdenAlfabeticamente("ART8", "Imagine Dragons", "Imagine Dragons", "Estados Unidos", "Island Records");
    insertarArtistaOrdenAlfabeticamente("ART9", "Coldplay", "Coldplay", "Reino Unido", "EMI Records");
    insertarArtistaOrdenAlfabeticamente("ART10", "Bruno Mars", "Peter Gene Hernandez", "Estados Unidos", "Atlantic Records");


    insertarFinalAlbum("ART1", "ALB1", "Happier Than Ever", 2021, 4);// Billie Eilish
    insertarFinalAlbum("ART2", "ALB2", "Midnights", 2022, 5); // Taylor Swift
    insertarFinalAlbum("ART3", "ALB3", "Certified Lover Boy", 2021, 4); // Drake
    insertarFinalAlbum("ART4", "ALB4", "Future Nostalgia", 2020, 4); // Dua Lipa
    insertarFinalAlbum("ART5", "ALB5", "After Hours", 2020, 4);// The Weeknd
    insertarFinalAlbum("ART6", "ALB6", "30", 2021, 3);// Adele
    insertarFinalAlbum("ART7", "ALB7", "Divide", 2017, 4);// Ed Sheeran
    insertarFinalAlbum("ART8", "ALB8", "Evolve", 2017, 4);// Imagine Dragons
    insertarFinalAlbum("ART9", "ALB9", "Music of the Spheres", 2021, 4); // Coldplay
    insertarFinalAlbum("ART10", "ALB10", "24K Magic", 2016, 4);// Bruno Mars

    // insertarCancion("ART1", "ALB1");  // Billie Eilish
    // insertarCancion("ART2", "ALB2");  // Taylor Swift
    // insertarCancion("ART3", "ALB3");  // Drake
    // insertarCancion("ART4", "ALB4");  // Dua Lipa
    // insertarCancion("ART5", "ALB5");  // The Weeknd
    // insertarCancion("ART6", "ALB6");  // Adele
    // insertarCancion("ART7", "ALB7");  // Ed Sheeran
    // insertarCancion("ART8", "ALB8");  // Imagine Dragons
    // insertarCancion("ART9", "ALB9");  // Coldplay
    // insertarCancion("ART10", "ALB10");  // Bruno Mars
}




int main() {
    cargarDatos();
    menuGeneral();
    return 0;
}
