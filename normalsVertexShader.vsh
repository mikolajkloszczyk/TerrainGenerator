#version 330

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform vec3 vLightPosition;
uniform sampler2D texture;
in vec4 vertex;
//in vec3 normal;
//in vec4 color;

out vec3 varyingLightDir;
out vec3 varyingNormal;
out vec4 varyingColor;
out vec2 varyingUV;


struct ColorParameters 
{
    vec3 height;
    vec4 color;
};
const int maxColors = 8;
uniform int numColors;
uniform ColorParameters colors[maxColors];
uniform vec3 mapSize;
void main(void)
{
	float mapSizeX = mapSize.x;
	float mapSizeZ = mapSize.z;
	float posX = vertex.x/(mapSizeX*2);
	float posZ = vertex.z/mapSizeZ;
	vec4 position = texture2D(texture, vec2(posX,posZ));
	vec4 vertexTmp = vec4(vertex.x,((position.r+position.g+position.b)/3)*mapSize.y*255,vertex.z,1.0);
	//if(posZ == 0 || posX == 0)
	//{
	//	vertexTmp = vec4(0.0,0.0,0.0,1.0);
	//}
	if(colors[0].height.z == -1)
	varyingColor = vec4(0.33,0.33,0.33,0.33);
	else
	varyingColor = vec4(1.0,1.0,1.0,1.0);
	for(int i = 0; i < numColors; i++)
	{
		if(vertexTmp.y >= colors[i].height.x && vertexTmp.y < colors[i].height.y)
		{
			varyingColor = colors[i].color;
		}
	}
	varyingNormal = ((texture2D(texture, vec2((vertex.x+mapSizeX)/(mapSizeX*2),vertex.z/mapSizeZ)).rgb-vec3(0.5,0.5,0.5)) * vec3(2.0,2.0,2.0));

    vec4 vPosition4 = mvMatrix * vertexTmp;
  	vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    varyingLightDir = normalize(vLightPosition-vPosition3);  	
	varyingUV = vec2((vertex.x)/(mapSizeX*2), vertex.z/mapSizeZ);
    gl_Position = vertexTmp;
}
