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
    }
} *primerP;

struct SellosDiscograficos {
    string id;
    string nombre;
    string pais;
    int year;

    SellosDiscograficos *siguiente, *anterior;

    /* SUBLISTAS */
    struct Canciones *canciones;

    /* CONSTRUCTOR */
    SellosDiscograficos(string idP, string nombreP, string paisP, int yearP) {
        id = idP;
        nombre = nombreP;
        pais = paisP;
        year = yearP;
        siguiente = NULL;
        anterior = NULL;
    }
};

/* AUXILIARES */
Artistas* buscarArtistas(string ide){
    if (primerA == NULL){
        return NULL;
    }
    Artistas* temp = primerA;
    while (temp != NULL){
        if (temp->id == ide){
            return temp;
        } else {
            temp = temp -> siguiente;
        }
    }
    return NULL;
}

/* ARTISTAS */
void insertarOrdenAlfabeticamente(string id, string nombreArt, string nombreReal, string pais, string selloDisc) {

    if (buscarArtistas(id) != NULL) {
        cout << "El artista con el ID " << id << " ya existe." << endl;
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
}

int main()
{
    return 0;
}
