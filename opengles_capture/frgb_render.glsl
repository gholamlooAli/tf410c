	#version 300 es 			
      
	precision mediump float;                            
	in vec2 v_tex_coord;    
	uniform mediump int image_proc;				
	uniform mediump int uimage_width;				
	uniform mediump int uimage_height;					
      	uniform sampler2D s_luma_texture;                        
	layout (location=0) out vec4 out_color;   
	
      void main()                                         
	

      {
	vec2 texelsize=vec2(1.0f/float(uimage_width),1.0f/float(uimage_height));      
	vec4 rgba;
	rgba= texture2D(s_luma_texture, v_tex_coord);
	switch (image_proc)		
	{	
		case 0:
		break;
		
		case 8:	
			float x = 1.0f/float(uimage_width);
			float y = 1.0f/float(uimage_height);
		
			vec4 h_edge=vec4(0.0);
			h_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x - x, v_tex_coord.y -y )) * 1.0;
			h_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x - x, v_tex_coord.y    )) * 2.0;
			h_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x - x, v_tex_coord.y +y )) * 1.0;
			h_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x + x, v_tex_coord.y -y )) * 1.0;
			h_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x + x, v_tex_coord.y    )) * 2.0;
			h_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x + x, v_tex_coord.y +y )) * 1.0;
		
			vec4 v_edge=vec4(0.0);

			v_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x - x, v_tex_coord.y -y )) * 1.0;
			v_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x    , v_tex_coord.y -y )) * 2.0;
			v_edge -= texture2D(s_luma_texture, vec2(v_tex_coord.x + x, v_tex_coord.y -y )) * 1.0;
			v_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x - x, v_tex_coord.y +y )) * 1.0;
			v_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x    , v_tex_coord.y +y )) * 2.0;
			v_edge += texture2D(s_luma_texture, vec2(v_tex_coord.x + x, v_tex_coord.y +y )) * 1.0;
		
			vec4 tot = sqrt(v_edge*v_edge+h_edge*h_edge);
			/*
			vec4 tm1m1 = texture2D(s_luma_texture,v_tex_coord+vec2(-1,-1)*texelsize);
			vec4 tm10 =  texture2D(s_luma_texture,v_tex_coord+vec2(-1,0)*texelsize);
			vec4 tm1p1 = texture2D(s_luma_texture,v_tex_coord+vec2(-1,1)*texelsize);
			vec4 tp1m1 = texture2D(s_luma_texture,v_tex_coord+vec2(1,-1)*texelsize);
			vec4 tp10 =  texture2D(s_luma_texture,v_tex_coord+vec2(1,0)*texelsize);
			vec4 tp1p1 = texture2D(s_luma_texture,v_tex_coord+vec2(1,1)*texelsize);
			vec4 t0m1 =  texture2D(s_luma_texture,v_tex_coord+vec2(0,-1)*texelsize);
			vec4 t0p1 =  texture2D(s_luma_texture,v_tex_coord+vec2(0,-1)*texelsize);

			vec4 xdiff = -1.0*tm1m1 + -2.0*tm10 + -1.0*tm1p1 + 1.0*tp1m1 + 2.0*tp10 + 1.0*tp1p1;
			vec4 ydiff = -1.0*tm1m1 + -2.0*t0m1 + -1.0*tp1m1 + 1.0*tm1p1 + 2.0*t0p1 + 1.0*tp1p1;
			vec4 tot = sqrt(xdiff*xdiff+ydiff*ydiff);
			*/
			rgba = tot;
			break;
	}	
	
	out_color =rgba;
	
      }                                                   

 