#include "stdafx.h"
#include "CompositeTextures.h"


CompositeTextures::CompositeTextures(ComputeCore* computeCore)
{
	core = computeCore;
	compositeCS = std::unique_ptr<ComputeProcess>(new ComputeProcess(core, L"CompositeCS.cso"));
}

Texture * CompositeTextures::Composite(ID3D12GraphicsCommandList * command, Texture * inputA, Texture * inputB, TexturePool * pool)
{
	UINT width = 1280;
	UINT height = 720;
	auto texR = pool->GetNext();
	auto outUAV = texR.UAV;
	auto outSRV = texR.SRV;
	compositeCS->SetShader(command);
	compositeCS->SetTextureSRV(command, inputA);
	compositeCS->SetTextureSRVOffset(command, inputB);
	compositeCS->SetTextureUAV(command, outUAV);
	compositeCS->Dispatch(command, width, height, 1);
	return outSRV;
}


CompositeTextures::~CompositeTextures()
{
}
