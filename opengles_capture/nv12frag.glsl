     #version 300 es	
	precision mediump float;	
	in vec2 v_tex_coord;	
	layout(location = 0) out vec4 out_color;	
	const vec3 offset = vec3(0, -0.5, -0.5);	
	
	const mat3 coeff = mat3(	
	    1.0,      1.0,     1.0,	
	    0.0,     -0.344,  1.722,	
	    1.402,   -0.714,   0);	
	vec3 yuv;	
	vec3 rgb;	
	uniform mediump int image_proc;				
	uniform mediump int uimage_width;				
	uniform mediump int uimage_height;					
      	
	uniform sampler2D s_luma_texture;
	uniform sampler2D s_chroma_texture;
	void main()
	{
		float xcoord,ycoord;       
		float texel_width, texel_height;       
		vec3 yuv;		       
		texel_width=1.0f/float(uimage_width);
		texel_height=1.0f/float(uimage_height);
		
		vec2 texelsize=vec2(texel_width,texel_height);    
		vec2 texelsize2=vec2(texel_width*2.0f,texel_height*2.0f);    
		
		yuv.x = texture2D(s_luma_texture, v_tex_coord).x;
		yuv.yz = texture2D(s_chroma_texture, v_tex_coord).xw;
		yuv += offset;
		rgb = coeff * yuv;
		switch (image_proc)		
		{	
			case 0:
			break;
			
			
			case 2://y
				rgb.r = yuv.x;
				rgb.g = yuv.x;
				rgb.b = yuv.x;
			break;
			
			case 3://u
				rgb.r = yuv.y+0.5;
				rgb.g = yuv.y+0.5;
				rgb.b = yuv.y+0.5;
			break;
			
			case 4://v
				rgb.r = yuv.z+0.5;
				rgb.g = yuv.z+0.5;
				rgb.b = yuv.z+0.5;
			break;
			case 5://r
				rgb.g=0.0f;
				rgb.b=0.0f;
			break;
			case 6://g
				rgb.r=0.0f;
				rgb.b=0.0f;
			break;
			case 7://b
				rgb.r=0.0f;
				rgb.g=0.0f;
			break;
			case 9://o for threshold
				vec3 col=vec3(0.5f,0.5f,0.5f);
				rgb = vec3(greaterThanEqual(rgb,col));
				
			break;
		}
		//rgb=tot;
	    out_color = vec4(rgb,1);
	}


 