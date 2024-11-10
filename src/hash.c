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
        if (!hash)
                return NULL;
        
        hash->capacidad = capacidad_inicial;
        hash->tabla = calloc(capacidad_inicial,sizeof(void*));
        if (!hash->tabla){
                free(hash);
                return NULL;
        }
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


double hash_factor_de_carga(hash_t* hash)
{
        return  (double)hash_cantidad(hash)/(double)hash->capacidad;
}


static size_t funcion_hash(unsigned char *str){
        unsigned long hash = 5381;
        unsigned long c = *str;

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
        if (strcmp((char*)pares_elem->clave,(char*)pares->clave) == 0){
                pares_elem->valor = pares->valor;
                return false;
        }
        return true;
}


bool reposisionar_pares(char *clave,void *elemento, void*ctx_){
        hash_insertar((hash_t *)ctx_,clave,elemento,NULL);
        return true;
}

void rehash(hash_t *hash)
{
        hash_t *nuevo_hash = hash_crear(hash->capacidad*2);

        hash_iterar(hash,reposisionar_pares,nuevo_hash);

        for (size_t i = 0; i < hash->capacidad; i++){
                abb_iterar_inorden(hash->tabla[i],destruir_claves,NULL);
                abb_destruir_todo(hash->tabla[i],destruir_pares);
        }
        free(hash->tabla);
        hash->tabla = nuevo_hash->tabla;
        hash->capacidad = nuevo_hash->capacidad;
        free(nuevo_hash);
        return ;
}

        
        
        



bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado){
        if (!hash || !clave)
                return false;
        
        size_t indice = funcion_hash((unsigned char *)clave) % hash->capacidad;
        pares_t pares2;
        pares2.clave = clave;
        pares2.valor = valor; 
        if (hash_contiene(hash,clave)){
                encontrado = hash_buscar(hash,clave);
                abb_iterar_inorden(hash->tabla[indice],modificar_valor_par,&pares2);
                return true;
        }
        char *copia_clave = calloc(strlen(clave) + 1,sizeof(char));
        strcpy(copia_clave,clave);
        pares_t *pares = calloc(1,sizeof(pares_t));
        pares->clave = copia_clave;
        pares->valor = valor; 
        bool asd = abb_insertar(hash->tabla[indice],pares);
        if (hash_factor_de_carga(hash) > 0.75)
        {
                rehash(hash);
        }
        return asd;
}




void* hash_quitar(hash_t* hash, char* clave){
        if (!hash || !clave)
                return false;
        size_t indice = funcion_hash((unsigned char *)clave) % hash->capacidad;
        void * encontrado = NULL;
        pares_t pares;
        pares.clave = clave; 
        abb_quitar(hash->tabla[indice],&pares,&encontrado);
        pares = *(pares_t*)encontrado;
        free(pares.clave);
        free(encontrado);
        return pares.valor;
}

struct iterador {
        bool (*f)(char*, void*, void*);
        void* ctx;
};

bool aplicar_funcion_elementos(void *elemento, void *ctx){
        pares_t *pares_elem = elemento;
        struct iterador *iterador = ctx;
        return iterador->f(pares_elem->clave,pares_elem->valor,iterador->ctx);

}



size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx){
        if (!hash || !f)
                return 0;
        struct iterador iterador;
        iterador.f = f;
        iterador.ctx = ctx; 
        size_t cantidad = 0;
        for (size_t i = 0; i < hash->capacidad; i++)
                cantidad += abb_iterar_inorden(hash->tabla[i],aplicar_funcion_elementos,&iterador);
        return cantidad;
}


static bool destruir_claves(void *pares_, void *ctx){
        pares_t *pares = pares_;
        free(pares->clave);
        // void (*destructor)(void*) = ctx;
        // destructor(pares->valor);
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
                abb_iterar_inorden(hash->tabla[i],destruir_claves,destructor);
                abb_destruir_todo(hash->tabla[i],destruir_pares);
                }
        free(hash->tabla);
        free(hash);
}