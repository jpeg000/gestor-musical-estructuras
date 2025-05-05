#include <iostream>
using namespace std;

/*  Fecha de Inicio: 17/4/2025
    Integrantes:
    - Jose Pablo Avendaño Zúñiga
    - José Andres Villegas Murillo

    Descripción de Estructuras:

    Descripción de cada función:
*/

struct Canciones {
    string id;
    string titulo;
    int duracion;
    int year;
    string idAlbum;
    string idArtista;

    Canciones *siguiente;

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

struct Artistas {
    string id;
    string nombreArtistico;
    string nombreReal;
    string pais;
    string selloDiscografico;

    Artistas *siguiente, *anterior;

    /* SUBLISTAS */
    struct Canciones *canciones;
    struct Albumes *albumes;

    /* CONSTRUCTOR */
    Artistas(string idP, string nombreA, string nombreR, string paisP, string selloDisc) {
        id = idP;
        nombreArtistico = nombreA;
        nombreReal = nombreR;
        pais = paisP;
        selloDiscografico = selloDisc;
        siguiente = NULL;
        anterior = NULL;
        canciones = NULL;
        albumes = NULL;
    }
} *primerA;

struct Albumes {
    string id;
    string titulo;
    int year;
    int numeroCanciones;

    Albumes *siguiente;

    /* SUBLISTAS */
    struct Canciones *canciones;

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

struct GenerosMusicales {
    string id;
    string nombre;
    string descripcion;

    GenerosMusicales *siguiente;

    /* SUBLISTAS */
    struct Canciones *canciones;

    /* CONSTRUCTOR */
    GenerosMusicales(string idP, string nombreP, string desc) {
        id = idP;
        nombre = nombreP;
        descripcion = desc;
        siguiente = NULL;
        canciones = NULL;
    }
} *primerG;

struct Playlist {
    string id;
    string nombre;
    string creador;
    int fecha;

    Playlist *siguiente;

    /* SUBLISTAS */
    struct Canciones *canciones;

    /* CONSTRUCTOR */
    Playlist(string idP, string nombreP, string creadorP, int fechaP) {
        id = idP;
        nombre = nombreP;
        creador = creadorP;
        fecha = fechaP;
        siguiente = NULL;
        canciones = NULL;
    }
} *primerP;

struct SellosDiscograficos {
    string id;
    string nombre;
    string pais;
    int year;

    SellosDiscograficos *siguiente, *anterior;

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
} *primerS;

struct enlaceSellosArtistas {

    enlaceSellosArtistas *siguiente;
    struct Artistas *enlace;

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
struct Artistas* buscarArtistas(string ide){
    if (primerA == NULL){
        return NULL;
    }
    struct Artistas* temp = primerA;
    while (temp != NULL){
        if (temp->id == ide){
            return temp;
        } else {
            temp = temp -> siguiente;
        }
    }
    return NULL;
}

struct SellosDiscograficos* buscarSellos(string ide) {
    if (primerS == NULL) {
        return NULL;
    }
    struct SellosDiscograficos* temp = primerS;
    do {
        if (temp->id == ide) {
            return temp;
        }
        temp = temp->siguiente;
    } while (temp != primerS);
    return NULL;
}

struct SellosDiscograficos *buscarSelloPorNombre(string n) {

    if (primerS == NULL) {
        return NULL;
    }

    struct SellosDiscograficos *temp = primerS;

