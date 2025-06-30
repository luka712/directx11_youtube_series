float4 main(uint vertexID : SV_VertexID) : SV_POSITION
{
    float2 positions[3] =
    {
        float2(0.0f, 0.5f), // Top
        float2(0.5f, -0.5f), // Bottom Right
        float2(-0.5f, -0.5f) // Bottom Left
    };
	
    return float4(positions[vertexID], 1.0, 1.0);
}