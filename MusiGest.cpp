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
    struct enlaceSellosArtista *sublistaArtista;

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
SellosDiscograficos* buscarSellos(string ide) {
    if (primerS == NULL) {
        return NULL;
    }
    SellosDiscograficos* temp = primerS;
    do {
        if (temp->id == ide) { 
            return temp;
        }
        temp = temp->siguiente;
    } while (temp != primerS); 
    return NULL;
}

/*Sello discográfico*/
void insertarSellosDiscográficos(string id,string nombre, int pais,int añoFund){
    SellosDiscograficos* newSello = new SellosDiscograficos(id,nombre,pais,añoFund);
    if (primerS == NULL){
        primerS = newSello;
        newSello -> siguiente = newSello;
        newSello -> anterior = newSello;
    }else{
        SellosDiscograficos* temp = primerS -> anterior;
        temp -> siguiente = newSello;
        newSello -> anterior = temp;
        newSello -> siguiente = primerS;
        primerS -> anterior = newSello;
    }
}

void modificarNombredeSello(string ide,string newNombre){
    SellosDiscograficos* SelloDisc = buscarSellos(ide);
    if (SelloDisc == NULL){
        cout << "El sello discográfico no existe"<<endl;
    }else{
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

void modificarSelloDiscograficoDeArtista(string ide, string selloDiscograficoN){
    Artistas* nodoArtista = buscarArtistas(ide);
    if (nodoArtista == NULL){
        cout << "El artista no existe" << endl;
    } else {
        nodoArtista->selloDiscografico = selloDiscograficoN;
        cout << "Sello discográfico actualizado correctamente." << endl;
    }
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

int main()
{
    return 0;
}