    do {
        if (temp -> nombre == n) {
            return temp;
        }
        temp = temp -> siguiente;
    } while (temp != primerS);
    return NULL;
};

struct Albumes *buscarAlbumes(string idArtista, string idAlbum) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        return NULL;
    }
    struct Albumes *temp = nodoArtista -> albumes;
    while (temp != NULL) {
        if (temp -> id == idAlbum) {
            return temp;
        }
        temp = temp -> siguiente;
    }
    return NULL;
}
struct GenerosMusicales* buscarGeneroMusical(string ide){
    if (primerG == NULL){
        return NULL;
    }
    GenerosMusicales* temp = primerG;
    do{
        if (temp -> id == ide){
            return temp;
        }
        temp = temp -> siguiente;
    }while(temp != primerG);
    return NULL;
}

struct Canciones *buscarCancion(string idArtista, string idAlbum, string idCancion) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    if (nodoArtista == NULL) {
        return NULL;
    }
    struct Albumes *nodoAlbum = nodoArtista -> albumes;
    if (nodoAlbum == NULL) {
        return NULL;
    }
    struct Canciones *temp = nodoArtista -> albumes -> canciones;

    while (temp != NULL) {
        if (temp -> id == idCancion) {
            return temp;
        }
        temp = temp -> siguiente;
    }
    return NULL;
}

struct Playlist* buscarPlaylist(string ide){
    if (primerP == NULL){
        cout << "No hay playlists registradas" << endl;
        return NULL;
    }
    struct Playlist* temp = primerP;
    while (temp != NULL){
        if (temp->id == ide){
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}


/*
=========
SELLO DISCOGRAFICO
=========
*/
void insertarSellosDiscograficos(string id, string nombre, string pais, int anoFund){
    if (buscarSelloPorNombre(nombre) != NULL){
        cout << "El nombre de este sello ya existe" << endl;
        return;
    }
    SellosDiscograficos* newSello = new SellosDiscograficos(id, nombre, pais, anoFund);
    if (primerS == NULL){
        primerS = newSello;
        newSello->siguiente = newSello;
        newSello->anterior = newSello;
    } else {
        SellosDiscograficos* temp = primerS->anterior;
        temp->siguiente = newSello;
        newSello->anterior = temp;
        newSello->siguiente = primerS;
        primerS->anterior = newSello;
    }
    cout << "Sello discográfico agregado correctamente." << endl;
}


void modificarNombredeSello(string ide,string newNombre){
    SellosDiscograficos* SelloDisc = buscarSellos(ide);
    if (SelloDisc == NULL){
        cout << "El sello discográfico no existe"<<endl;
        }
    else{
    SelloDisc -> nombre = newNombre;
    cout << "Nombre del sello discográfico modificado correctamente"<<endl;
        }
}

void modificarPaisdeSello(string ide,string newPais){
    SellosDiscograficos* SelloDisc = buscarSellos(ide);
    if (SelloDisc == NULL){
        cout << "El sello discográfico no existe"<<endl;
    }else{
        SelloDisc -> pais = newPais;
        cout << "País del sello discográfico modificado correctamente"<<endl;
    }
}

void eliminarSelloDiscografico(string ide) {
    SellosDiscograficos* selloDisc = buscarSellos(ide);
    if (selloDisc == NULL) {
        cout << "El sello discográfico no está registrado"<<endl;
        return;
    }
    if (selloDisc->siguiente == selloDisc && selloDisc->anterior == selloDisc) {
        delete selloDisc;
        primerS = NULL;
    }
    else {
        selloDisc->anterior->siguiente = selloDisc->siguiente;
        selloDisc->siguiente->anterior = selloDisc->anterior;

        if (selloDisc == primerS) {
            primerS = selloDisc->siguiente;
        }
        delete selloDisc;
    }
}

void insertarArtistaEnSello(string idArtista, string idSelloDisc) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    struct SellosDiscograficos *nodoSello = buscarSellos(idSelloDisc);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    if (nodoSello == NULL) {
        cout << "El sello discográfico ID " << idSelloDisc << " no está registrado." << endl;
        return;
    }

    enlaceSellosArtistas *temp = nodoSello->sublistaArtista;
    while (temp != NULL) {
        if (temp->enlace->id == nodoArtista->id) {  // Verifica si ya está vinculado
            cout << "El artista ya está vinculado a este sello discográfico." << endl;
            return;
        }
        temp = temp->siguiente;
    }

    enlaceSellosArtistas *enlace = new enlaceSellosArtistas(nodoArtista);
    enlace->siguiente = nodoSello->sublistaArtista;
    nodoSello->sublistaArtista = enlace;
    nodoArtista->selloDiscografico = nodoSello->nombre;
}



void eliminarArtistaDeSello(string idArtista, string idSelloDisc) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    struct SellosDiscograficos *nodoSello = buscarSellos(idSelloDisc);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe."<< endl;
        return;
    }

    if (nodoSello == NULL) {
        cout << "El sello discográfico ID " << idSelloDisc << " no está registrado."<< endl;
        return;
    }

    if (nodoArtista -> selloDiscografico != nodoSello -> nombre) {
        cout << "El artista no esta asociado a ese sello discográfico." << endl;
        return;
    }

    struct enlaceSellosArtistas *actual = nodoSello -> sublistaArtista;
    struct enlaceSellosArtistas *anterior = NULL;

    while (actual != NULL) {
        if (actual -> enlace == nodoArtista) {
            if (anterior == NULL) {
                nodoSello -> sublistaArtista = actual -> siguiente;
            }
            else {
                anterior -> siguiente = actual -> siguiente;
            }
            delete actual;
            nodoArtista -> selloDiscografico = "";
            cout << "El artista " << nodoArtista -> nombreArtistico <<
                " ha sido eliminado del Sello Artístico " << nodoSello -> nombre << "." << endl;
            return;
        }

        anterior = actual;
        actual = actual -> siguiente;
    }
}

