/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL
 * functions.
 *
 * Copyright 2005-2025, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file win.h
 * \brief Header file with useful display functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_WIN__H
#define JB_WIN__H 1

#include "math.h"

#if JBW == JBW_NO

void jbw_show_error_terminal (const char *message);
void jbw_show_warning_terminal (const char *message);

static inline int
jbw_init (int *argn __attribute__((unused)),
          ///< pointer to the number of command line arguments.
          char ***argc __attribute__((unused)))
  ///< pointer to the command line arguments.
{
  jb_show_error = jbw_show_error_terminal;
  jb_show_warning = jbw_show_warning_terminal;
  return 0;
}

#elif JBW == JBW_GTK

#include <stdbool.h>
#include <ft2build.h>
#include <freetype/freetype.h>

#include <png.h> // to remove

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <GL/glew.h>
#if HAVE_VULKAN
#include <vulkan/vulkan.h>
#endif
#if HAVE_FREEGLUT
#include <GL/freeglut.h>
#elif HAVE_SDL
#include <SDL.h>
#if HAVE_VULKAN
#include <SDL_vulkan.h>
#endif
#elif HAVE_GLFW
#if HAVE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#else
#if HAVE_VULKAN
#include <gdk/gdk.h>
#ifdef GDK_WINDOWING_WAYLAND
#if GTK_MAJOR_VERSION > 3
#include <gdk/wayland/gdkwayland.h>
#else
#include <gdk/gdkwayland.h>
#endif
#include <vulkan/vulkan_wayland.h>
#elif defined(GDK_WINDOWING_X11)
#if GTK_MAJOR_VERSION > 3
#include <gdk/x11/gdkx.h>
#else
#include <gdk/gdkx.h>
#endif
#include <vulkan/vulkan_xlib.h>
#elif defined(GDK_WINDOWING_WIN32)
#include <gdk/win32/gdkwin32.h>
#include <vulkan/vulkan_win32.h>
#elif defined(GDK_WINDOWING_MACOS)
#include <gdk/macos/gdkmacos.h>
#include <vulkan/vulkan_metal.h>
#include <objc/runtime.h>
#include <objc/message.h>
#else
#error "Unknown GDK Windowing"
#endif
#endif
#endif
#include <gtk/gtk.h>

/**
 * \def JBW_GRAPHIC_N_TYPES
 * \brief number of graphical file formats.
 * \def JBW_GRAPHIC_N_PATTERNS
 * \brief maximum number of graphical file format patterns.
 */
#if JBW_GRAPHIC_OUTPUT == JBW_GRAPHIC_OUTPUT_GDK_PIXBUF
#define JBW_GRAPHIC_N_TYPES 7
#define JBW_GRAPHIC_N_PATTERNS 4
#else
#define JBW_GRAPHIC_N_TYPES 1
#define JBW_GRAPHIC_N_PATTERNS 2
#endif
#define JBW_WINDOW_WIDTH 100
///< macro to define the default JBWGraphics window width.
#define JBW_WINDOW_HEIGHT 100
///< macro to define the default JBWGraphics window height.

///> enum to define the data types of a JBWArrayEditor column.
enum JBWEditorWidgetType
{
  JBW_EDITOR_WIDGET_TYPE_TEXT = 0,      ///< text data.
  JBW_EDITOR_WIDGET_TYPE_INT = 1,       ///< integer number data.
  JBW_EDITOR_WIDGET_TYPE_FLOAT = 2,     ///< floating point number data.
  JBW_EDITOR_WIDGET_TYPE_TIME = 3       ///< time data.
};

