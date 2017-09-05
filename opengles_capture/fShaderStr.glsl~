	#version 300 es 			
      
		
        precision mediump float;                            
        in vec2 v_tex_coord;                            
      	uniform mediump int image_proc;				
	
	uniform mediump int uimage_width;				
	uniform sampler2D s_luma_texture;                        
	layout (location=0) out vec4 out_color;   
	// Additive offset for BT656 YUV to RGB transform.	
	const vec3 offset = vec3(0, -0.5, -0.5);	
	
	//const mat3 coeff = mat3(	
	//    1.0,      1.0,     1.0,	
	//    0.0,     -0.344,  1.722,	
	//    1.402,   -0.714,   0);	
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
	vec3 yuv;		       
	vec4 res;		       
	  
	texture_width=float(uimage_width);	
	texel_width=1.0/texture_width; 
	xcoord = floor (v_tex_coord.x * texture_width);	 
	luma_chroma = texture2D(s_luma_texture, v_tex_coord);	
	// just look up the brightness
	yuv.x = (luma_chroma.a - 0.0625) * 1.1643;	

	  
	if (0.0 == mod(xcoord , 2.0)) 	// even
	    {				
	      yuv.y = luma_chroma.r;	
	      yuv.z = texture2D(s_luma_texture,vec2(v_tex_coord.x - texel_width, v_tex_coord.y)).g;	
	    }	
	else // odd
	{	
	      yuv.z = luma_chroma.r;	
	      yuv.y = texture2D(s_luma_texture,vec2(v_tex_coord.x + texel_width, v_tex_coord.y)).g; 	    
	}	
	  
	yuv += offset;
	
	res.r = yuv.x + 1.402 * yuv.z;	
	res.g = yuv.x - 0.3441 * yuv.y - 0.7141 * yuv.z;	
	res.b = yuv.x + 1.772 * yuv.y;	
	
	//res.r = yuv.x + 1.5958 * yuv.z;	
	//res.g = yuv.x - 0.39173 * yuv.y - 0.8129 * yuv.z;	
	//res.b = yuv.x + 2.017 * yuv.y;	
	
	//res.r = yuv.x + 1.793 * yuv.z;	
	//res.g = yuv.x - 0.213 * yuv.y - 0.534 * yuv.z;	
	//res.b = yuv.x + 2.115 * yuv.y;	
	
	switch (image_proc)		
	{				
	   case 0:				
	   break;				
	}				
	res.a = 1.0;				
	//    rgb = coeff * yuv;
	//    res = vec4(rgb,1);
	out_color = clamp(res,vec4(0),vec4(1));
	
      }                                                  
