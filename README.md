# PixelBox 

<p align="center">
  <img src="docs/demo.gif" alt="Short demo" width="250">
  <img src="docs/views.png" alt="Side views" width="443">
</p>



**A modular, standalone pixel-art device** that you can access from any browser on your local network. Built on a Wemos D1 Mini and TFT screen, PixelBox hosts its own web app where you can draw, upload, and paste pixel art that appears live on the display. The included retro-TV enclosure is just one example—you can use the parametric model to design your own housings or adapt the project to different TFT screen sizes.



---

## ✨ Highlights

* **Standalone:** Boots, connects to Wi-Fi, shows a QR code to open it, and serves a built-in web UI (no extra apps needed).
* **Modular:** Design and swap enclosures (STEPs + STLs), batteries, or even different TFT screens.
* **Create your way:** Draw pixel-by-pixel, choose colors, clear, paste from the clipboard, or upload images.
* **Fast updates:** A batch RGB drawing API enables quick and responsive rendering while keeping network traffic and MCU load within safe limits.

---

## 🧩 Hardware

* **MCU:** Wemos D1 mini (ESP8266)
* **Display:** 1.44″ ST7735 TFT (compatible variants work)
* **Battery:** \~1000 mAh Li-ion (≈ 40×25×20 mm)
* **Charging:** USB-C Li-ion charger (4.2 V / 1 A)
* **Enclosure:** `hardware/step` (parametric) + `hardware/stl` (printable)


<p align="center">
  <img src="docs/exploded.png" alt="Exploded view" width="450">
</p>

> See `hardware/wiring.png` for a diagram.

⚠️ **Disclaimer:** Working with electronics, batteries, and soldering carries inherent risks. Only attempt wiring, soldering, or battery integration if you have the proper skills and experience. Incorrect handling may result in damage, overheating, or injury. Always follow safe practices and double-check connections before powering the device.

⚡ **Charging Notice:** Use only standard 5V USB power sources (such as a laptop USB port) and avoid fast-charging cables or adapters. The charging module typically indicates status with an onboard LED (commonly red for charging and green/blue for fully charged), but please verify this with your specific component. Never leave the device unattended while charging.

---

## 🛠️ Firmware (PlatformIO)

Requires PlatformIO and these libs (auto-installed via `platformio.ini`):

* Adafruit GFX
* Adafruit ST7735/ST7789
* ArduinoJson
* WiFiManager

Build & upload:

```bash
# From the repo root
pio run -t upload     # compiles and uploads
pio device monitor    # optional: serial logs @ 115200
```

 

The web interface is defined in `data/index.html`. During the build process, a script inlines it into `include/web_page.h`—no separate SPIFFS upload is required.

`scripts/prebuild.py` is responsible for compressing `data/index.html` and converting embedded images into Base64 format, maximizing storage efficiency and keeping everything self-contained.

---

## ▶️ Use

1. **Power PixelBox.** If it can’t join Wi-Fi, it starts a configuration portal named **MiniPC\_Config** and shows a QR code. Scan it with your phone to join the portal (or join **MiniPC\_Config** manually), then pick your Wi-Fi on the setup page that opens. If the page doesn’t open by itself, go to `192.168.4.1`.

> 💡 To reset or update Wi-Fi credentials later, hold down the button connected to **D6** while powering up the device. This will launch the configuration portal directly.

2. On success, the TFT shows a QR code and the device IP in your local subnet (e.g., `192.168.1.50`). It stays on screen until the page is opened or something is drawn. Press the **D6** button at any time to show it again.
3. Scan the QR code, or open that IP in a browser on the same network. You’ll see a pixel grid UI:

   * Pick colors
   * **Draw** pixels with mous or on touchscreen
   * **Upload** an image or **paste** from clipboard
   * **Clear** the screen, or view **Info**
4. The TFT updates live as you draw, also indicated by blinking LED connected to D3

### API (local)

* `POST /batchDraw` — send batched RGB cell data (JSON)
* `GET /clear` — clear display

---

## 📁 Repo layout

```
src/           # firmware
include/       # generated web_page.h (auto)
scripts/       # prebuild.py (HTML → header)
data/          # index.html + assets (embedded)
hardware/      # STEP/STL + wiring
```

---

## 🧱 Enclosures

The retro-TV housing is one example under `hardware/stl/`. Open the **parametric STEP/Fusion** files in `hardware/step/`, which also includes STEP files of each electronics components. Contributions with new themes welcome!

---

## 🔐 See `LICENSE`

