# Fractal Viewer (SDL2)

A real-time interactive Mandelbrot and Julia set renderer using SDL2, with color customization, zooming, animation, and high-quality screenshot capture.
Currently supports the Mandelbrot set and Julia sets (try and uncover the interaction!).

## Features

- Render Mandelbrot and Julia sets in real-time.
- Zoom in/out with precision.
- Mouse control for navigating and exploring the fractal space.
- Toggle animation of Julia sets.
- Capture high-resolution screenshots.
- Fine-grained control over visual appearance via:

  - Exponential color bias adjustment.
  - Max escape step tweaking.
  - Custom color map.

- Smooth animations via rotating complex parameter `C` in the Julia set.

> **Note:** The y axis increases downwards (opposite to a standard graph) to make the mouse movements more intuitive.

---

## Keybindings

| Key         | Action                                                                          |
| ----------- | ------------------------------------------------------------------------------- |
| `ESC`       | Exit the program                                                                |
| `s`         | Save a high-resolution screenshot                                               |
| `f`         | Toggle the color of "in the set" pixels (contrasted or natural progression)     |
| `m`         | Toggle mouse control for adjusting the Julia parameter `C`                      |
| `i`         | Zoom **in** at mouse location and reset mouse to center (use I for larger zoom) |
| `o`         | Zoom **out** from mouse location (use O for larger zoom)                        |
| `n`         | Cycle to the next fractal variant                                               |
| `1`         | Switch to Julia set                                                             |
| `2`         | Switch to Mandelbrot set                                                        |
| `3`         | Switch to Burning Ship set                                                      |
| `,` / `.`   | Decrease / increase exponential color bias                                      |
| `<` / `>`   | Decrease / increase max escape steps                                            |
| Mouse click | Center view on mouse location                                                   |
| `a`         | Toggle animation for the Julia set                                              |
| `g`         | Get mathematical location details logged to terminal                            |

---

## Visual Tuning Tips

- If the image is **too dark or too bright**, use `,` and `.` to adjust the **exponential color bias**. This alters how quickly color intensity grows, making subtle structures more visible.
- If you see large black blobs that don’t resolve detail, increase the **maximum escape steps** using `>`.

- For best screenshots:

  - Adjust colors and zoom level (use both large and small zoom levels for fine adjustment).
  - Freeze animation (`a`) and lock mouse input (`m`).
  - Then press `s` to save a snapshot.

---

## Build & Run

### Prerequisites

- **SDL2** and **SDL2_image** (install via Homebrew: `brew install sdl2 sdl2_image`)
- **OpenMP** (for parallel rendering)
- C compiler supporting OpenMP (`gcc` or `clang` on macOS with `libomp`)

### Build Instructions (macOS/Homebrew)

```bash
make build
```

### Run the Program

```bash
make run
```

### Clean Build Files

```bash
make clean
```

> **Note:** This Makefile assumes you're using **Homebrew** and an **Apple Silicon (M1/M2)** or Intel Mac with libraries installed in `/opt/homebrew/`.

If you’re on another system, you may need to adjust the `-I` and `-L` paths in the `Makefile`.

---

## Screenshots

## 📸 Screenshots

### Travellers

![Double Pass Rendering](images/double%20pass%20rendering%20test.png)

### Electric

![Electric](images/electric.png)

### Event Horizon

![Event Horizon](images/event%20horizon.png)

### Lilypads

![Lilypads](images/lilypads.png)

### Julia Flower

![Main Background](images/main%20background.png)

### Mandelbrot Spiral

![Mandelbrot Spiral](images/mandelbrot%20spiral.png)

### Mini Mandelbrot

![Mini Mandelbrot](images/minimandelbrot.png)

### Mouth of the Mandelbrot

![Mouth of Mandelbrot](images/mouth%20of%20the%20mandelbrot.png)

### Pink Spirals

![Pink Spirals](images/pink%20spirals.png)

### Fire

![Screenshot Copy](images/screenshot%20copy.png)

### Twisters

![Screenshot 2](images/screenshot_2.png)

### Thorns

![Screenshot](images/screenshot.png)

### Spider Fractal

![Spider Fractal](images/spider_fractal.png)

### Spirals

![Spirals](images/spirals.png)

### Super Zoomed Mandelbrot

![Super Zoomed Mandelbrot](images/super%20zoomed%20mandelbrot.png)

### The Limit of the Doubles

![Limit of Doubles](images/the%20limit%20of%20the%20doubles.png)

### The Probe

![The Probe](images/the%20probe%20copy.png)

### Tree of Life

![Tree of Life](images/tree%20of%20life.png)

### Web

![Web](images/web.png)

### Zoomed Black and White

![Zoomed Black and White](images/zoomed%20black%20and%20white.png)

### Zoomed Flower Spiral

![Zoomed Flower Spiral](images/zoomed%20flower%20spiral.png)

### Burning Ship

## ![Burning Ship](images/burning%20ship.png)

## License

MIT License
