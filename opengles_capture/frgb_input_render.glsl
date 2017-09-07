	#version 300 es 			
      
	precision mediump float;                            
	in vec2 v_tex_coord;                            
      	uniform mediump int image_proc;				
	uniform mediump int uimage_width;				
	uniform sampler2D s_luma_texture;                        
	layout (location=0) out vec4 out_color;   
	vec4 res;
	vec4 rgb;
      void main()                                         
	

      {
	rgb= texture2D(s_luma_texture, v_tex_coord);
	res=rgb;
	switch (image_proc)		
	{	
		case 0:
		break;
		
		case 5://r
			res.r = rgb.r;
			res.g = 0.0f;
			res.b = 0.0f;
		break;
		
		case 6://g
			res.r = 0.0f;
			res.g = rgb.g;
			res.b = 0.0f;
		break;
		
		case 7://b
			res.r = 0.0f;
			res.g = 0.0f;
			res.b = rgb.b;
		break;
	}	
	
	out_color = clamp(res,vec4(0),vec4(1));
	
      }                                                   

 