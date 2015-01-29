#version 330
#extension GL_EXT_geometry_shader4: enable
layout(triangles_adjacency) in;
layout( triangle_strip, max_vertices = 6) out;
uniform mat4 mvpMatrix;
in vec3 varyingLightDir[];
in vec3 varyingNormal[];
in vec4 varyingColor[];
in vec2 varyingUV[];

out vec3 LightDir;
out vec3 Normal;
out vec4 Color;
out vec2 UV;

void main() {

	int i = 0; 
	for(i=0; i<6; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		LightDir = varyingLightDir[i];
		Normal = varyingNormal[i];
		Color = varyingColor[i];
		UV = varyingUV[i];
		EmitVertex();
		if(i == 2 || i == 5)
		{
			EndPrimitive();
		}
	}
}
