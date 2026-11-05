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