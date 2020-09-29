#version 330 core

layout(location = 0) in vec2 aPositionOffset;
layout(location = 1) in vec2 aAxisDirection;
layout(location = 2) in vec2 aLineHalfLength;
layout(location = 3) in int aBaseLineId;

uniform vec4 uNormalColor;
uniform vec4 uGroupColor;
uniform vec4 uAxisColor;
uniform float uNormalHalfWidth;
uniform float uGroupHalfWidth;
uniform float uAxisHalfWidth;
uniform int uGroupSize;
uniform float uLineOffset;

out VS_OUT {
	vec4 color;
	vec2 halfSize;
} vs_out;

const float zNormal = 1.0f;
const float zGroup = 0.5f;
const float zAxis = 0.0f;

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
	int lineId = aBaseLineId + gl_InstanceID;

	int isAxisLine = AreEq(lineId, 0);
	int isGroupLine = And(Neg(isAxisLine), AreEq(int(mod(lineId, uGroupSize)), 0));
	int isNormalLine = And(Neg(isAxisLine), Neg(isGroupLine));

	float halfWidth = isNormalLine * uNormalHalfWidth + isGroupLine * uGroupHalfWidth + isAxisLine * uAxisHalfWidth;

	gl_Position.xy = aPositionOffset + aAxisDirection * uLineOffset * lineId;
	gl_Position.z = isNormalLine * zNormal + isGroupLine * zGroup + isAxisLine * zAxis;
	gl_Position.w = 1.0f;

	vs_out.color = vec4(1,1,1,1);//isNormalLine * uNormalColor + isGroupLine * uGroupColor + isAxisLine * uAxisColor;
	vs_out.halfSize = aAxisDirection * halfWidth + aLineHalfLength;
}