/*
=========
ARTISTAS
=========
*/
void insertarArtistaOrdenAlfabeticamente(string id, string nombreArt, string nombreReal, string pais, string selloDisc) {
    struct Artistas *existeArtista = buscarArtistas(id);
    struct SellosDiscograficos *nodoSello = buscarSelloPorNombre(selloDisc);

    if (existeArtista != NULL) {
        cout << "El artista con el ID " << id << " ya existe." << endl;
        return;
    }
    if (nodoSello == NULL){
        cout << "El sello con el nombre" << selloDisc << " no existe." << endl;
        return;
    }
    struct Artistas *nuevoArtista = new Artistas(id, nombreArt, nombreReal, pais, selloDisc);
    if (primerA == NULL) {
        primerA = nuevoArtista;
        return;
    }
    if (nombreArt < primerA -> nombreArtistico) {
        nuevoArtista -> siguiente = primerA;
        primerA -> anterior = nuevoArtista;
        primerA = nuevoArtista;
        return;
    }
    Artistas *temp = primerA;
    while (temp -> siguiente != NULL && temp -> siguiente -> nombreArtistico < nombreArt) {
        temp = temp -> siguiente;
    }

    nuevoArtista -> siguiente = temp -> siguiente;
    nuevoArtista -> anterior = temp;

    if (temp -> siguiente != NULL) {
        temp -> siguiente -> anterior = nuevoArtista;
    }

    temp -> siguiente = nuevoArtista;

    insertarArtistaEnSello(id, nodoSello -> id);
}

void modificarNombreArtisticoDeArtista(string ide, string nombre){
    Artistas* nodoArtista = buscarArtistas(ide);
    if (nodoArtista == NULL){
        cout << "El artista no existe" << endl;
    } else {
        nodoArtista->nombreArtistico = nombre;
        cout << "Nombre artístico actualizado correctamente." << endl;
    }
}

void modificarPaisDeArtista(string ide, string paisNuevo){
    Artistas* nodoArtista = buscarArtistas(ide);
    if (nodoArtista == NULL){
        cout << "El artista no existe" << endl;
    } else {
        nodoArtista->pais = paisNuevo;
        cout << "País actualizado correctamente." << endl;
    }
}

