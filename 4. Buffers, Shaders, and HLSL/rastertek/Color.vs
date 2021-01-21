cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;
	
	// 적절한 행렬 계산을 위해 위치 벡터를 동차 좌표로 변환한다.
	input.position.w = 1.0f;

	// 월드, 뷰, 프로젝션 행렬들을 이용해 정점의 위치를 계산한다.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// 입력받은 색상을 그대로 픽셀 셰이더에서 이용하도록 저장한다.
	output.color = input.color;

	return output;
}