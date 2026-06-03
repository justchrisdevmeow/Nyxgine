#include "../core/window.h"
#include "../core/input.h"
#include "../core/time.h"
#include "../render/shader.h"
#include "../render/mesh.h"
#include "../render/camera.h"
#include "../physics/rigidbody.h"
#include <stdio.h>

static const char* vertex_shader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\n";

static const char* fragment_shader =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec3 color;\n"
    "void main() {\n"
    "    FragColor = vec4(color, 1.0);\n"
    "}\n";

int main(void) {
    Window* win = window_create(800, 600, "Nyxgine");
    if (!win) return -1;
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    
    input_init(win);
    time_update();
    
    Shader* shader = shader_create(vertex_shader, fragment_shader);
    Mesh* cube = mesh_create_cube();
    Mesh* ground = mesh_create_plane(10.0f);
    
    Camera* cam = camera_create(800.0f / 600.0f);
    cam->position = vec3(0, 3, 8);
    
    RigidBody* rb = rigidbody_create(vec3(0, 2, 0), 1.0f);
    
    glEnable(GL_DEPTH_TEST);
    
    while (!window_should_close(win)) {
        time_update();
        float dt = time_delta();
        
        input_update();
        camera_process_mouse(cam, input_mouse_dx(), input_mouse_dy());
        
        float speed = 5.0f * dt;
        if (input_key_down(GLFW_KEY_W))
            cam->position = vec3_add(cam->position, vec3_mul(cam->front, speed));
        if (input_key_down(GLFW_KEY_S))
            cam->position = vec3_sub(cam->position, vec3_mul(cam->front, speed));
        if (input_key_down(GLFW_KEY_D))
            cam->position = vec3_add(cam->position, vec3_mul(vec3_cross(cam->front, cam->up), speed));
        if (input_key_down(GLFW_KEY_A))
            cam->position = vec3_sub(cam->position, vec3_mul(vec3_cross(cam->front, cam->up), speed));
        
        rigidbody_update(rb, dt);
        
        if (input_key_pressed(GLFW_KEY_SPACE)) {
            rb->position = vec3(0, 2, 0);
            rb->velocity = vec3_zero();
        }
        
        Mat4 view = camera_get_view(cam);
        Mat4 proj = camera_get_projection(cam);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader_use(shader);
        shader_set_mat4(shader, "view", &view.m[0][0]);
        shader_set_mat4(shader, "projection", &proj.m[0][0]);
        
        Mat4 ground_model = mat4_identity();
        shader_set_mat4(shader, "model", &ground_model.m[0][0]);
        shader_set_vec3(shader, "color", 0.4f, 0.5f, 0.3f);
        mesh_draw(ground);
        
        Mat4 cube_model = mat4_translate(rb->position);
        cube_model = mat4_mul(cube_model, mat4_scale(vec3(0.5f, 0.5f, 0.5f)));
        shader_set_mat4(shader, "model", &cube_model.m[0][0]);
        shader_set_vec3(shader, "color", 1.0f, 0.3f, 0.3f);
        mesh_draw(cube);
        
        window_swap_buffers(win);
        window_poll_events();
    }
    
    mesh_destroy(cube);
    mesh_destroy(ground);
    shader_destroy(shader);
    camera_destroy(cam);
    rigidbody_destroy(rb);
    window_destroy(win);
    return 0;
}
