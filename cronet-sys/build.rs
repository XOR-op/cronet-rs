use std::env;
use std::path::PathBuf;

fn main() {
    let dir = env!("CARGO_MANIFEST_DIR");
    let mut build_dir = PathBuf::from(dir);
    build_dir.pop();
    build_dir.push("chromium/out/Release/obj/components/cronet");
    // build_dir.push("chromium/out/Release");

    println!(
        "cargo:rustc-link-search={}",
        build_dir.as_os_str().to_str().unwrap()
    );
    println!("cargo:rustc-link-lib=cronet_static");
    #[cfg(target_os = "macos")]
    {
        println!("cargo:rustc-link-lib=objc");
        println!("cargo:rustc-link-lib=framework=CoreFoundation");
        println!("cargo:rustc-link-lib=framework=CFNetwork");
        println!("cargo:rustc-link-lib=framework=AppKit");
        println!("cargo:rustc-link-lib=framework=Security");
        println!("cargo:rustc-link-lib=framework=SystemConfiguration");
    }

    println!("cargo:rerun-if-changed=wrapper.h");

    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("wrapper.h")
        .clang_arg("-I../chromium/components/cronet/native/include")
        .clang_arg("-I../chromium/components/cronet/native/generated")
        .clang_arg("-I../chromium/components/grpc_support/include")
        .clang_arg("-x")
        .clang_arg("c++")
        .clang_arg("-std=c++11")
        .clang_arg("-stdlib=libc++")
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
