// could not work 8 times loop with GMA950
#define NUMBER_OF_WEIGHTS 8

float WIDTH;
float HEIGHT;
float WEIGHT[NUMBER_OF_WEIGHTS];
float TAPOFFSET_X[NUMBER_OF_WEIGHTS]; // 1 / WIDTH, 2 / WIDTH, ..., index 0 is not used
float TAPOFFSET_Y[NUMBER_OF_WEIGHTS]; // 1 / HEIGHT, 2 / HEIGHT, ..., index 0 is not used

Texture2D texDiffuse;
SamplerState samDiffuse
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct InputVS
{
	float4 pos   : POSITION;
	float2 tex   : TEXCOORD0;
};

struct OutputVS
{
	float4 pos   : SV_POSITION;
	float2 tex   : TEXCOORD0;
};

OutputVS VS_Pass0(InputVS inVert)
{
	return inVert;
}

float4 PS_Pass0(OutputVS inPixel) : SV_TARGET0
{
	float4 color  = WEIGHT[0] * texDiffuse.Sample( samDiffuse, inPixel.tex );
	for(int i = 1; i < NUMBER_OF_WEIGHTS; i++) {
		color += WEIGHT[i]
		  * ( texDiffuse.Sample( samDiffuse, inPixel.tex + float2(TAPOFFSET_X[i], 0.0f))
			+ texDiffuse.Sample( samDiffuse, inPixel.tex + float2(-TAPOFFSET_X[i], 0.0f)));
	}
	color = saturate(color * 2.0f);
	return color;
}

OutputVS VS_Pass1(InputVS inVert)
{
	return inVert;
}

float4 PS_Pass1(OutputVS inPixel) : SV_TARGET0
{
	float4 color  = WEIGHT[0] * texDiffuse.Sample( samDiffuse, inPixel.tex );
	for(int i = 1; i < NUMBER_OF_WEIGHTS; i++) {
		color += WEIGHT[i]
		  * ( texDiffuse.Sample( samDiffuse, inPixel.tex + float2(0.0f, TAPOFFSET_Y[i]))
			+ texDiffuse.Sample( samDiffuse, inPixel.tex + float2(0.0f, -TAPOFFSET_Y[i])));
	}
	color = saturate(color * 2.0f);
	return color;
}

technique10 Shader
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Pass0() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Pass0() ) );
    }
    pass P1
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Pass1() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Pass1() ) );
    }
}
