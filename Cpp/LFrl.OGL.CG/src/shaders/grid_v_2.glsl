#version 330 core

layout(location = 0) in vec2 aPositionOffset;
layout(location = 1) in vec2 aAxisDirection;
layout(location = 2) in vec2 aLineHalfLength;
layout(location = 3) in float aBaseLineId;

uniform vec4 uNormalColor;
uniform vec4 uGroupColor;
uniform vec4 uAxisColor;
uniform float uNormalHalfWidth;
uniform float uGroupHalfWidth;
uniform float uAxisHalfWidth;
uniform float uGroupSize;
uniform float uLineOffset;

out VS_OUT {
	vec4 color;
	vec2 halfSize;
} vs_out;

const float zNormal = 0.0f;
const float zGroup = 0.5f;
const float zAxis = 1.0f;

int AreNotEq(int a, int b)
{
	return abs(sign(a - b));
}

int Neg(int a)
{
	return 1 - a;
}

int AreEq(int a, int b)
{
	return Neg(AreNotEq(a, b));
}

int And(int a, int b)
{
	return a * b;
}

void main()
{
	float groupSize = floor(uGroupSize);
	int lineId = int(aBaseLineId) + gl_InstanceID;

	int isAxisLine = AreEq(lineId, 0);
	int isGroupLine = And(Neg(isAxisLine), AreEq(int(mod(float(lineId), groupSize)), 0));
	int isNormalLine = And(Neg(isAxisLine), Neg(isGroupLine));

	float halfWidth = isNormalLine * uNormalHalfWidth + isGroupLine * uGroupHalfWidth + isAxisLine * uAxisHalfWidth;

	vec2 position = aPositionOffset + aAxisDirection * (uLineOffset * float(lineId));
	float zIndex = isNormalLine * zNormal + isGroupLine * zGroup + isAxisLine * zAxis;
	gl_Position = vec4(position, zIndex, 1.0f);

	vs_out.color = isNormalLine * uNormalColor + isGroupLine * uGroupColor + isAxisLine * uAxisColor;
	vs_out.halfSize = aAxisDirection * halfWidth + aLineHalfLength;
}
