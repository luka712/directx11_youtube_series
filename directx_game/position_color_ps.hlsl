struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

float4 main(VSOutput output) : SV_TARGET
{
    return output.color;
}