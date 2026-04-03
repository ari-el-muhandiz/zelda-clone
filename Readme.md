This is Zelda clone game built using SDL 2.0 and C++.

✅ Phase 1: Core Engine Prototype
•	Set up build system with C++ and CMake
•	Implement window/input loop (GLFW or SDL)
•	Render a triangle with Vulkan or OpenGL
•	Add ECS and scene graph
•	Implement basic camera and transforms

✅ Phase 2: Tools and Assets
•	Implement asset loader (PNG, OBJ, glTF, etc.)
•	Add 3D rendering (mesh, material, light)
•	Create minimal editor/debug UI
•	Add scripting with Lua

✅ Phase 3: Gameplay Systems
•	Add animation system (skeletal & sprite)
•	Add physics engine integration
•	Build example game level (Zelda-style)
•	Save/load support, input config

✅ Phase 4: Portability Layer
•	Abstract rendering/input/audio layers
•	Design backend per platform (Windows, macOS, Switch SDK)
•	Create export pipeline


TIMEFRAME

🔥 Phase 1: Core Engine Foundations

✅ Week 1–4: Set Up Your Environment
•	Install Rider for Unreal, CMake, and Vulkan SDK
•	Choose your windowing/input library: GLFW or SDL2
•	Set up your first C++ project structure using CMake
•	Create a simple game loop that opens a window and polls for input
•	Optional: Add hot-reload-friendly directory structure (e.g., src/, engine/, game/)

✅ Week 5–8: Rendering Engine Basics
•	Initialize Vulkan (or OpenGL first for faster progress, then swap to Vulkan later)
•	Render a triangle to the screen (hello world)
•	Build a render abstraction layer (e.g., Renderer::DrawMesh(mesh, material))
•	Load and render 2D sprites or textured quads
•	Support sprite sheets with UV offset/scale for animation frames

⸻

🧩 Phase 2: Engine Architecture & Systems

✅ Week 9–14: Core Systems
•	Implement Entity-Component-System (ECS)
•	Use entt or write your own
•	Add a Scene Graph for hierarchical transforms
•	Build a Camera system (2D and 3D support)
•	Input system abstraction (keyboard/mouse/gamepad)

✅ Week 15–20: Asset & Tooling
•	Implement Asset Loader
•	Support .png, .obj, .gltf
•	Use stb_image, tinyobjloader, cgltf
•	Build resource manager with caching
•	Add ImGui-based debug UI for runtime inspection

⸻

🎮 Phase 3: Gameplay Features

✅ Week 21–30: Engine Gameplay Layer
•	Add scripting with Lua or Wren
•	Implement basic 2D/3D animation system
•	Skeletal animation for 3D characters
•	Sprite animation for 2D
•	Integrate Bullet Physics or write your own collision/physics

⸻

🛠️ Phase 4: Editor & Exporter

✅ Week 31–40:
•	Create an editor window using ImGui
•	Implement transform tools (move, scale, rotate)
•	Save/load scene files (e.g., JSON or custom binary format)
•	Add level design & prefab tools
•	Export scenes for your runtime to load

⸻

🚀 Phase 5: Platform Abstraction & Porting

✅ (Post-Prototype Phase)
•	Create Platform, Renderer, Input, Audio abstraction layers
•	Swap out SDL/GLFW and replace with SDK backends for:
•	🟢 Windows (Win32)
•	🍎 macOS (Metal layer via MoltenVK or SDL)
•	🎮 Switch, PS5, Xbox (via dev SDKs)
•	Build export system that bundles engine + game assets

⸻

## 🎨 Features

### Sprite Sheet Support

The engine supports sprite sheets (texture atlases) with UV offset and scale for selecting individual frames:

**Shader Support:**
- `uvOffset`: starting UV coordinate for the sprite frame
- `uvScale`: size of one frame in UV space (e.g., 1/16 for a 16-column sheet)

**Usage Example:**
```cpp
// For a 16x9 sprite sheet, select sprite at column 5, row 2
float u0 = 5.0f / 16.0f;
float v0 = 2.0f / 9.0f;
material->setVec2("uvOffset", u0, v0);
material->setVec2("uvScale", 1.0f / 16.0f, 1.0f / 9.0f);
```

**Benefits:**
- Single texture for all character animations
- Easy frame switching for sprite animation
- Memory efficient compared to separate textures per frame