void modificarSelloDiscograficoDeArtista(string idArtista, string idSelloNuevo) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    struct SellosDiscograficos *nodoSelloNuevo = buscarSellos(idSelloNuevo);
    struct SellosDiscograficos *nodoSelloAnterior = buscarSelloPorNombre(nodoArtista -> selloDiscografico);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    if (nodoSelloNuevo == NULL) {
        cout << "El sello ID " << idSelloNuevo << " no existe." << endl;
        return;
    }

    eliminarArtistaDeSello(idArtista, nodoSelloAnterior->id);
    insertarArtistaEnSello(idArtista, idSelloNuevo);
    cout << "El sello discográfico del artista " << nodoArtista -> nombreArtistico <<
        " se modificó exitosamente"<< endl;
}

void eliminarArtista(string ide){
    Artistas* nodoArtista = buscarArtistas(ide);
    if (nodoArtista == NULL){
        cout << "El artista no existe" << endl;
    } else {
        if (nodoArtista->anterior != NULL){
            nodoArtista->anterior->siguiente = nodoArtista->siguiente;
        } else {
            primerA = nodoArtista->siguiente;
        }
        if (nodoArtista->siguiente != NULL){
            nodoArtista->siguiente->anterior = nodoArtista->anterior;
        }
        delete nodoArtista;
        cout << "Artista eliminado correctamente." << endl;
    }
}

/*
=========
ALBUMES
=========
*/
void insertarFinalAlbum(string idArtista, string idAlbum, string titulo, int year, int numCanciones) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    struct Albumes *nuevoAlbum = new Albumes(idAlbum, titulo, year, numCanciones);
    if (buscarAlbumes(idArtista,idAlbum)){
        cout << "El album ya está registrado en el artista."<<endl;
        return;
    }

    if (nodoArtista -> albumes == NULL) {
        nodoArtista -> albumes = nuevoAlbum;
    }

    else {
        struct Albumes *temp = nodoArtista -> albumes;
        while (temp -> siguiente != NULL) {
            temp = temp -> siguiente;
        }
        temp -> siguiente = nuevoAlbum;
    }

    cout << "El albúm " << titulo << " se agregó existosamente al artista " <<
        nodoArtista -> nombreArtistico << "." << endl;
}

void modificarTituloAlbum(string idArtista, string idAlbum, string tituloNuevo) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);

    if (nodoAlbum == NULL) {
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    Albumes *temp = nodoArtista->albumes;
    while (temp != NULL) {
        if (temp != nodoAlbum && temp->titulo == tituloNuevo) {
            cout << "Ya existe un álbum con ese título para este artista." << endl;
            return;
        }
        temp = temp->siguiente;
    }

    nodoAlbum->titulo = tituloNuevo;
    cout << "Se cambió el título del álbum correctamente." << endl;
}


void eliminarAlbum(string idArtista, string idAlbum) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);

    if (nodoAlbum == NULL) {
        cout << "El album con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    struct Albumes *actual = nodoArtista -> albumes;
    struct Albumes *anterior = NULL;

    while (actual != NULL) {
        if (actual -> id == idAlbum) {

            if (anterior == NULL) {
                nodoArtista -> albumes = actual -> siguiente;
            }

            else {
                anterior -> siguiente = actual -> siguiente;
            }

            delete actual;
            cout << "El albúm con el ID " << idAlbum << " se ha eliminado exitosamente " << endl;
            return;
        }

        anterior = actual;
        actual = actual -> siguiente;
    }
}

int cantidadCancionesAlbum(string idArtista, string idAlbum) {
    int cont = 0;
    Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);
    Canciones* temp = nodoAlbum->canciones;
    while (temp != NULL) {
        cont++;
        temp = temp->siguiente;
    }
    return cont;
}

/*
=========
GENEROS MUSICALES
=========
*/
void insertarGeneroMusical(string ID, string nombre, string descripcion) {
    GenerosMusicales* newGenre = new GenerosMusicales(ID, nombre, descripcion);
    if (primerG == NULL) {
        primerG = newGenre;
        newGenre->siguiente = primerG;
        return;
    }
    if (buscarGeneroMusical(ID) != NULL){
        cout << "El genero musical ya está registrado"<<endl;
        return;
    }
    GenerosMusicales* temp = primerG;
    while (temp->siguiente != primerG) {
        temp = temp->siguiente;
    }
    temp->siguiente = newGenre;
    newGenre->siguiente = primerG;
}

