#version 330

out vec4 FragColor;

in vec2 fragmentTextureCoordinates;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec3 ambientLightColor;

void main() {
    vec4 ambientLightVector = vec4(ambientLightColor, 1);
    FragColor = texture(diffuseTexture, fragmentTextureCoordinates) * ambientLightVector;
}
