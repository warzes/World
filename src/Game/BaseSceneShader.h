#pragma once

[[nodiscard]] inline ShaderProgramRef CreateBaseSceneShader()
{
	const char* vertexShaderText = R"(
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

uniform mat4 pvMatrix;

out vec2 fragmentTexCoord;
out vec4 fragmentColor;

void main()
{
	gl_Position      = pvMatrix * vec4(aPosition, 1.0);
	fragmentTexCoord = aTexCoord;
	fragmentColor    = aColor;
}
)";

	const char* fragmentShaderText = R"(
in vec2 fragmentTexCoord;
in vec4 fragmentColor;

out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, fragmentTexCoord) * fragmentColor;
}
)";

	return GetRenderSystem().CreateShaderProgram({vertexShaderText}, {fragmentShaderText});
}