void modificarDescripcionGeneroMusical(string ID, string descripcion) {
    GenerosMusicales* generoMusical = buscarGeneroMusical(ID);
    if (generoMusical == NULL) {
        cout << "El género musical no está registrado" << endl;
    } else {
        generoMusical->descripcion = descripcion;
    }
}

void eliminarGeneroMusical(string ID) {
    GenerosMusicales* generoMusical = buscarGeneroMusical(ID);
    if (generoMusical == NULL) {
        cout << "El género musical no existe" << endl;
    } else {
        if (primerG->siguiente == primerG) {
            delete primerG;
            primerG = NULL;
            cout << "Género musical eliminado" << endl;
            return;
        }
        GenerosMusicales* actual = primerG;
        GenerosMusicales* anterior = NULL;
        do {
            if (actual->id == ID) {
                if (actual == primerG) {
                    GenerosMusicales* ultimo = primerG;
                    while (ultimo->siguiente != primerG) {
                        ultimo = ultimo->siguiente;
                    }
                    primerG = primerG->siguiente;
                    ultimo->siguiente = primerG;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                cout << "Género eliminado correctamente." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        } while (actual != primerG);
    }
}

/*
=========
CANCIONES
=========
*/
void insertarCancion(string idArtista, string idAlbum, string idCancion, string titulo, int duracion, int year) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);
    struct Canciones *nodoCancion = buscarCancion(idArtista, idAlbum, idCancion);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    if (nodoAlbum == NULL) {
        cout << "El album con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    if (nodoCancion != NULL) {
        cout << "La canción con el ID " << idCancion << " ya existe." << endl;
        return;
    }

    struct Canciones *nuevaCancion = new Canciones(idCancion, titulo, duracion, year, idArtista, idAlbum);

    nuevaCancion -> siguiente = nodoAlbum -> canciones;
    nodoAlbum -> canciones = nuevaCancion;
    nodoAlbum -> numeroCanciones++;

    cout << "La canción " << titulo << " fue agregada correctamente al albúm con ID " << idAlbum << "." <<endl;
}

void modificarTituloCancion(string idArtista, string idAlbum, string idCancion, string nuevoTitulo) {
    struct Artistas *nodoArtista = buscarArtistas(idArtista);
    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);
    struct Canciones *nodoCancion = buscarCancion(idArtista, idAlbum, idCancion);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    if (nodoAlbum == NULL) {
        cout << "El álbum con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    if (nodoCancion == NULL) {
        cout << "La canción con el ID " << idCancion << " no existe." << endl;
        return;
    }

    // Verificar que no exista otra canción con el nuevo título en el mismo álbum
    Canciones *temp = nodoAlbum->canciones;
    while (temp != NULL) {
        if (temp != nodoCancion && temp->titulo == nuevoTitulo) {
            cout << "Ya existe una canción con ese título en este álbum." << endl;
            return;
        }
        temp = temp->siguiente;
    }

    string tituloAntiguo = nodoCancion->titulo;
    nodoCancion->titulo = nuevoTitulo;

    cout << "El título de la canción " << tituloAntiguo << " ha sido cambiado por " << nuevoTitulo << " exitosamente." << endl;
}


void eliminarCancion(string idArtista, string idAlbum, string idCancion) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    struct Albumes *nodoAlbum = buscarAlbumes(idArtista, idAlbum);

    if (nodoAlbum == NULL) {
        cout << "El album con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    struct Canciones *nodoCancion = buscarCancion(idArtista, idAlbum, idCancion);

    if (nodoCancion == NULL) {
        cout << "La canción con el ID " << idCancion << " no existe." << endl;
        return;
    }

    struct Canciones *actual = nodoAlbum -> canciones;
    struct Canciones *anterior = NULL;

    while (actual != NULL) {
        if (actual -> id == idCancion) {

            if (anterior == NULL) {
                nodoAlbum -> canciones = actual -> siguiente;
            }

            else {
                anterior -> siguiente = actual -> siguiente;
            }

            delete actual;
            cout << "La canción con el ID " << idCancion << " se ha eliminado correctamente." << endl;
            return;
        }

        anterior = actual;
        actual = actual -> siguiente;
    }
}

