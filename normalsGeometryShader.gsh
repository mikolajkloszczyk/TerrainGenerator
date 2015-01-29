#version 330
#extension GL_EXT_geometry_shader4: enable
layout(triangles_adjacency) in;
layout( line_strip, max_vertices = 12) out;
uniform mat4 mvpMatrix;
in vec3 varyingLightDir[];
in vec3 varyingNormal[];
in vec4 varyingColor[];
in vec2 varyingUV[];

out vec3 LightDir;
out vec3 Normal;
out vec4 Color;
out vec2 UV;
vec3 GetNormal(vec4 p1, vec4 p2, vec4 p3)
{
	vec3 Normal;
	vec4 U,V;
	mat4 inverseMatrix;
	inverseMatrix = inverse(mvpMatrix);
	
	U = inverseMatrix*(p2 - p1);
	V = inverseMatrix*(p3 - p1);
	Normal = cross(U.xyz, V.xyz);
	return Normal;
}
void DrawPlane(vec4 p1, vec4 p2, vec4 p3)
{
	vec4 pos = vec4((p1 + p2 + p3) / 3);
	gl_Position = pos;
	LightDir = varyingLightDir[0];
	Normal = vec3(0.0,1.0,0.0);
	Color = vec4(1.0,0.0,0.0,1.0);
	UV = varyingUV[0];
	EmitVertex();
	gl_Position = pos +vec4(GetNormal(p1, p2, p3),1.0);
	LightDir = varyingLightDir[0];
	Normal = vec3(0.0,0.0,0.0);
	Color = vec4(1.0,0.0,0.0,1.0);
	UV = varyingUV[0];
	EmitVertex();
	EndPrimitive();
	
}
void DrawPointNormal(int index)
{
	gl_Position = mvpMatrix*gl_in[index].gl_Position;
	LightDir = varyingLightDir[0];
	Normal = vec3(0.0,1.0,0.0);
	Color = vec4(1.0,0.0,0.0,1.0);
	UV = varyingUV[0];
	EmitVertex();
	gl_Position = mvpMatrix*(gl_in[index].gl_Position+vec4(varyingNormal[index],0.0));
	LightDir = varyingLightDir[0];
	Normal = vec3(0.0,0.0,0.0);
	Color = vec4(1.0,1.0,1.0,1.0);
	UV = varyingUV[0];
	EmitVertex();
	EndPrimitive();
}
void main() 
{
	DrawPointNormal(0);
	DrawPointNormal(1);
	DrawPointNormal(2);
	DrawPointNormal(3);
	DrawPointNormal(5);
}
