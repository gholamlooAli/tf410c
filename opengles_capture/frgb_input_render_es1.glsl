	//#version 300 es 			
      
	precision mediump float;                            
	varying vec2 v_tex_coord;                            
      	uniform mediump int image_proc;				
	uniform mediump int uimage_width;
	uniform mediump int uimage_height;	
	uniform sampler2D s_luma_texture;                        
	vec4 res;
	vec4 rgb;
      void main()                                         
	

      {
	//rgb= texture2D(s_luma_texture, v_tex_coord);
	//res=rgb;
	vec2 texelsize=vec2(1.0f/float(uimage_width),1.0f/float(uimage_height));      
	vec4 rgba;
	rgba= texture2D(s_luma_texture, v_tex_coord);  
	if(image_proc==5){
		rgba.g = 0.0f;
		rgba.b = 0.0f;
	}     
	if(image_proc==6){
		rgba.r = 0.0f;
		rgba.b = 0.0f;
	} 
	if(image_proc==7){
		rgba.g = 0.0f;
		rgba.r = 0.0f;
	} 
	if(image_proc==8){	
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
	
	}
	gl_FragColor = rgba;//clamp(res,vec4(0),vec4(1));
	
      }                                                   

 