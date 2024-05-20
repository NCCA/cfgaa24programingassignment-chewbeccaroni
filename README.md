# Rebecca Blundell CFGAA Assignment

- Assignment Idea

The aim of my project was to create some type of glowing effect using 2 shaders in c++ using OpenGL. One shader renders the base colour or texture, the other
renders a blurred framebuffer using kernels. From the start I ran into issues. I couldn't get the blurred shader to work. I tried many different methods from many different sources but nothing seemed to solve my issues. I asked ChatGPT and it told me that I was blurring the textures rather than the frame buffer itself. I then fixed this issue so that the framebuffer was the blurring unit, however in the end it still didn't work. In this documentation I aim to talk about the different files and what each function includes and what it should do.

<p>A <a href="https://learnopengl.com/Advanced-Lighting/Bloom">link to opengl bloom</a>.</p>

<p>A <a href="https://learnopengl.com/Advanced-Lighting/HDR">link to opengl HDR</a>.</p>

<p>A <a href="https://github.com/NCCA/FBODemos/tree/main">link to NCCA on github FBOs</a>.</p>

<p>A <a href="https://learnopengl.com/Advanced-OpenGL/Framebuffers">link to opengl framebuffer</a>.</p>


