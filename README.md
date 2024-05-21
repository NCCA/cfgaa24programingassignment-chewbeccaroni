# Rebecca Blundell CFGAA Assignment

## Assignment Idea

The aim of my project was to create some type of glowing effect using 2 shaders in c++ using OpenGL. One shader renders the base colour or texture, the other
renders a blurred framebuffer using kernels. From the start I ran into issues. I couldn't get the blurred shader to work. I tried many different methods from many different sources but nothing seemed to solve my issues. I asked ChatGPT and it told me that I was blurring the textures rather than the frame buffer itself. I then fixed this issue so that the framebuffer was the blurring unit, however in the end it still didn't work. In this documentation I aim to talk about the different files and what each function includes and what it should have done in the final code.

## Particle Fragment Shader

I included shaders in my project as it was how I would get the 'Bloom' effect to work. Originally, I decided to ignore the texture/colour shader and get straight into blurring effect which is why there are many different versions that have been commented out in this file. However, the image below shows what added colour to the dragon in the image in the final code using Vec4 and Vec3. It took a bit to get this right as 'particleColour' was vec3 trying to convert to a vec4 but I figured this out with the '.rgb' at the end of 'fragColour'.

![image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/particlefragment(1).png)

Whilst using this particle shader, I'm going to comment on the parts that didn't work and did not make it to the final code as they parts helped me develop my code and let me understand how to go about it but at the same time it's code I worked on but never ended up using.

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/particlefragnotes(1).png)

The image above is a repeat of the final code but includes a brightness like effect. I can't get this to work now but this made the colours in the texture brighter or darker depending on the values used in the main function.

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/fragment.png)

This next one was my first attempt at a blurring effect using offsets and kernels. Using Advanced OpenGL [4] I divided everything by 16 in the kernel so that the colours shown aren't really bright and overexposed. Then you create offsets for the texture and multiply it by the weight of the kernels. The problem came when adding the texture part, because I haven't been able to add 2 shaders at the same time, I'm unable to check if this code blurs the texture or not as it shown a black screen as it comes off screen textures rather than added in textures from me. This was when I put this into ChatGPT to ask what was wrong with it and told me I was blurring the texture rather than as a frambuffer. I went through a couple of iterations of similar code to figure out what went wrong but it ended up going to waste.

Therefore, I went from a different angle and looked more at Bloom OpenGL [1] to create the blurring effect. I then ran into issues on this end as the sources online aren't up to date so some vec3/vec4 functions had changed. It also missed out code about lighting but as a novice coder I couldn't figure out what it was telling me. I concluded that it didn't make much of a difference and continued trying out methods. I used a version where it takes samples of distance to blur, to make more of a DOF effect instead but this wasn't what I was going for so this became anothe deadend. In the end I added the code into another particle shader called 'ParticleBlur' using OpenGL Bloom [1] again.

## SRC

### nglscene.cpp - InitializeGL

The problem however was the fact that I couldn't get 2 shaders to work similtaneously in NGLScene.cpp even after trying many methods. At one point I had a function called 'renderQuad' which did exactly that, It used to triangles to render a 2D texture into the scene, but this got rid of the dragon so this got discared earlier on.

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/initilizegl.png)

So instead I added the framebuffer and particle shaders through intializeGL. This establishes the background colour of the window and adds the shaders into the scene. The same code is repeated twice, however the second half isn't needed but just there for if I got the second particle shader to work. It was made for the framebuffer effects but never went through. It also inlcudes the camera for the scene.

## nglscne.cpp - PaintGL

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/paintgl.png)

PaintGL adds the dragon to the scene and goes through a loop of adding the blur texture by going between the 2 shaders like a ping pong effect. It includes transformations through NGL. Before starting this project and adding a shader, the colour of the dragon was red, hence "Colour" being set to red but not showing up. I also commented out the 'glUniform1i' as it kept spraying warnings at me. I went to the source library on Github to figure out it was this line specifically that as creating that warning which it was.

## nglscenemousecontrols.cpp

I will breifly talk about the functions in here, however as these were part of the original code from Jon Macey, I can't claim that I created these. When using the scene, the left mouse buttoms rotates the camera, and the right mouse button moves it around the scene whether that be in the x, y or z axis. This didn't work in the scene at first (or stopped working) but I managed to fix that issue in nglscene.cpp. It updates every frame so it rerenders the scene every frame. Therefore 'glClear' is needed so that the frames update and don't add on top of eachother. (Alhtough this does create a cool effect as seen below)

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/effect.png)

# Final Result

![Image](https://github.com/NCCA/cfgaa24programingassignment-chewbeccaroni/blob/main/Images/final.png)

I'm quite disappointed that I didn't get the blur effect to work as that would have made this look a lot more visually pleasing. However, I'm happy I tried and this project as a whole has helped me better understand my limits but also the limits of OpenGL. I found it hard to find out how to fix errors on the internet as alot of the code sources come from Jon Macey's NCCA github library (my own choice as it is what we were learning in workshops) so unless ChatGPT gives you a good reliable answer (0.6% probibility) it takes a while to figure out why an error isn't working which really backtracked me and slowed me down.

[1] <p>A <a href="https://learnopengl.com/Advanced-Lighting/Bloom">link to opengl bloom</a>.</p>

This website helps with establishing the set up of a bloom/glow effect but creating 2 different shaders and combining them. I used this as reference quite often, however, some parts are outdated (along with a lot of other elements in this website) so I had to figure out how to change some functions in the particle shader.

[2] <p>A <a href="https://learnopengl.com/Advanced-Lighting/HDR">link to opengl HDR</a>.</p>

A website that talks about exposure and brightness. It uses similar methods to bloom but changes things slightly so I used it to analyse and create some functions but in the end I didn't use them. 

[3] <p>A <a href="https://github.com/NCCA/FBODemos/tree/main">link to NCCA on github FBOs</a>.</p>

A whole repository for FBO's so very handy for what I'm doing. If I had issues I used this as a source as to why I'm getting such errors. Again, bit outdated and code has been updated since so some parts weren't useful but some were.

[4] <p>A <a href="https://learnopengl.com/Advanced-OpenGL/Framebuffers">link to opengl framebuffer</a>.</p>

The most useful of my sources. This really helped my understand what offsets and kernels did and why I needed them. After I understood this, I could go onto use reference [1] more easily and used this in my blurring fragment shader.


