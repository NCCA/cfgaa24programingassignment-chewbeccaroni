# Rebecca Blundell CFGAA Assignment

## Assignment Idea

The aim of my project was to create some type of glowing effect using 2 shaders in c++ using OpenGL. One shader renders the base colour or texture, the other
renders a blurred framebuffer using kernels. From the start I ran into issues. I couldn't get the blurred shader to work. I tried many different methods from many different sources but nothing seemed to solve my issues. I asked ChatGPT and it told me that I was blurring the textures rather than the frame buffer itself. I then fixed this issue so that the framebuffer was the blurring unit, however in the end it still didn't work. In this documentation I aim to talk about the different files and what each function includes and what it should have done in the final code.

## Particle Fragment Shader

I included shaders in my project as it was how I would get the 'Bloom' effect to work. Originally, I decided to ignore the texture/colour shader and get straight into blurring effect which is why there are many different versions that have been commented out in this file. However, the image below shows what added colour to the dragon in the image in the final code using Vec4 and Vec3. It took a bit to get this right as 'particleColour' was vec3 trying to convert to a vec4 but I figured this out with the '.rgb' at the end of 'fragColour'.

![image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/particlefragment(1).png)

Whilst using this particle shader, I'm going to comment on the parts that didn't work and did not make it to the final code as they parts helped me develop my code and let me understand how to go about it but at the same time it's code I worked on but never ended up using.

<p>A <a href="https://learnopengl.com/Advanced-Lighting/Bloom">link to opengl bloom</a>.</p>

<p>A <a href="https://learnopengl.com/Advanced-Lighting/HDR">link to opengl HDR</a>.</p>

<p>A <a href="https://github.com/NCCA/FBODemos/tree/main">link to NCCA on github FBOs</a>.</p>

<p>A <a href="https://learnopengl.com/Advanced-OpenGL/Framebuffers">link to opengl framebuffer</a>.</p>


