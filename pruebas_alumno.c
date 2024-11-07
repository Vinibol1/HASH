#include "pa2m.h"
#include "src/hash.h"

void hash_crear_pruebas()
{
	hash_t *hash = hash_crear(4);
	pa2m_afirmar(hash != NULL, "El hash se creo correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La función has empieza con 0 elementos");
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Hash crear");
	hash_crear_pruebas();

	return pa2m_mostrar_reporte();
}
