	//VERTEX_SHADER
	//"#version 300 es
	
	//layout(location = 0) in vec4 a_position
	//layout(location = 1) in vec2 a_tex_coord
	//out vec2 v_tex_coord;\n"
	
	attribute vec4 a_position;
	attribute vec2 a_tex_coord;
	varying vec2 v_tex_coord;
	
	void main()
	{
	   gl_Position = a_position;
	   v_tex_coord = a_tex_coord;
	}
 