///> Enum to define Vulkan error codes.
enum JBWVKErrorCode
{
  JBW_VK_ERROR_CODE_SUCCESS = 0,        ///< success.
  JBW_VK_FAILED_TO_INIT_WINDOWS,  ///< failed to init the windows GUI.
  JBW_VK_ERROR_CODE_FAILED_TO_OPEN_WINDOW,      ///< failed to open the window.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_INSTANCE,
  ///< failed to create Vulkan instance.
  JBW_VK_ERROR_CODE_NO_INSTANCE_EXTENSIONS,
  ///< no Vulkan instance extensions supported.
  JBW_VK_ERROR_CODE_NO_PHYSICAL_DEVICES,
  ///< failed to find a GPU with Vulkan support.
  JBW_VK_ERROR_CODE_BAD_PHYSICAL_DEVICES,
  ///< error reading Vulkan physical devices.
  JBW_VK_ERROR_CODE_NO_SUITABLE_PHYSICAL_DEVICES,
  ///< no suitable physical devices.
  JBW_VK_ERROR_CODE_NO_SUITABLE_QUEUE_FAMILY,
  ///< no suitable Vulkan physical device queue family.
  JBW_VK_ERROR_CODE_NO_DEVICE,
  ///< failed to create the Vulkan device.
  JBW_VK_ERROR_CODE_NO_SURFACE,
  ///< failed to create a Vulkan surface.
  JBW_VK_ERROR_CODE_NO_SURFACE_SUPPORT,
  ///< Vulkan device does not support surfaces.
  JBW_VK_ERROR_CODE_NO_AVAILABLE_EXTENSION,
  ///< no available Vulkan extension.
  JBW_VK_ERROR_CODE_NO_SURFACE_FORMATS,
  ///< no surface formats.
  JBW_VK_ERROR_CODE_FAILED_TO_FIND_SUITABLE_SURFACE_FORMAT,
  ///< failed to find a suitable surface format
  JBW_VK_ERROR_CODE_NO_SWAPCHAIN,
  ///< failed to create the Vulkan swap chain.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VIEW,
  ///< failed to create the image view.
  JBW_VK_ERROR_CODE_FAILED_TO_OPEN_SHADER,
  ///< failed to open the shader module.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VERTEX_SHADER,
  ///< failed to create the vertex shader module.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VERTEX_SHADER,
  ///< failed to create the image vertex shader module.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_FRAGMENT_SHADER,
  ///< failed to create the fragment shader module.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_FRAGMENT_SHADER,
  ///< failed to create the image fragment shader module.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_PIPELINE_LAYOUT,
  ///< failed to create the pipeline layout.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_PIPELINE_LAYOUT,
  ///< failed to create the image pipeline layout.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_RENDER_PASS,
  ///< failed to create the render pass.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_PIPELINE,
  ///< failed to create graphics pipeline.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_PIPELINE,
  ///< failed to create image pipeline.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_FRAMEBUFFER,
  ///< failed to create framebuffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_COMMAND_POOL,
  ///< failed to create the command pool.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_COMMAND_BUFFERS,
  ///< failed to allocate command buffers.
  JBW_VK_ERROR_CODE_FAILED_TO_RECORD_COMMAND_BUFFER,
  ///< failed to record command buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_BEGIN_RECORDING_COMMAND_BUFFER,
  ///< failed to begin recording command buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_SEMAPHORES,
  ///< failed to create semaphores.
  JBW_VK_ERROR_CODE_FAILED_TO_SUBMIT_DRAW_COMMAND_BUFFER,
  ///< failed to submit draw command buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_ACQUIRE_SWAP_CHAIN_IMAGE,
  ///< failed to acquire swap chain image.
  JBW_VK_ERROR_CODE_FAILED_TO_PRESENT_SWAP_CHAIN_IMAGE,
  ///< failed to present swap chain image.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_BUFFER,
  ///< failed to create buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_FIND_SUITABLE_MEMORY_TYPE,
  ///< failed to find suitable memory type.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_BUFFER_MEMORY,
  ///< failed to allocate buffer memory.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VERTEX_BUFFER,
  ///< failed to create the vertex buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VERTEX_BUFFER,
  ///< failed to create the image vertex buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_STAGING_BUFFER,
  ///< failed to create the staging buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_INDEX_BUFFER,
  ///< failed to create the index buffer.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_SET_LAYOUT,
  ///< failed to create descriptor set layout.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_DESCRIPTOR_SET_LAYOUT,
  ///< failed to create image descriptor set layout.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_POOL_LINES,
  ///< failed to create descriptor pool for lines.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_POOL_IMAGES,
  ///< failed to create descriptor pool for images.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_LINE,
  ///< failed to allocate descriptor sets for a line.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_LINES,
  ///< failed to allocate descriptor sets for lines.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_IMAGE,
  ///< failed to allocate descriptor sets for a image.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE,
  ///< failed to create image.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_IMAGE_MEMORY,
  ///< failed to allocate image memory.
  JBW_VK_ERROR_CODE_UNSUPPORTED_LAYOUT_TRANSITION,
  ///< unsupported layout transition.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_IMAGE,
  ///< failed to create texture image.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_IMAGE_VIEW,
  ///< failed to create texture image view.
  JBW_VK_ERROR_CODE_FAILED_TO_LOAD_LOGO_IMAGE,
  ///< failed to load logo image.
  JBW_VK_ERROR_CODE_FAILED_TO_INIT_IMAGE,
  ///< failed to init image.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_SAMPLER,
  ///< failed to create texture sampler.
  JBW_VK_ERROR_CODE_FAILED_TO_INIT_FREETYPE,
  ///< failed to init FreeType library.
  JBW_VK_ERROR_CODE_FAILED_TO_OPEN_FONT,
  ///< failed to open font.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_TEXT,
  ///< failed to allocate text.
  JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_TEXT_DESCRIPTOR_SETS,
  ///< failed to allocate text descriptor sets.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXT_IMAGE,
  ///< failed to create text image.
};

#if JBM_HIGH_PRECISION > 2
typedef GtkEntry JBWFloatEntry;
#else
typedef GtkSpinButton JBWFloatEntry;
#endif
///< widget to work with float number.

/**
 * \struct JBWVertex
 * \brief struct to pack the vertex data.
 */
typedef struct
{
  float position[2];            ///< position.
} JBWVertex;

/**
 * \struct JBWVertexImage
 * \brief struct to pack the image vertex data.
 */
typedef struct
{
  float position[2];            ///< position.
  float texture[2];             ///< texture coordinates.
} JBWVertexImage;

/**
 * \struct JBWUniformColor
 * \brief struct to define uniform colors.
 */
typedef struct
{
  float color[3];               ///< RGB color vector.
} JBWUniformColor;

#if HAVE_VULKAN

