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


/* SELLO DISCOGRAFICO */
void insertarSellosDiscograficos(string id, string nombre, string pais, int anoFund){
    SellosDiscograficos* newSello = new SellosDiscograficos(id,nombre,pais,anoFund);
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
void insertarArtistaOrdenAlfabeticamente(string id, string nombreArt, string nombreReal, string pais, string selloDisc) {
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
void artistaMaxAlbumes() {
    if (primerA == NULL) {
        cout << "No hay artistas registrados" << endl;
    } else {
        Artistas* temp = primerA;
        Artistas* artistaConMaxAlbumes = NULL;
        int max = -1;
        while (temp != NULL) {
            int cont = 0;
            Albumes* temp2 = temp->albumes;
            while (temp2 != NULL) {
                cont++;
                temp2 = temp2->siguiente;
            }
            if (max < cont) {
                max = cont;
                artistaConMaxAlbumes = temp;
            }
            temp = temp->siguiente;
        }
        cout << "El artista con más álbumes es: " << artistaConMaxAlbumes->nombreArtistico << " (" << max << ")" << endl;
    }
}


/* ALBUMES */
void insertarFinalAlbum(string idArtista, string idAlbum, string titulo, int year, int numCanciones) {

    struct Artistas *nodoArtista = buscarArtistas(idArtista);

    if (nodoArtista == NULL) {
        cout << "El artista con el ID " << idArtista << " no existe." << endl;
        return;
    }

    struct Albumes *nuevoAlbum = new Albumes(idAlbum, titulo, year, numCanciones);

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
        cout << "El album con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    nodoAlbum -> titulo = tituloNuevo;
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
/* GENEROS MUSICALES */
void insertarGeneroMusical(string ID, string nombre, string descripcion) {
    GenerosMusicales* newGenre = new GenerosMusicales(ID, nombre, descripcion);
    if (primerG == NULL) {
        primerG = newGenre;
        newGenre->siguiente = primerG;
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
void generoMayorCanciones() {
    if (primerG == NULL) {
        cout << "No hay géneros registrados" << endl;
    } else {
        GenerosMusicales* temp = primerG;
        GenerosMusicales* generoConMasCanciones = NULL;
        int max = -1;
        do {
            int contador = 0;
            Canciones* temp2 = temp->canciones;
            while (temp2 != NULL) {
                contador++;
                temp2 = temp2->siguiente;
            }
            if (contador > max) {
                max = contador;
                generoConMasCanciones = temp;
            }
            temp = temp->siguiente;
        } while (temp != primerG);
        if (generoConMasCanciones != NULL) {
            cout << "Género con más canciones: " << generoConMasCanciones -> nombre << " (" << max << " canciones)" << endl;
        }
    }
}


/* CANCIONES */

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
        cout << "El album con el ID " << idAlbum << " no existe." << endl;
        return;
    }

    if (nodoCancion == NULL) {
        cout << "La canción con el ID " << idCancion << " no existe." << endl;
        return;
    }

    string tituloAntiguo = nodoCancion -> titulo;
    nodoCancion -> titulo = nuevoTitulo;

    cout << "El titulo de la canción " << tituloAntiguo << " ha sido cambiada por " << nuevoTitulo
        << " exitosamente." << endl;
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
/* Playlist*/
void agregarPlaylist(string id,string nombre,string creador,int fecha){
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



int main() {
    return 0;
}
