#include "pa2m.h"
#include "src/hash.h"

void hash_crear_pruebas()
{
	hash_t *hash = hash_crear(4);
	pa2m_afirmar(hash != NULL, "El hash se creo correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La función has empieza con 0 elementos");
	hash_destruir(hash);
}

void hash_insertar_pruebas()
{
	hash_t *hash = hash_crear(4);
	char *clave = "daa";
	int valor = 2;
	pa2m_afirmar(hash_insertar(hash,clave,&valor,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función has empieza con 0 elementos");
	pa2m_afirmar(hash_contiene(hash,clave) == true, "La función encontro el elemento correctamente");
	hash_destruir(hash);
}

void hash_insertar_pruebas2()
{
	hash_t *hash = hash_crear(4);
	char *clave = "daa";
	int valor = 2;
	char *clave2 = "asd0";
	int valor2 = 2;
	char *clave3 = "asd1";
	int valor3 = 2;
	char *clave4 = "asd2";
	int valor4 = 2;
	char *clave5 = "asd3";
	int valor5 = 2;
	pa2m_afirmar(hash_insertar(hash,clave,&valor,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash,clave2,&valor2,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(hash_insertar(hash,clave3,&valor3,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene  3 elementos");
	pa2m_afirmar(hash_insertar(hash,clave4,&valor4,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene  4 elementos");
	pa2m_afirmar(hash_insertar(hash,clave5,&valor5,NULL) == true, "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La función tiene  4 elementos");
	pa2m_afirmar(hash_contiene(hash,clave) == true, "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash,clave2) == true, "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash,clave3) == true, "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash,clave4) == true, "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash,"aguante racing") == false, "le paso una clave que no existe devuelve false");
	pa2m_afirmar(*(int*)hash_buscar(hash,clave) == valor, "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int*)hash_buscar(hash,clave2) == valor2, "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int*)hash_buscar(hash,clave4) == valor3, "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int*)hash_buscar(hash,clave3) == valor4, "La función encontro el elemento correctamente");
	pa2m_afirmar((int*)hash_buscar(hash,"asdasd") == NULL, "le paso una clave que no existe y devuelve NULL");
	hash_destruir(hash);
}


int main()
{
	pa2m_nuevo_grupo("Hash crear");
	hash_crear_pruebas();
	hash_insertar_pruebas();
	hash_insertar_pruebas2();

	return pa2m_mostrar_reporte();
}
