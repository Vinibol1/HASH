#include "stdlib.h"
#include "string.h"
#include "hash.h"
#include "abb.h"

typedef struct pares
{
        char *clave;
        void *valor;
} pares_t;


struct hash
{
        abb_t **tabla;
        size_t capacidad; 
};

static int comparador(void *elemento_, void *elemento_agregado_){
        pares_t *elemento = elemento_;
        pares_t *elemento_agregado = elemento_agregado_;
        return strcmp(elemento->clave,elemento_agregado->clave);
}

hash_t* hash_crear(size_t capacidad_inicial){
        if (capacidad_inicial < 3)
                capacidad_inicial = 3;
        
        hash_t *hash = calloc(1,sizeof(hash_t));
        hash->capacidad = capacidad_inicial;
        hash->tabla = calloc(capacidad_inicial,sizeof(void*));
        for (size_t i = 0; i < capacidad_inicial; i++)
              hash->tabla[i] = abb_crear(comparador);  
        
        return hash;
}

size_t hash_cantidad(hash_t* hash){
        if (!hash)
                return 0;
        
        size_t contador;
        for (size_t i = 0; i < hash->capacidad; i++)
                contador += abb_cantidad(hash->tabla[i]);
        return contador;
}

static size_t funcion_hash(char *clave){
        return 0;
}

bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado){
        if (!hash || !clave)
                return false;
        size_t indice = funcion_hash(clave) % hash->capacidad;
        char copia_clave;
        strcpy(&copia_clave,clave);
        pares_t *pares = calloc(1,sizeof(pares_t));
        pares->clave = &copia_clave;
        pares->valor = valor; 
        return abb_insertar(hash->tabla[indice],pares);
}


void* hash_buscar(hash_t* hash, char* clave){
        if (!hash || !clave)
                return NULL;
        for (size_t i = 0; i < hash->capacidad; i++)
                return abb_obtener(hash->tabla[i],clave);
        return NULL;
}

bool hash_contiene(hash_t* hash, char* clave){
        if (!hash || !clave)
                return false;
        for (size_t i = 0; i < hash->capacidad; i++)
                if(abb_obtener(hash->tabla[i],clave) != NULL)
                        return true;       
        return false;
}

size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx){
        return 0;
}



void hash_destruir(hash_t* hash){
        if (!hash)
                return
        
        for (size_t i = 0; i < hash->capacidad; i++)
                abb_destruir(hash->tabla[i]);
        free(hash->tabla);
        free(hash);
}

void hash_destruir_todo(hash_t* hash, void (*destructor)(void*)){
        if (!hash)
                return;
                
        for (size_t i = 0; i < hash->capacidad; i++)
                abb_destruir_todo(hash->tabla[i],destructor);
        free(hash->tabla);
        free(hash);
}