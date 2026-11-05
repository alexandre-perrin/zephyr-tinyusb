# Zephyr TinyUSB

This repository bridges [TinyUSB](https://github.com/hathach/tinyusb)
to Zephyr as a standalone module.
Upstream sources remain unmodified in the `tinyusb/` Git submodule.
The root `CMakeLists.txt` and `Kconfig` provide the integration,
registered by `zephyr/module.yml`.

## Add to a west workspace

Add this repository to the application manifest
with submodule updates enabled:

```yaml
manifest:
  projects:
    - name: zephyr-tinyusb
      url: https://github.com/alexandre-perrin/zephyr-tinyusb
      revision: main
      path: modules/lib/zephyr-tinyusb
      submodules: true
```

Then run `west update` to fetch the bridge
and initialize its upstream submodule.

## Configuration

Enable `CONFIG_TINYUSB` in the application configuration.
The application must provide a `tusb_config.h` file.
Set `TINYUSB_CONFIG_DIR` to its directory before
`find_package(Zephyr)` in the application CMake file.

## Sample

The FIFO sample demonstrates TinyUSB's bounded FIFO API
and runs without a USB controller.
Run it on `native_sim` with Twister:

```sh
west twister -p native_sim -T samples/fifo
```

## Tests

From a configured Zephyr workspace,
run the smoke tests with Twister:

```sh
west twister -p native_sim -T tests
```
