struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

float4 main(VSOutput vsOutput) : SV_TARGET
{
    return vsOutput.color;
}