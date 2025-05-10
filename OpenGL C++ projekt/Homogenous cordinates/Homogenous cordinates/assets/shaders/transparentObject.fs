#version 330 core
out vec4 FragColor;

in vec3 myColor;
in float alpha;

void main(){
	FragColor = vec4(myColor, alpha);
}