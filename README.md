# VulkanHelloTriangle
A simple program that uses the Vulkan api to render a triangle on the screen
As this example is meant to be as simple as possible no depth buffer or space-conversion matrices are used.

To render a triangle on vulkan you have to :

1. Create an Instance
2. Interface with the window system by asking for a surface we can render and present on
3. Find all the available physical devices (the gpus on the machine)
4. Find a queue that supports presenting and rendering on the chosen physical device
4. Create a logic device by choosing from the list of physical devices 
5. Create a swapchain from the wsi surface
6. Obtain from the swapchain a set of images we can render on
7. Create a framebuffer from each swapchain image
8. Create a Render pass and subpass to specify rendertargets.
9. Create shader modules with the spir-v fragment and vertex shaders (compiled from glsl shaders with glslangValidator)
10. Create a vertex buffer to store the vertices to render
11. Create a Graphics Pipeline object to specify all the pipeline stages (no depth stencil, viewport and scissor are dynamic)
12. Ask the swapchain for the next image we can render on 
13. Create a command buffer, bind the renderpass, the pipeline, set the dynamic stages and issue a draw call
14. Place a pre-present barrier
15. Wait for the command to complete
14. Present the queue 
15. Weep with joy

#references
* <a href="https://renderdoc.org/vulkan-in-30-minutes.html">Vulkan in 30 minutes</a>, a great overview on the vulkan API.
* <a href="https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/pdf/vkspec.pdf">Vulkan specifications</a>, really well written, incredibly detailed and yet easy to understand.
* <a href="http://lunarg.com/vulkan-sdk/">The LunarG SDK</a> for the api headers, loader, validation layers and samples.
* <a href="https://github.com/SaschaWillems/Vulkan>Sascha Willems code samples</a>, a LOT of great samples.

If you have any doubts or remarks, please contact me
