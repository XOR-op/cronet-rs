# cronet-rs
Rust FFI bindings for Chromium network stack(cronet). 

*Note: This project is currently in an experimental phase and is at an early stage of development.
It may be subject to frequent changes, and some features may not be fully implemented.
Currently only macos-aarch64 and linux-x86_64 are tested.*

## How to build the project
```bash
# Download Chromium whose version is specified in `CHROMIUM_VERSION` file
./tools/import-upstream.sh 
# Patch source code
./build-script/patch.sh
# Prepare build tools
./build-script/get-clang.sh

# Invoke gn to generate .ninja files. For arm64 macOS, run
target_cpu="arm64" ./build-script/build.sh
# For other platforms, run
./build-script/build.sh

# Build static library
ninja -C chromium/out/Release cronet_static
# (Optional) Build dynamic library
ninja -C chromium/out/Release cronet
```

## Credits
Thanks:
- Chromium project for the basement of this  project.
-  [NaïveProxy](https://github.com/klzgrad/naiveproxy) for the original build scripts.