/*
========
PLAYLIST
========
*/
void agregarPlaylist(string id,string nombre,string creador,int fecha){
    struct Playlist* nodoPlaylist = buscarPlaylist(id);
    if (nodoPlaylist != NULL){
        cout << "La playlist con ID:" << nodoPlaylist -> id <<" ya existe"<<endl;
    }
    struct Playlist* newPlaylist = new Playlist(id,nombre,creador,fecha);
    if (primerP == NULL){
        primerP = newPlaylist;
        return;
    }
    newPlaylist -> siguiente = primerP;
    primerP = newPlaylist;
}

void modificarNombrePlaylist(string id,string name){
    struct Playlist* playlist = buscarPlaylist(id);
    if (playlist == NULL){
        cout << "La playlist no existe"<<endl;
    }else{
        playlist -> nombre = name;
    }
}
void modificarCreadorPlaylist(string id, string creator){
    struct Playlist *playlist = buscarPlaylist(id);
    if (playlist == NULL){
        cout << "La playlist no existe"<<endl;
    }else{
        playlist -> creador = creator;
    }
}

void eliminarPlaylist(string id) {
    Playlist* playlist = buscarPlaylist(id);
    if (playlist == NULL) {
        cout << "La playlist no existe" << endl;
    } else {
        Playlist* actual = primerP;
        Playlist* anterior = NULL;

        while (actual != NULL) {
            if (actual->id == id) {
                if (anterior == NULL) {
                    primerP = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                cout << "Playlist eliminada correctamente." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

/*
=========
CONSULTAS
=========
*/

void generoMayorCanciones() {
    if (primerG == NULL) {
        cout << "No hay géneros registrados" << endl;
        return;
    }

    GenerosMusicales* temp = primerG;
    int max = 0;
    bool primeraVuelta = true;

    do {
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
        primeraVuelta = false;
    } while (temp != primerG && (temp != NULL || primeraVuelta));

    if (max == 0) {
        cout << "No hay canciones registradas en ningún género." << endl;
        return;
    }

    temp = primerG;
    primeraVuelta = true;
    cout << "Géneros con más canciones (" << max << " canciones):" << endl;
    do {
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
        primeraVuelta = false;
    } while (temp != primerG && (temp != NULL || primeraVuelta));
}

void artistaMaxAlbumes() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados" << endl;
        return;
    }
    Artistas* temp = primerA;
    int max = 0;

    while (temp != NULL) {
        int cont = 0;
        Albumes* temp2 = temp->albumes;
        while (temp2 != NULL) {
            cont++;
            temp2 = temp2->siguiente;
        }
        if (cont > max) {
            max = cont;
        }
        temp = temp->siguiente;
    }
    if (max == 0) {
        cout << "Ningún artista tiene álbumes registrados" << endl;
        return;
    }

    cout << "Artistas con más álbumes (" << max << "):" << endl;
    temp = primerA;
    while (temp != NULL) {
        int cont = 0;
        Albumes* temp2 = temp->albumes;
        while (temp2 != NULL) {
            cont++;
            temp2 = temp2->siguiente;
        }
        if (cont == max) {
            cout << "- " << temp->nombreArtistico << endl;
        }
        temp = temp->siguiente;
    }
}


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

        Canciones* singles = temp->canciones;
        while (singles != NULL) {
            if (singles->duracion > maxTiempo) {
                maxTiempo = singles->duracion;
            }
            singles = singles->siguiente;
        }

        temp = temp->siguiente;
    }

    GenerosMusicales* temp2 = primerG;
    while (temp2 != NULL) {
        Canciones* cancion = temp2->canciones;
        while (cancion != NULL) {
            if (cancion->duracion > maxTiempo) {
                maxTiempo = cancion->duracion;
            }
            cancion = cancion->siguiente;
        }
        temp2 = temp2->siguiente;
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

        Canciones* singles = temp->canciones;
        while (singles != NULL) {
            if (singles->duracion == maxTiempo) {
                cout << "- " << singles->titulo << endl;
            }
            singles = singles->siguiente;
        }

        temp = temp->siguiente;
    }

    temp2 = primerG;
    while (temp2 != NULL) {
        Canciones* cancion = temp2->canciones;
        while (cancion != NULL) {
            if (cancion->duracion == maxTiempo) {
                cout << "- " << cancion->titulo << endl;
            }
            cancion = cancion->siguiente;
        }
        temp2 = temp2->siguiente;
    }
}


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


void albumesPorArtista(){
    if (primerA == NULL){
        cout << "No hay artistas registrados"<<endl;
        return;
    }
    Artistas *artista = primerA;
    while (artista != NULL){
        int cont = 0;
        Albumes *temp = artista -> albumes;
        while (temp != NULL){
            cont++;
            temp = temp -> siguiente;
        }
        cout << artista ->nombreArtistico << "tiene " << cont << "álbumes registrados"<<endl;
        artista = artista -> siguiente;
    }
}

void selloDiscograficoConMasArtistas() {
    if (primerS == NULL) {
        cout << "No hay sellos discográficos registrados" << endl;
        return;
    }

    SellosDiscograficos *selloDiscografico = primerS;
    SellosDiscograficos *selloDiscMaxArtistas = NULL;
    int max = 0;

    while (selloDiscografico != NULL) {
        int contador = 0;
        enlaceSellosArtistas *enlace = selloDiscografico->sublistaArtista;
        while (enlace != NULL) {
            contador++;
            enlace = enlace->siguiente;
        }
        if (contador > max) {
            max = contador;
            selloDiscMaxArtistas = selloDiscografico;
        }
        selloDiscografico = selloDiscografico->siguiente;
    }

    if (selloDiscMaxArtistas != NULL) {
        cout << "El sello discográfico con más artistas firmados es "
             << selloDiscMaxArtistas->nombre << " (" << max << " artistas)" << endl;
    }
}

void cancionesPublicadasYear(int year1) {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay canciones" << endl;
        return;
    }
    Artistas *artistas = primerA;
    bool hayCanciones = false;

    while (artistas != NULL) {
        Albumes *album = artistas->albumes;
        while (album != NULL) {
            Canciones *cancion = album->canciones;
            while (cancion != NULL) {
                if (cancion->year == year1) {
                    hayCanciones = true;
                    cout << "La canción \"" << cancion->titulo << "\" del artista \"" << artistas->nombreArtistico << "\" es del año " << year1 << "." << endl;
                }
                cancion = cancion->siguiente;
            }
            album = album->siguiente;
        }
        artistas = artistas->siguiente;
    }
    if (!hayCanciones) {
        cout << "No se encontraron canciones del año " << year1 << "." << endl;
    }
}

