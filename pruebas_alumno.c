#include "pa2m.h"
#include "src/hash.h"
#include "string.h"

void hash_crear_pruebas()
{
	hash_t *hash = hash_crear(4);
	pa2m_afirmar(hash != NULL, "El hash se creo correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La función has empieza con 0 elementos");
	hash_destruir(hash);
}

void hash_insertar_pruebas()
{
	hash_t *hash = hash_crear(4);
	char *clave = "daa";
	int valor = 2;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_contiene(hash, clave) == true,
		     "La función encontro el elemento correctamente");
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
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene  3 elementos");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene  4 elementos");
	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La función tiene  4 elementos");
	pa2m_afirmar(hash_contiene(hash, clave) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash, clave2) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash, clave3) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash, clave4) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(hash_contiene(hash, "aguante racing") == false,
		     "le paso una clave que no existe devuelve false");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave) == valor,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave2) == valor2,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave4) == valor3,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave3) == valor4,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar((int *)hash_buscar(hash, "asdasd") == NULL,
		     "le paso una clave que no existe y devuelve NULL");
	hash_destruir(hash);
}

void hash_insertar_pruebas_claves_iguales()
{
	hash_t *hash = hash_crear(4);
	char *clave = "daa";
	int valor = 2;
	char *clave2 = "asd0";
	int valor2 = 2;
	char *clave3 = "asd0";
	int valor3 = 5;
	int *enconctrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave2) == valor2,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, (void**)&enconctrado) == true,
		     "hash devolvio true");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave2) == valor3,
		     "La función encontro el elemento correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene 2 elementos");
	pa2m_afirmar(hash_contiene(hash, clave) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(*enconctrado = 2,
		     "Encontrado devolvio el valor anterior");
	pa2m_afirmar(hash_contiene(hash, clave3) == true,
		     "La función encontro la clave correctamente");
	pa2m_afirmar(*(int *)hash_buscar(hash, clave) == valor,
		     "La función encontro el elemento correctamente %i",
		     *(int *)hash_buscar(hash, clave));
	hash_destruir(hash);
}

void hash_quitar_pruebas()
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
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene  3 elementos");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene  4 elementos");
	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La función tiene 5 elementos");
	pa2m_afirmar(*(int *)hash_quitar(hash, clave5) == valor5,
		     "hash devolvio valor 5");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene 4 elementos");
	pa2m_afirmar(*(int *)hash_quitar(hash, clave4) == valor4,
		     "hash devolvio valor 4");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene 3 elementos");
	pa2m_afirmar(*(int *)hash_quitar(hash, clave3) == valor3,
		     "hash devolvio valor 3");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene 2 elementos");
	pa2m_afirmar(*(int *)hash_quitar(hash, clave2) == valor2,
		     "hash devolvio valor 2");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elementos");
	pa2m_afirmar(*(int *)hash_quitar(hash, clave) == valor,
		     "hash devolvio valor 1");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La función tiene 0 elementos");
	hash_destruir(hash);
}

bool iterar(char *k, void *v, void *ctx)
{
	int *asd = v;
	*asd += 2;
	return true;
}

void hash_iterar_pruebas()
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
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene  3 elementos");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene  4 elementos");
	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La función tiene 5 elementos");
	size_t iterador = hash_iterar(hash, iterar, NULL);
	pa2m_afirmar(iterador == 5, "La función iterar itera %i de 5 elementos",
		     iterador);
	pa2m_afirmar(*(int *)hash_buscar(hash, "daa") == 4,
		     "La función iterar sumo 2 al elemento");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd0") == 4,
		     "La función iterar sumo 2 al elemento");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd1") == 4,
		     "La función iterar sumo 2 al elemento");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd2") == 4,
		     "La función iterar sumo 2 al elemento");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd3") == 4,
		     "La función iterar sumo 2 al elemento");

	hash_destruir(hash);
}

bool iterar2(char *k, void *v, void *ctx)
{
	int *asd = v;
	if (*asd == 3)
		return false;

	*asd += 2;
	return true;
}

void hash_iterar_terminando_el_iterador_forzadamente_pruebas()
{
	hash_t *hash = hash_crear(4);
	char *clave = "daa";
	int valor = 2;
	char *clave2 = "asd0";
	int valor2 = 2;
	char *clave3 = "asd1";
	int valor3 = 2;
	char *clave4 = "asd2";
	int valor4 = 3;
	char *clave5 = "asd3";
	int valor5 = 3;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La función tiene 1 elemento");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La función tiene  2 elementos");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La función tiene  3 elementos");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La función tiene  4 elementos");
	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, NULL) == true,
		     "hash devolvio true");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La función tiene 5 elementos");
	size_t iterador = hash_iterar(hash, iterar2, NULL);
	pa2m_afirmar(iterador == 1,
		     "La función iterar itera %zu de 5 elementos", iterador);
	pa2m_afirmar(*(int *)hash_buscar(hash, "daa") == 2,
		     "La función iterar no sumo");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd0") == 2,
		     "La función iterar no sumo");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd1") == 2,
		     "La función iterar no sumo");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd2") == 3,
		     "La función iterar no sumo");
	pa2m_afirmar(*(int *)hash_buscar(hash, "asd3") == 3,
		     "La función iterar no sumo");
	hash_destruir(hash);
}

void hash_muchas_claves()
{
	hash_t *hash = hash_crear(10000);
	char clave[100000] = "a";
	int valor = 2;
	for (size_t i = 0; i < 10000; i++) {
		clave[strlen(clave)] = (char)i;
		hash_insertar(hash, clave, &valor, NULL);
	}

	pa2m_afirmar(hash_cantidad(hash) == 9961, "La función tiene %u elemento",
		     hash_cantidad(hash));

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Hash crear");
	hash_crear_pruebas();
	pa2m_nuevo_grupo("Hash Insertar crear");
	hash_insertar_pruebas();
	pa2m_nuevo_grupo("Hash insertar pruebas");
	hash_insertar_pruebas2();
	pa2m_nuevo_grupo("Hash insertar claves iguales");
	hash_insertar_pruebas_claves_iguales();
	pa2m_nuevo_grupo("Hash quitar");
	hash_quitar_pruebas();
	pa2m_nuevo_grupo("Hash iterar");
	hash_iterar_pruebas();
	pa2m_nuevo_grupo("Hash iterar forzando cierres");
	hash_iterar_terminando_el_iterador_forzadamente_pruebas();
	pa2m_nuevo_grupo("Hash insertar muchas claves");
	hash_muchas_claves();

	return pa2m_mostrar_reporte();
}
