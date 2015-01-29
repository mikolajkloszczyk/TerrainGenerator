#version 330
out vec4 fragColor;
uniform sampler2D texture;
in vec4 Color;
in vec3 LightDir;
in vec3 Normal;
in vec2  UV;
void main(void)
{
	
    vec4 abientColor = vec4(0.15,0.15,0.15,1.0);
    vec4 specularColor = vec4(0.33,0.33,0.33,1.0);
	vec4 color = Color;
	float shinnes = (color.r +color.g +color.b)/3;
	//shinnes = 0.5;
    float diff = max(0.0,dot(normalize(Normal),normalize(LightDir)));
    fragColor = diff*color;

    fragColor += abientColor*color;

    vec3 vReflection = normalize(reflect(-normalize(LightDir),normalize(Normal)));

    float spec = max(0.0,dot(normalize(Normal),vReflection)-1 + shinnes);
    if(diff != 0)
    {
        float fSpec = pow(spec,128.0);
        fragColor.rgb += vec3(fSpec,fSpec,fSpec);
    }
	//fragColor.rgb = texture2D(texture, UV).rgb;
	fragColor.a = 1.0f;
}