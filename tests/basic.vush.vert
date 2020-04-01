#version 460
#pragma stage(vertex)
#extension GL_GOOGLE_cpp_style_line_directive : require

struct VS_IN {
	vec3 position;
	vec3 normal;
	vec2 texcoord;
};

struct VS_OUT {
	vec4 position;
	vec2 texcoord;
};

layout(location = 0) out VS_OUT _out;

layout(location = 0) in vec3 _VS_IN_position;
layout(location = 1) in vec3 _VS_IN_normal;
layout(location = 2) in vec2 _VS_IN_texcoord;

#line 12 "../../tests/basic.vush"
VS_OUT opaque_vertex(VS_IN vin) {
	VS_OUT vout;
	vout.position = vec4(vin.position, 1.0);
	vout.texcoord = vin.texcoord;
	return vout;
}

void main() {
	VS_IN vin;
	vin.position = _VS_IN_position;
	vin.normal = _VS_IN_normal;
	vin.texcoord = _VS_IN_texcoord;
	_out = opaque_vertex(vin);
}