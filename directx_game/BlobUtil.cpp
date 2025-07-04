#include "BlobUtil.h"
#include <iostream>

ComPtr<ID3D10Blob> BlobUtil::Create(std::string filePath, std::string version, std::string mainFn)
{
	ComPtr<ID3D10Blob> blob;
	ComPtr<ID3D10Blob> errorBlob;

	HRESULT hr = D3DCompileFromFile(
		std::wstring(filePath.begin(), filePath.end()).c_str(), // Convert to wide string
		nullptr, // No macros
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // Include standard file
		mainFn.c_str(), // Entry point for vertex shader
		version.c_str(), // Target version for vertex shader
		0, // No flags
		0, // No effect flags
		&blob, // Output blob for vertex shader
		&errorBlob // No error blob
	);

	if (FAILED(hr)) {
		if (errorBlob) {
			std::cerr << "Vertex shader compilation failed: "
				<< static_cast<const char*>(errorBlob->GetBufferPointer())
				<< std::endl;
		}
		else {
			std::cerr << "Vertex shader compilation failed" << std::endl;
		}
		return nullptr;
	}

	return blob;
}
