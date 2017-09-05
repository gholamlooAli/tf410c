	#version 300 es 			
      
		
	precision mediump float;                            
	in vec2 v_tex_coord;                            
      	uniform mediump int image_proc;				
	uniform mediump int uimage_width;				
	uniform sampler2D s_luma_texture;                        
	layout (location=0) out vec4 out_color;   
	// Additive offset for BT656 YUV to RGB transform.	
	const vec3 offset = vec3(0, -0.5, -0.5);	
	// Temporary variable for YUV value	
	vec3 yuv;	
	// Temporary variable for RGB value	
	vec3 rgb;
	
	
      void main()                                         
	

      {                                                   
      
	vec4 luma_chroma;	       
	float xcoord;       
	float texture_width;       
	float texel_width; 
	const mat3 coeff = mat3(	
	    1.0,      1.0,     1.0,	
	    0.0,     -0.344,  1.722,	
	    1.402,   -0.714,   0);	
	      
	vec3 yuv;		       
	vec4 res;		       
	texture_width=float(uimage_width);	
	//texture_width=float(1980);	
	texel_width=1.0f/texture_width;
	      texel_width=1.0f/(960.0f*2.0f*4.0f);
	xcoord = floor (v_tex_coord.x * texture_width);	
	luma_chroma = texture2D(s_luma_texture, v_tex_coord);	
	// just look up the brightness
	//yuv.x = (luma_chroma.a - 0.0625) * 1.1643;	
	yuv.x = luma_chroma.a;
	int xcor=int (xcoord);
		//int step=uimage_width/320;
		int remi=xcor%2;
		if (0.0 != mod(xcoord , 2.0)) 	// even
	  //if(remi==0) 
	   {				
	      yuv.y = luma_chroma.g;	
//yuv.z = texture2D(s_luma_texture,vec2(v_tex_coord.x - float(1.0f/960.0f)/*texel_width*/, v_tex_coord.y)).b; 
	      yuv.z = texture2D(s_luma_texture,vec2(v_tex_coord.x + texel_width, v_tex_coord.y)).g;	
	    }	
	else // odd
	{	
	      yuv.z = luma_chroma.g;
//yuv.y = texture2D(s_luma_texture,vec2(v_tex_coord.x + float(1.0f/960.0f)/*texel_width*/, v_tex_coord.y)).r;		
	      yuv.y = texture2D(s_luma_texture,vec2(v_tex_coord.x - texel_width, v_tex_coord.y)).g; 	    
	}	
	  
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
	}
	out_color = vec4(rgb,1);
      }                                                   

 