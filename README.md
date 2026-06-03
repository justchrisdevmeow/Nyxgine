# Nyxgine

A minimal game engine built in C with OpenGL 3.3.  
Runs on Windows. Built with GitHub Actions.

## Features

- First-person camera (WASD + mouse)
- Physics (gravity, velocity, ground collision)
- Entity system (position, velocity, mass)
- Mesh rendering (cube, plane)
- Shader system (vertex + fragment)
- Input handling (keyboard + mouse)

## Folder Structure

```
nyxgine/
├── .github/workflows/build.yml   # CI/CD pipeline
├── libs/
│   ├── glad.c                     # OpenGL loader
│   └── glad.h
├── src/
│   ├── game/
│   │   └── main.c                 # Game entry point
│   ├── math/
│   │   ├── vec3.c/h               # 3D vector math
│   │   ├── mat4.c/h               # 4x4 matrix math
│   │   └── quat.c/h               # Quaternion math
│   ├── core/
│   │   ├── window.c/h             # GLFW window management
│   │   ├── input.c/h              # Keyboard/mouse input
│   │   └── time.c/h               # Delta time
│   ├── render/
│   │   ├── shader.c/h             # OpenGL shader compilation
│   │   ├── mesh.c/h               # Mesh creation (cube, plane)
│   │   └── camera.c/h             # FPS camera
│   └── physics/
│       └── rigidbody.c/h          # Gravity, velocity, collision
```

## Build

Push to GitHub. Actions builds `nyxgine.exe`.  
Download from Actions → Artifacts.

## Built-In Controls

| Key | Action |
|-----|--------|
| WASD | Move camera |
| Mouse | Look around |
| Space | Reset cube position |

## Dependencies

- GLFW 3.4 (window/input)
- OpenGL 3.3 Core (rendering)
- glad (OpenGL loader)

## License
MIT

Do whatever you want with it. 
