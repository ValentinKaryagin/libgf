#include "static_mesh.h"

static_mesh::static_mesh(const TCHAR *path)
	: path(path)
{}

static_mesh::~static_mesh()
{
	release();
}

int static_mesh::load()
{
	return 0;
}

void static_mesh::release()
{

}
