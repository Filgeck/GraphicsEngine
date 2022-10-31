#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float a = 0.05;
    float b = 0.01;
    float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

    //ambient
    float ambient = 0.2;

    //diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    //specular
    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight()
{
    //ambient
    float ambient = 0.2;

    //diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 0.0));
    float diffuse = max(dot(normal, lightDirection), 0.0);

    //specular
    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
    //use already "cosed" value (cos(angle)) as this is more efficient
    //simple degrees are not efficient
    float outerCone = 0.9;
    float innerCone = 0.95;

    //ambient
    float ambient = 0.2;

    //diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    //specular
    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float steepness = 0.5;
float offset = 5.0;

float logisticDepth(float depth)
{
    float zVal = logisticDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
    FragColor = pointLight();

    //visualizes depth
    //FragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z) / far), 1.0);

    //FOG not working
    //float depth = logisticDepth(gl_FragCoord.z);
    //FragColor = direcLight() * (1.0 - depth) + vec4(depth * vec3(0.85, 0.85, 0.90), 1.0);
}