void albumesCantidadCanciones(int cantidad) {
    if (primerA == NULL) {
        cout << "No hay artistas registrados, por lo tanto no hay canciones" << endl;
        return;
    }
    Artistas *artistas = primerA;
    bool hayCanciones = false;

    while (artistas != NULL) {
        Albumes *album = artistas->albumes;
        while (album != NULL) {
            int cont = 0;
            Canciones *cancion = album->canciones;
            while (cancion != NULL) {
                cont++;
                cancion = cancion->siguiente;
            }
            if (cont == cantidad) {
                cout << "El álbum \"" << album->titulo << "\" del artista \""
                     << artistas->nombreArtistico << "\" tiene " << cantidad << " canciones." << endl;
                hayCanciones = true;
            }
            album = album->siguiente;
        }
        artistas = artistas->siguiente;
    }

    if (!hayCanciones) {
        cout << "No hay álbumes con " << cantidad << " canciones." << endl;
    }
}

/*
========
REPORTES
========
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

void imprimirListaGenerosMusicales() {
    if (primerG == NULL) {
        cout << "No hay géneros musicales registrados." << endl;
        return;
    }
    GenerosMusicales *genero = primerG;
    while (genero != NULL) {
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
    }
}

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

void imprimirSellosDiscograficos() {
    if (primerS == NULL) {
        cout << "No hay sellos discográficos registrados." << endl;
        return;
    }
    SellosDiscograficos *sello = primerS;
    while (sello != NULL) {
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
    }
}

void imprimirListasPrincipales() {
    imprimirListaArtistas();
    imprimirListaAlbumes();
    imprimirListaGenerosMusicales();
    imprimirListaPlaylists();
    imprimirSellosDiscograficos();
}

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
        Canciones* nuevo = new Canciones(*temp); // Copia del nodo
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
    string idArtista, idAlbum, idCancion, titulo;
    int duracion, year;
    bool validarDuracion, validarYear = false;

    cout << "Ingrese el ID del artista: " << endl;
    cin >> idArtista;

    cout << "Ingrese el ID del álbum: " << endl;
    cin >> idAlbum;

    cout << "Ingrese un ID para la canción: " << endl;
    cin >> idCancion;

    cout << "Ingrese el título para la canción: " << endl;
    cin.ignore();
    getline(cin, titulo);

    while (!validarDuracion) {
        cout << "Ingrese la duración de la canción (en segundos): ";
        cin >> duracion;

        if (duracion > 0) {
            validarDuracion = true;
        }

        else {
            cout << "Inválido. Ingrese una duración mayor a 0 segundos." << endl;
            cout << "Intente nuevamente." << endl;
        }
    }

    while (!validarYear) {
        cout << "Ingrese el año de publicación de la canción: ";
        cin >> year;

        if (year > 0) {
            validarYear = true;
        }

        else {
            cout << "Inválido. Ingrese un número positivo" << endl;
            cout << "Intente nuevamente." << endl;
        }
    }

    insertarCancion(idArtista, idAlbum, idCancion, titulo, duracion, year);
    cout << endl;
}

void inputModificarTituloCancion() {
    string idArtista, idAlbum, idCancion, nuevoTitulo;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;

    cout << "Ingrese el ID del album: ";
    cin >> idAlbum;

    cout << "Ingrese el ID de la canción a modificar: ";
    cin >> idCancion;

    cout << "Ingrese el nuevo título de la canción: ";
    cin.ignore();
    getline(cin, nuevoTitulo);

    modificarTituloCancion(idArtista, idAlbum, idCancion, nuevoTitulo);
    cout << endl;
}

void inputEliminarCancion() {
    string idArtista, idAlbum, idCancion;

    cout << "Ingrese el ID del artista: ";
    cin >> idArtista;

    cout << "Ingrese el ID del album: ";
    cin >> idAlbum;

    cout << "Ingrese el ID de la canción a eliminar: ";
    cin >> idCancion;

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

void inputInsertarAlbum(){
    string idArtista, idAlbum,titulo;
    int year, numCanciones;

    cout <<"Ingrese el ID del artista: ";
    cin >> idArtista;
    cin.ignore();

    cout << "Ingrese el ID del album: ";
    cin >> idAlbum;

    cout << "Ingrese el título del album: ";
    getline(cin,titulo);

    cout << "Ingrese el año de lanzamiento del album: ";
    cin >> year;
    if (year <= 0){
        cout << "El año es inválido, intente nuevamente"<<endl;
    }

    numCanciones = cantidadCancionesAlbum(idArtista,idAlbum);

    insertarFinalAlbum(idArtista,idAlbum,titulo,year,numCanciones);
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
            case 1: imprimirListaArtistas(); break;

            case 2: imprimirListasPrincipales(); break;

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

int main() {
    menuGeneral();
    return 0;
}