#define JBW_MAX_FRAMES_IN_FLIGHT 2
///< maximum number of frames to be processed concurrently.
#define JBW_VK_N_DEVICE_EXTENSIONS 1    ///< number or Vulkan device extensions.
#define JBW_VK_N_VALIDATION_LAYERS 1    ///< number of Vulkan validation layers.

enum
{
  JBW_VK_ERROR_NONE = 0,        ///< no errors.
  JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_INSTANCE,
  ///< failed to create a Vulkan instance.
  JBW_VK_ERROR_NO_VULKAN_INSTANCE_EXTENSIONS,
  ///< no Vulkan instance extensions.
  JBW_VK_ERROR_NO_VULKAN_SURFACE_EXTENSION,
  ///< no VK_KHR_surface Vulkan extension.
  JBW_VK_ERROR_NO_AVAILABLE_VULKAN_VALIDATION_LAYERS,
  ///< no available Vulkan validation layers.
  JBW_VK_ERROR_NO_VULKAN_SURFACE,
  ///< unable to create a Vulkan surface.
  JBW_VK_ERROR_NO_VULKAN_PHYSICAL_DEVICES,
  ///< failed to find a GPU with Vulkan support.
  JBW_VK_ERROR_BAD_VULKAN_PHYSICAL_DEVICES,
  ///< bad Vulkan physical devices.
  JBW_VK_ERROR_NO_SUITABLE_VULKAN_PHYSICAL_DEVICES,
  ///< no suitable Vulkan physical devices.
  JBW_VK_ERROR_NO_AVAILABLE_VULKAN_EXTENSION,
  ///< no available Vulkan extension.
  JBW_VK_ERROR_NO_SUITABLE_VULKAN_QUEUE_FAMILY,
  ///< no suitable Vulkan queue family.
  JBW_VK_ERROR_UNSUPPORTED_VULKAN_SURFACES,
  ///< unsupported Vulkan surfaces.
  JBW_VK_ERROR_NO_VULKAN_DEVICE,
  ///< no Vulkan logical device.
  JBW_VK_ERROR_NO_VULKAN_SWAP_CHAIN,
  ///< no Vulkan swap chain.
  JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_IMAGE_VIEW,
  ///< failed to create a Vulkan swap chain image view.
  JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_RENDER_PASS,
  ///< failed to create the Vulkan render pass.
  JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VULKAN_DESCRIPTOR_SET_LAYOUT,
  ///< failed to create the Vulkan descriptor set layout.
  JBW_VK_ERROR_FAILED_TO_OPEN_SHADER_FILE,
  ///< failed to open the shader file.
  JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_SHADER_MODULE,
  ///< failed to create the Vulkan shader module.
} JBWVKError;                   ///< enum to define Vulkan error codes.

/**
 * \struct JBWVKSwapChainSupportDetails
 * \brief struct to pack the Vulkan swap chain support details.
 */
typedef struct
{
  VkSurfaceCapabilitiesKHR capabilities;
  ///< Vulkan surface capabilities.
  VkSurfaceFormatKHR *formats;  ///< Vulkan surface formats array.
  VkPresentModeKHR *present_modes;      ///< Vulkan present modes.
} JBWVKSwapChainSupportDetails;

/**
 * \struct JBWVK
 * \brief Struct to pack the Vulkan resources data.
 */
