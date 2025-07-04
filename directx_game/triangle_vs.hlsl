

float4 main(uint vertexID: SV_VertexID ) : SV_POSITION
{
	float2 positions[3] = {
        float2(0.0f, 0.5f), // Top vertex
        float2(0.5, -0.5f), // Right vertex
        float2(-0.5f, -0.5f) // Left vertex
    };
    
    return float4(positions[vertexID], 0.0f, 1.0f);
}