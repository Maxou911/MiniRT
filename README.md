# miniRT 🎯

> A minimal ray tracer built in C, following the 42 School project specifications.

<img width="1402" height="879" alt="image" src="https://github.com/user-attachments/assets/beb49b58-c9bc-4ad1-baf2-e60b6c77b9ee" />

---

## 📖 Description

**miniRT** is a ray tracing engine written in C from scratch. It renders 3D scenes described in `.rt` configuration files, producing realistic images with lighting, shadows, and multiple geometric objects.

This project is an introduction to the beautiful world of ray tracing — simulating how light interacts with objects to generate photorealistic images.

---

## ✨ Features

- 🔵 **Geometric primitives** — Spheres, Planes, Cylinders
- 💡 **Lighting** — Ambient light and point light sources
- 🌑 **Shadows** — Hard shadows cast by objects
- 🎨 **Colors & materials** — Per-object RGB color definition
- 📷 **Configurable camera** — Position, orientation, and field of view
- 🖼️ **Real-time window** — Rendered with MiniLibX
- ⌨️ **Controls** — Close with `ESC` or the window's close button

---

## 🗂️ Scene file format (`.rt`)

A scene is described in a plain-text `.rt` file. Each element is defined on its own line.

### Elements

| Identifier | Description | Example |
|------------|-------------|---------|
| `A` | Ambient light | `A 0.2 255,255,255` |
| `C` | Camera | `C -50,0,20 0,0,1 70` |
| `L` | Point light | `L -40,50,0 0.6 255,255,255` |
| `sp` | Sphere | `sp 0,0,20 20 255,0,0` |
| `pl` | Plane | `pl 0,-10,0 0,1,0 200,200,200` |
| `cy` | Cylinder | `cy 50,0,20 0,0,1 14 20 120,200,50` |

### Example scene

```
A  0.2                          255,255,255

C  -50,0,20    0,0,1            70
L  -40,50,0    0.6              255,255,255

sp  0,0,20     20               255,0,0
pl  0,-10,0    0,1,0            200,200,200
cy  50,0,20    0,0,1   14  20   120,200,50
```

---

## 🔧 Installation & Usage

### Requirements

- GCC / Clang
- Make
- MiniLibX (included or installed separately)
- Linux or macOS

### Clone & Build

```bash
git clone https://github.com/your-username/miniRT.git
cd miniRT
make
```

### Run

```bash
./miniRT scene-rt/your_scene.rt
```

### Clean

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Rebuild from scratch
```
---

## 🧮 How ray tracing works

1. **For each pixel**, a ray is cast from the camera through the scene.
2. The ray is tested against **every object** to find the closest intersection.
3. At the hit point, the **normal** is computed.
4. A **shadow ray** is sent toward the light source to determine occlusion.
5. The final **color** is computed using ambient + diffuse (Phong-like) lighting.

---

## 🎓 42 School

This project is part of the **42 School** graphics branch. It introduces:
- 3D mathematics (vectors, dot products, normals)
- Ray–object intersection algorithms
- Basic shading and lighting models
- Scene parsing and window management with MiniLibX

---

## 👥 Authors

| Name | GitHub |
|------|--------|
| Your Name | [@Maxou911](https://github.com/Maxou911) |
| Your Name | [@uzyberaj](https://github.com/uzyberaj) |

---

## 📄 License

This project is for educational purposes as part of the 42 School curriculum.
