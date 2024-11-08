#include "stdlib.h"
#include "stdio.h"
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
        
        size_t contador = 0;
        for (size_t i = 0; i < hash->capacidad; i++)
                contador += abb_cantidad(hash->tabla[i]);
        return contador;
}

static size_t funcion_hash(unsigned char *str){
        unsigned long hash = 5381;
        unsigned long c = *str++;

        while (c){
                hash = ((hash << 5) + hash*c) + c;
                c = *str++;
        }
        return hash;
}


void* hash_buscar(hash_t* hash, char* clave){
        if (!hash || !clave)
                return NULL;
        size_t indice = funcion_hash((unsigned char *)clave) % hash->capacidad;
        pares_t pares;
        pares_t *pares2 = NULL;
        pares.clave = clave;
        pares2 = (pares_t*)abb_obtener(hash->tabla[indice],&pares);
        if (pares2)
                return pares2->valor;
        
        return NULL;
}

bool hash_contiene(hash_t* hash, char* clave){
        if (!hash || !clave)
                return false;
        size_t indice = funcion_hash((unsigned char *)clave) % hash->capacidad;
        pares_t pares;
        pares.clave = clave;
        if( abb_obtener(hash->tabla[indice],&pares) != NULL)
                return true;       
        return false;
}

bool modificar_valor_par(void *elemento, void *ctx){
        pares_t *pares_elem = elemento;
        pares_t *pares = ctx;
        if (pares_elem->clave == pares->clave){
                pares_elem->valor = pares->valor;
                return false;
        }
        return true;
}


bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado){
        if (!hash || !clave)
                return false;
        size_t indice = funcion_hash((unsigned char *)clave) % hash->capacidad;
        char *copia_clave = calloc(strlen(clave) + 1,sizeof(char));
        for(int i = 0; i < strlen(clave) + 1;i++)
                copia_clave[i] = clave[i];
        pares_t pares2;
        pares2.clave = copia_clave;
        pares2.valor = valor; 
        if (encontrado && hash_contiene(hash,clave)){
                abb_iterar_inorden(hash->tabla[indice],modificar_valor_par,&pares2);
        }
        pares_t *pares = calloc(1,sizeof(pares_t));
        pares->clave = copia_clave;
        pares->valor = valor; 

        
        return abb_insertar(hash->tabla[indice],pares);
}


size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx){
        return 0;
}

static bool destruir_claves(void *pares_, void *ctx){
        pares_t *pares = pares_;
        free(pares->clave);
        return true;
}

static void destruir_pares(void *pares_){
        pares_t *pares = pares_;
        free(pares);
}

void hash_destruir(hash_t* hash){
        if (!hash)
                return;
        
        for (size_t i = 0; i < hash->capacidad; i++){
                abb_iterar_inorden(hash->tabla[i],destruir_claves,NULL);
                abb_destruir_todo(hash->tabla[i],destruir_pares);
        }
        free(hash->tabla);
        free(hash);
}

void hash_destruir_todo(hash_t* hash, void (*destructor)(void*)){
        if (!hash)
                return;
                
        for (size_t i = 0; i < hash->capacidad; i++){
                abb_iterar_inorden(hash->tabla[i],destruir_claves,NULL);
                abb_destruir_todo(hash->tabla[i],destructor);
                }
        free(hash->tabla);
        free(hash);
}