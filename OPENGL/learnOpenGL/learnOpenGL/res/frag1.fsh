#version 460 core
out vec4 FragColor;

in vec3 fragPos;

void main() {
  FragColor = vec4(
        abs(fragPos.x),
        abs(fragPos.y), 
        abs(fragPos.z),
        1.0
    );
} 