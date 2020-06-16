#include "shader.h"

shader::shader(const TCHAR *path, const char *entry)
	: path(path)
	, entry(entry)
{}

shader::~shader()
{
	release();
}

int shader::load()
{
	int err_lvl = 0;

	if (!path)
	{
		err_lvl = 1;
	}

	if (!err_lvl)
	{
		ID3DBlob *errors = nullptr;
		if (FAILED(D3DCompileFromFile(
			path,
			NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entry,
			"vs_5_0",
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&buffer,
			&errors)))
		{
			if (errors)
			{
#ifdef _DEBUG
				printf((char *)errors->GetBufferPointer());
#endif
				errors->Release();
			}

			err_lvl = 2;
		}
	}

	return err_lvl;
}

void shader::release()
{
	D3D_SAFE_RELEASE(buffer);
}
