#include "BlobUtil.h"
#include <iostream>

ComPtr<ID3D10Blob> BlobUtil::Create(std::string filePath, std::string version, std::string mainFn)
{
	ComPtr<ID3D10Blob> blob = nullptr;

	ComPtr<ID3D10Blob> errorBlob = nullptr;

	// Load the vertex shader from file
	HRESULT hr = D3DCompileFromFile(
		std::wstring(filePath.begin(), filePath.end()).c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		mainFn.c_str(),
		version.c_str(),
		0,
		0,
		&blob,
		&errorBlob
	);

	if (FAILED(hr)) {
		if (errorBlob) {
			std::cerr << "Shader compilation failed: " <<
				static_cast<const char*>(errorBlob->GetBufferPointer())
				<< std::endl;
		}
		else {
			std::cerr << "Shader compilation failed." << std::endl;
		}
		return nullptr;
	}

	return blob;
}