typedef struct
{
  VkInstance instance;          ///< Vulkan instance.
#if JBW_VK_N_VALIDATION_LAYERS
  VkDebugUtilsMessengerEXT *debug_messenger;
  ///< Vulkan validation layers debug messenger.
#endif
  VkSurfaceKHR surface;         ///< Vulkan surface.
  VkPhysicalDevice physical_device;     ///< Vulkan graphics card handle.
  VkDevice device;              ///< Vulkan logical device.
  VkExtent2D extent;            ///< Vulkan extent.
  VkQueue graphics_queue;       ///< Vulkan graphics queue.
  VkQueue present_queue;        ///< Vulkan present queue.
  VkSurfaceFormatKHR surface_format;    ///< Vulkan surface format.
  VkSwapchainKHR swap_chain;    ///< Vulkan swap chain.
  VkImage *swap_chain_images;   ///< array of Vulkan swap chain images.
  VkImageView *swap_chain_image_views;
  ///< array of Vulkan swap chain image views.
  VkPipelineLayout pipeline_layout;     ///< Vulkan pipeline layout.
  VkPipelineLayout image_pipeline_layout;
  ///< Vulkan image pipeline layout.
  VkRenderPass render_pass;     ///< Vulkan render pass.
  VkPipeline pipeline;          ///< Vulkan graphics pipeline.
  VkPipeline image_pipeline;    ///< Vulkan image pipeline.
  VkFramebuffer *swap_chain_framebuffers;
  ///< array of Vulkan framebuffers.
  VkCommandPool command_pool;   ///< Vulkan command pool.
  VkCommandBuffer command_buffers[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan command buffers.
  VkSemaphore image_available_semaphores[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan semaphores to signal that an image has been acquired from
  ///< the swap chain.
  VkSemaphore render_finished_semaphores[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan semaphores to signal that rendering has finished.
  VkFence in_flight_fences[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan fences to make sure only one frame is rendering at a
  ///< time.
  VkBuffer vertex_buffer_frame; ///< vertex buffer handle.
  VkBuffer vertex_buffer_image; ///< image vertex buffer handle.
  VkDeviceMemory vertex_buffer_memory_frame;
  ///< frame vertex buffer memory handle.
  VkDeviceMemory vertex_buffer_memory_image;
  ///< image vertex buffer memory handle.
  VkDescriptorSetLayout descriptor_set_layout;
  ///< Vulkan descriptor set layout.
  VkDescriptorSetLayout image_descriptor_set_layout;
  ///< Vulkan image descriptor set layout.
  VkBuffer uniform_buffers[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of unifform buffer handles.
  VkDeviceMemory uniform_buffers_memory[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of memory uniform buffers.
  void *uniform_buffers_mapped[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of mapped uniform buffers.
  VkDescriptorPool descriptor_pool_lines;
  ///< Vulkan descriptor pool for lines.
  VkDescriptorPool descriptor_pool_images;
  ///< Vulkan descriptor pool for images.
  VkDescriptorSet (*descriptor_sets_lines)[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan description set handles for lines.
  VkDescriptorSet (*descriptor_sets_images)[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan description set handles for images.
  VkDescriptorSet text_descriptor_sets[JBW_MAX_FRAMES_IN_FLIGHT];
  ///< array of Vulkan text description set handles.
  VkSampler texture_sampler;    ///< Vulkan texture sampler.
  bool framebuffer_resized;     ///< flags that a resize has happened.
  uint32_t queue_family_index_graphics; ///< Vulkan graphics queue family index.
  uint32_t queue_family_index_present;  ///< Vulkan present queue family index.
  uint32_t n_image_views;       ///< number of Vulkan swap chain images.
  uint32_t current_frame;       ///< current frame index.
  uint32_t n_image_channels;    ///< number of image channels.
  uint32_t n_lines;             ///< maximum number of lines.
  uint32_t n_images;            ///< maximum number of images.
} JBWVK;

#endif

/**
 * \struct JBWImage
 * \brief struct to define an image for the JBWGraphic widget.
 */
typedef struct
{
#if HAVE_VULKAN
  JBWVK *vk;                    ///< JBWVK struct;
  VkImage vk_image;             ///< Vulkan image.
  VkDeviceMemory vk_memory;     ///< Vulkan image memory.
  VkImageView vk_view;          ///< Vulkan image view.
#endif
  GLfloat matrix[16];           ///< projection matrix.
  GLfloat vertices[8];          ///< vertices.
  GLfloat square_texture[8];    ///< square texture vertices.
  GLushort elements[6];         ///< element indices.
  GLint uniform_texture;        ///< texture constant.
  GLint attribute_texture;      ///< texture variable.
  GLint attribute_texture_position;     ///< texture variable position.
  GLint uniform_matrix;         ///< projection matrix.
  GLuint vbo;                   ///< vertices buffer object.
  GLuint ibo;                   ///< indices buffer object.
  GLuint vbo_texture;           ///< texture vertex buffer object.
  GLuint program_texture;       ///< texture program.
  GLuint id_texture;            ///< texture identifier.
  guchar *pixel;                ///< image bytes.
  unsigned int width;           ///< image width.
  unsigned int height;          ///< image height.
  unsigned int row_stride;      ///< image row stride.
  unsigned int nbytes;          ///< number of image bytes.
} JBWImage;                     ///< image widget.

/**
 * \struct JBWGraphic
 * \brief widget to drawing graphics.
 */
typedef struct _JBWGraphic JBWGraphic;
struct _JBWGraphic
{
#if HAVE_VULKAN
  JBWVK vk[1];                  ///< JBWVK struct.
  unsigned int is_vulkan_supported;
  ///< flag set to 1 when Vulkan is supported.
#endif
  JBWImage *image_xtic[JBW_GRAPHIC_N_TICS];
  ///< array of x-axis tic images.
  JBWImage *image_ytic[JBW_GRAPHIC_N_TICS];
  ///< array of y-axis tic images.
  JBWImage *image_ztic[JBW_GRAPHIC_N_TICS];
  ///< array of z-axis tic images.
  JBDOUBLE xtic[JBW_GRAPHIC_N_TICS];    ///< x-axis tics.
  JBDOUBLE ytic[JBW_GRAPHIC_N_TICS];    ///< y-axis tics.
  JBDOUBLE ztic[JBW_GRAPHIC_N_TICS];    ///< z-axis tics.
  void (*draw) (JBWGraphic * graphic);
  ///< pointer to the draw function.
  int (*calculate) (JBWGraphic * graphic);
  ///< pointer to a calculate function.
  JBWImage *logo;               ///< logo.
  JBWImage *image_title;        ///< title image.
  JBWImage *image_x;            ///< x-label image.
  JBWImage *image_y;            ///< 1st y-label image.
  JBWImage *image_yy;           ///< 2nd y-label image.
  JBWImage *image_z;            ///< 1st z-label image.
  JBWImage *image_zz;           ///< 2nd z-label image.
#if HAVE_GTKWIDGET
  GtkWindow *window;            ///< GtkWindow window.
  GtkWidget *widget;            ///< GtkWidget widget.
#elif HAVE_FREEGLUT
  int window;                   ///< FreeGLUT window number.
#elif HAVE_SDL
  SDL_Window *window;           ///< SDL window.
  SDL_GLContext *sdl_context;   ///< SDL context.
#elif HAVE_GLFW
  GLFWwindow *window;           ///< GLFW window.
#endif
  FT_Library ft;                ///< FreeType data.
  FT_Face face;                 ///< FreeType face to draw text.
  void *data;                   ///< user data.
  const char *str_title;        ///< title label.
  const char *str_x;            ///< x label.
  const char *str_y;            ///< 1st y label.
  const char *str_yy;           ///< 2nd y label.
  const char *str_z;            ///< 1st z label.
  const char *str_zz;           ///< 2nd z label.
  JBDOUBLE xmin;                ///< minimum x-range.
  JBDOUBLE xmax;                ///< maximum x-range.
  JBDOUBLE ymin;                ///< minimum y-range.
  JBDOUBLE ymax;                ///< maximum y-range.
  JBDOUBLE zmin;                ///< minimum y-range.
  JBDOUBLE zmax;                ///< maximum y-range.
  GLfloat sx;                   ///< x text scale factor.
  GLfloat sy;                   ///< y text scale factor.
  /* int type; ///< type of graphic (NOT IMPLEMENTED) */
  /* int legend; ///< legend drawing (NOT IMPLEMENTED) */
  int resize;
  ///< 1 if automatic range has to be set to extremal variable values.
  int grid;                     ///< 1 on grid drawing.
  int map;
  ///< 1 if coordenates system has to be proportional to screen.
  int nx;                       ///< current number of x-axis labels.
  int ny;                       ///< current number of y-axis labels.
  int nz;                       ///< current number of z-axis labels.
  int nxmax;                    ///< maximum number of x-axis labels.
  int nymax;                    ///< maximum number of y-axis labels.
  int nzmax;                    ///< maximum number of z-axis labels.
  int x1;                       ///< minimum viewport x-coordinate.
  int x2;                       ///< maximum viewport x-coordinate.
  int y1;                       ///< minimum viewport y-coordinate.
  int y2;                       ///< maximum viewport y-coordinate.
  int minimum_width;            ///< minimum widget width.
  int minimum_height;           ///< maximum widget width.
  int width;                    ///< widget width.
  int height;                   ///< widget width.
  int init;                     ///< 1 on initated, 0 otherwise
  int char_ascender;            ///< character ascender.
  int char_descender;           ///< character descender.
  unsigned int char_width;      ///< character width.
  unsigned int char_height;     ///< character height.
  unsigned int has_to_close;    ///< to close the GtkWindow widget.
#if HAVE_GTKWIDGET
  unsigned int is_window_realized;
  ///< flag set to 1 when the GtkWindow is realized.
#endif
  uint32_t screen_width;        ///< screen resolution width.
  uint32_t screen_height;       ///< screen resolution height.
  GLint in_2D_position;         ///< 2D position.
  GLint uniform_2D_color;       ///< 2D color.
  GLint uniform_2D_matrix;      ///< 2D matrix.
  GLint in_3D_position;         ///< 3D position.
  GLint uniform_3D_color;       ///< 3D color.
  GLint uniform_3D_matrix;      ///< 3D matrix.
  GLint in_2Dc_position;        ///< 2D with color position.
  GLint in_2Dc_color;           ///< 2D with color color.
  GLint uniform_2Dc_matrix;     ///< 2D with color matrix.
  GLint in_3Dc_position;        ///< 3D with color position.
  GLint in_3Dc_color;           ///< 3D with color color.
  GLint uniform_3Dc_matrix;     ///< 3D with color matrix.
  GLint in_text_position;       ///< text position.
  GLint uniform_text_color;     ///< text color.
  GLint uniform_text;           ///< text uniform.
  GLuint vbo_text;              ///< text vertex buffer object.
  GLuint program_2D;            ///< 2D program.
  GLuint program_3D;            ///< 3D program.
  GLuint program_2Dc;           ///< 2D program.
  GLuint program_3Dc;           ///< 3D program.
  GLuint program_text;          ///< text program.
};

#if GTK_MAJOR_VERSION < 4
/**
 * \struct JBWArrayEditor
 * \brief widget to edit matrix data.
 */
typedef struct
{
  GtkScrolledWindow *scrolled;  ///< GtkScrolledWindow widget.
  GtkButton **button_numeric;
  ///< array of row numeric GtkButton widgets.
  GtkButton **button_title;
  ///< array of column title GtkButton widgets.
  GtkWidget ***matrix_entry;    ///< matrix of GtkWidget widgets.
  GtkGrid *grid;                ///< GtkGrid widget.
  int *type;                    ///< array of widget types.
  int ncolumns;                 ///< number of columns.
  int nrows;                    ///< number of rows.
  int nfull;                    ///< number of full columns.
} JBWArrayEditor;               ///< widget to edit matrices.
#endif

///> macro to do after and swapped GSignal connections.
#define jbw_signal_connect_swapped_after(instance, detailed_signal, c_handler, \
  data) \
      g_signal_connect_data((instance), (detailed_signal), (c_handler), \
      (data), 0, G_CONNECT_SWAPPED | G_CONNECT_AFTER)

#if JBM_HIGH_PRECISION > 2
#define jbw_float_entry_new (JBWFloatEntry*)gtk_entry_new
///< macro to unify float point numbers entry widgets.
#else
#define jbw_float_entry_new (JBWFloatEntry*)gtk_spin_button_new
#endif

extern GtkWindow *window_parent;
extern GdkGLContext *jbw_gdk_gl_context;
extern JBWGraphic *jbw_graphic_pointer;

extern const GLfloat jbw_black[4];
extern const GLfloat jbw_darkred[4];
extern const GLfloat jbw_darkgreen[4];
extern const GLfloat jbw_darkblue[4];
extern const GLfloat jbw_red[4];
extern const GLfloat jbw_brown[4];
extern const GLfloat jbw_green[4];
extern const GLfloat jbw_greenblue[4];
extern const GLfloat jbw_blue[4];
extern const GLfloat jbw_violet[4];
extern const GLfloat jbw_yellow[4];
extern const GLfloat jbw_pink[4];
extern const GLfloat jbw_lightblue[4];
extern const GLfloat jbw_starred[4];
extern const GLfloat jbw_stargreen[4];
extern const GLfloat jbw_starblue[4];
extern const GLfloat jbw_stargray[4];
extern const GLfloat jbw_white[4];

extern const GLfloat jbw_identity[16];

#if HAVE_GTKWIDGET
extern int (*jbw_graphic_loop_idle) (void);
extern GMainLoop *jbw_graphic_loop_pointer;
#elif HAVE_FREEGLUT
extern void (*jbw_graphic_loop_idle) (void);
extern void (*jbw_graphic_loop_resize) (int width, int height);
extern void (*jbw_graphic_loop_render) (void);
#elif HAVE_SDL
extern int (*jbw_graphic_loop_idle) (void);
extern void (*jbw_graphic_loop_resize) (int width, int height);
extern void (*jbw_graphic_loop_render) (void);
#elif HAVE_GLFW
extern int (*jbw_graphic_loop_idle) (void);
extern void (*jbw_graphic_loop_render) (void);
extern unsigned int jbw_graphic_loop_exit;
#endif

int jbw_init_gtk (int *argn, char ***argc);
void jbw_process_pending ();

void jbw_show_message_gtk (const char *title, const char *message,
                           GtkMessageType type);
void jbw_show_error_gtk (const char *message);
void jbw_show_warning_gtk (const char *message);
void jbw_combo_box_set_strings (GtkComboBoxText * combo, char **strings, int n);
GtkComboBoxText *jbw_combo_box_new_with_strings (char **strings, int n);

void jbw_float_entry_set_value_with_format (JBWFloatEntry * entry,
                                            char *format, JBDOUBLE value);
#if JBM_HIGH_PRECISION > 2
void jbw_float_entry_set_value (JBWFloatEntry * entry, JBDOUBLE value);
JBDOUBLE jbw_float_entry_get_value (JBWFloatEntry * entry);
#else
#define jbw_float_entry_set_value gtk_spin_button_set_value
///< macro to unify the set value function of float point numbers entry widgets.
#define jbw_float_entry_get_value gtk_spin_button_get_value
///< macro to unify the get value function of float point numbers entry widgets.
#endif

void jbw_draw_clear (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void jbw_draw_range (JBFLOAT * xmin, JBFLOAT * xmax);
void jbw_draw_rangel (JBDOUBLE * xmin, JBDOUBLE * xmax);
void jbw_draw_tics (JBFLOAT xmin, JBFLOAT xmax, int nlabels, int *n,
                    JBFLOAT * tic);
void jbw_draw_ticsl (JBDOUBLE xmin, JBDOUBLE xmax, int nlabels, int *n,
                     JBDOUBLE * tic);
void jbw_draw_orthogonal_matrix (GLint uniform, GLfloat x, GLfloat y,
                                 GLfloat w, GLfloat h);
void jbw_draw_orthogonal_matrixl (GLint uniform, GLdouble x, GLdouble y,
                                  GLdouble w, GLdouble h);

JBWImage *jbw_image_new_from_file (const char *name);

void jbw_graphic_destroy (void);
void jbw_graphic_init (void);
void jbw_graphic_resize (int width, int height);
void jbw_graphic_render (void);
void jbw_graphic_loop (void);
void jbw_graphic_set_title (const char *title);
int jbw_graphic_set_logo (const char *name);
JBWGraphic *jbw_graphic_new (unsigned int nx, unsigned int ny,
                             unsigned int nz,
                             void (*draw) (JBWGraphic * graphic),
                             const char *title);
void jbw_graphic_get_display_size (void);
void jbw_graphic_draw_text (const char *string,
                            GLfloat x, GLfloat y, const GLfloat * color);
void jbw_graphic_map_resize (void);
void jbw_graphic_draw_resize (JBFLOAT * x, JBFLOAT * y1, JBFLOAT * y2,
                              JBFLOAT * z1, JBFLOAT * z2, int n);
void jbw_graphic_draw_resizel (JBDOUBLE * x, JBDOUBLE * y1, JBDOUBLE * y2,
                               JBDOUBLE * z1, JBDOUBLE * z2, int n);
void jbw_graphic_draw_resizev (void *x, void *y1, void *y2, void *z1,
                               void *z2, unsigned int size, int n);
void jbw_graphic_draw_resizevl (void *x, void *y1, void *y2, void *z1,
                                void *z2, unsigned int size, int n);
void jbw_graphic_draw_rectangles_color (GLfloat * vertex, GLushort * index,
                                        unsigned int n);
void jbw_graphic_draw_farray (JBFLOAT * x, JBFLOAT * y, unsigned int n,
                              const GLfloat * color, GLenum type);
void jbw_graphic_draw_darray (JBDOUBLE * x, JBDOUBLE * y, unsigned int n,
                              const GLfloat * color, GLenum type);
void jbw_graphic_draw_rectangle (JBFLOAT x1, JBFLOAT y1, JBFLOAT x2,
                                 JBFLOAT y2, const GLfloat * color);
void jbw_graphic_draw_rectanglel (JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE x2,
                                  JBDOUBLE y2, const GLfloat * color);
void jbw_graphic_draw_labels (void);
void jbw_graphic_draw_logo (void);
void jbw_graphic_draw_lines (JBFLOAT * x, JBFLOAT * y1, JBFLOAT * y2,
                             JBFLOAT * z1, JBFLOAT * z2, int n);
void jbw_graphic_draw_linesl (JBDOUBLE * x, JBDOUBLE * y1, JBDOUBLE * y2,
                              JBDOUBLE * z1, JBDOUBLE * z2, int n);
void jbw_graphic_draw_linesv (void *x, void *y1, void *y2, void *z1,
                              void *z2, unsigned int size, int n);
void jbw_graphic_draw_linesvl (void *x, void *y1, void *y2, void *z1,
                               void *z2, unsigned int size, int n);
void jbw_graphic_save (char *file_name);
void jbw_graphic_dialog_save (void);

#if GTK_MAJOR_VERSION < 4
void jbw_array_editor_check_column (JBWArrayEditor * editor, int column,
                                    int type);
void jbw_array_editor_set_element (JBWArrayEditor * editor, int row,
                                   int column, const char *str);
char *jbw_array_editor_get_element (JBWArrayEditor * editor, int row,
                                    int column);
void jbw_array_editor_set_element_int (JBWArrayEditor * editor, int row,
                                       int column, long int x);
long int jbw_array_editor_get_element_int (JBWArrayEditor * editor,
                                           int row, int column);
void jbw_array_editor_set_element_float (JBWArrayEditor * editor, int row,
                                         int column, JBDOUBLE x);
JBDOUBLE jbw_array_editor_get_element_float (JBWArrayEditor * editor,
                                             int row, int column);
void jbw_array_editor_set_element_time (JBWArrayEditor * editor, int row,
                                        int column, JBDOUBLE t);
JBDOUBLE jbw_array_editor_get_element_time (JBWArrayEditor * editor,
                                            int row, int column);
void jbw_array_editor_set_column (JBWArrayEditor * editor, int column,
                                  char **c);
void jbw_array_editor_get_column (JBWArrayEditor * editor, int column,
                                  char **c);
void jbw_array_editor_set_column_int (JBWArrayEditor * editor, int column,
                                      long int *x);
void jbw_array_editor_get_column_int (JBWArrayEditor * editor, int column,
                                      long int *x);
void jbw_array_editor_set_column_float (JBWArrayEditor * editor,
                                        int column, JBFLOAT * x);
void jbw_array_editor_set_column_floatl (JBWArrayEditor * editor,
                                         int column, JBDOUBLE * x);
void jbw_array_editor_get_column_float (JBWArrayEditor * editor,
                                        int column, JBFLOAT * x);
void jbw_array_editor_get_column_floatl (JBWArrayEditor * editor,
                                         int column, JBDOUBLE * x);
void jbw_array_editor_set_column_time (JBWArrayEditor * editor, int column,
                                       JBDOUBLE * t);
void jbw_array_editor_get_column_time (JBWArrayEditor * editor, int column,
                                       JBDOUBLE * t);
void jbw_array_editor_set_column_sensitive (JBWArrayEditor * editor,
                                            int column, int sensitive);
void jbw_array_editor_show_column (JBWArrayEditor * editor, int column);
void jbw_array_editor_hide_column (JBWArrayEditor * editor, int column);
void jbw_array_editor_insert_row (JBWArrayEditor * editor, int row);
void jbw_array_editor_remove_row (JBWArrayEditor * editor, int row);
void jbw_array_editor_set_rows (JBWArrayEditor * editor, int n);
void jbw_array_editor_set_title (JBWArrayEditor * editor, int column,
                                 char *title);
void jbw_array_editor_destroy (JBWArrayEditor * editor);
JBWArrayEditor *jbw_array_editor_new (int ncolumns, int nfull, int nrows,
                                      const int *types, const char **label);
#endif

/**
 * Function to init the show error and warning functions.
 */
static inline int
jbw_init (int *argn __attribute__((unused)),
          ///< pointer to the number of command line arguments.
          char ***argc __attribute__((unused)))
  ///< pointer to the command line arguments.
{
  jb_show_error = jbw_show_error_gtk;
  jb_show_warning = jbw_show_warning_gtk;
  return jbw_init_gtk (argn, argc);
}

/**
 * Function to set the resize property of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_resize (JBWGraphic *graphic,    ///< JBWGraphic widget.
                        int resize)     ///< 1 if automatic bounds resize.
{
  graphic->resize = resize;
}

/**
 * Function to set the grid property of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_grid (JBWGraphic *graphic,      ///< JBWGraphic widget.
                      int grid) ///< 1 if visible grid.
{
  graphic->grid = grid;
}

/**
 * Function to set the x label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_xlabel (JBWGraphic *graphic,    ///< JBWGraphic widget.
                        const char *str_x)      ///< x label.
{
  graphic->str_x = str_x;
}

/**
 * Function to set the 1st y label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_ylabel (JBWGraphic *graphic,    ///< JBWGraphic widget.
                        const char *str_y)      ///< 1st y label.
{
  graphic->str_y = str_y;
}

/**
 * Function to set the 2nd y label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_yylabel (JBWGraphic *graphic,   ///< JBWGraphic widget.
                         const char *str_yy)    ///< 2nd y label.
{
  graphic->str_yy = str_yy;
}

/**
 * Function to set the 1st z label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_zlabel (JBWGraphic *graphic,    ///< JBWGraphic widget.
                        const char *str_z)      ///< 1st z label.
{
  graphic->str_z = str_z;
}

/**
 * Function to set the 2nd z label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_zzlabel (JBWGraphic *graphic,   ///< JBWGraphic widget.
                         const char *str_zz)    ///< 2nd z label.
{
  graphic->str_zz = str_zz;
}

/**
 * Function to set the draw function of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_draw (JBWGraphic *graphic,      ///< JBWGraphic widget.
                      void (*draw) (JBWGraphic *))
                      ///< draw function pointer.
{
  graphic->draw = draw;
}

/**
 * Function to set the minimum size allowed of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_size_request (JBWGraphic *graphic,      ///< JBWGraphic widget.
                              int width,        ///< minimum width.
                              int height)       ///< minimum height.
{
  graphic->minimum_width = width;
  graphic->minimum_height = height;
#if HAVE_GTKWIDGET
  gtk_widget_set_size_request (graphic->widget, width, height);
#elif HAVE_SDL
  SDL_SetWindowMinimumSize (graphic->window, width, height);
#elif HAVE_GLFW
  glfwSetWindowSizeLimits (graphic->window, width, height, GLFW_DONT_CARE,
                           GLFW_DONT_CARE);
#endif
}

/**
 * Function to set a calculate function on a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_calculate (JBWGraphic *graphic, ///< JBWGraphic widget.
                           int (*calculate) (JBWGraphic *graphic))
                                 ///< calculate function.
{
  graphic->calculate = calculate;
}

/**
 * Function to set user data on a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_data (JBWGraphic *graphic,      ///< JBWGraphic widget.
                      void *data)       ///< user data.
{
  graphic->data = data;
}

/**
 * Function to quit a main loop in a JBWGraphic widget.
 */
static inline void
jbw_graphic_loop_quit (void)
{
#if HAVE_GTKWIDGET
  g_main_loop_quit (jbw_graphic_loop_pointer);
#elif HAVE_FREEGLUT
  glutLeaveMainLoop ();
#elif HAVE_SDL
  SDL_Event event[1];
  event->type = SDL_QUIT;
  SDL_PushEvent (event);
#elif HAVE_GLFW
  jbw_graphic_loop_exit = 1;
#endif
}

/**
 * Function to show the JBWGraphic widget.
 */
#if HAVE_GTKWIDGET
static inline void
jbw_graphic_show (JBWGraphic *graphic)  ///< JBWGraphic widget.
{
#if GTK_MAJOR_VERSION > 3
  gtk_window_present (graphic->window);
#else
  gtk_widget_show_all (GTK_WIDGET (graphic->window));
#endif
}
#endif

#if GTK_MAJOR_VERSION > 3

void gtk_entry_set_text (GtkEntry * entry, const char *text);
const char *gtk_entry_get_text (GtkEntry * entry);

unsigned int jbw_array_buttons_get_active (GtkCheckButton * array[],
                                           unsigned int n);

#else

#define GtkPicture GtkImage

#define gtk_box_append(box, child) (gtk_box_pack_start(box, child, 0, 0, 0))
#define gtk_check_button_get_active(button) \
  (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
#define gtk_check_button_set_active(button, active) \
  (gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), active))
#define gtk_file_chooser_get_current_name gtk_file_chooser_get_filename
#define gtk_file_chooser_set_current_name gtk_file_chooser_set_filename
#define gtk_frame_set_child(frame, child) \
  (gtk_container_add(GTK_CONTAINER(frame), child))
#define gtk_grid_remove(grid, child) (gtk_widget_destroy(child))
#define gtk_picture_new_for_filename gtk_image_new_from_file
#define gtk_picture_new_for_pixbuf gtk_image_new_from_pixbuf
#define gtk_scrolled_window_set_child(scrolled, widget) \
  (gtk_container_add (GTK_CONTAINER(scrolled), widget))
#define gtk_window_destroy(window) (gtk_widget_destroy (GTK_WIDGET(window)))
#define gtk_window_set_child(window, widget) \
  (gtk_container_add (GTK_CONTAINER(window), widget))

#if GLIB_MAJOR_VERSION <= 2 && GLIB_MINOR_VERSION < 74
#define G_APPLICATION_DEFAULT_FLAGS G_APPLICATION_FLAGS_NONE
#endif

unsigned int jbw_array_buttons_get_active (GtkRadioButton * array[],
                                           unsigned int n);

#endif

#endif

#endif
