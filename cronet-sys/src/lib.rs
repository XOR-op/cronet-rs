#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

#[allow(clippy::all)]
mod binding {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use binding::*;

#[cfg(test)]
mod tests {
    use super::*;
    use std::ffi::{CStr, CString};

    unsafe fn create_engine() -> Cronet_EnginePtr {
        unsafe {
            let cronet_engine = Cronet_Engine_Create();
            let params = Cronet_EngineParams_Create();
            let user_agent = CString::new("CronetSample/1").unwrap();
            Cronet_EngineParams_user_agent_set(params, user_agent.as_ptr());
            Cronet_EngineParams_enable_quic_set(params, true);
            Cronet_Engine_StartWithParams(cronet_engine, params);
            Cronet_EngineParams_Destroy(params);
            cronet_engine
        }
    }
    #[test]
    fn test_create() {
        unsafe {
            let engine = create_engine();
            let version = CStr::from_ptr(Cronet_Engine_GetVersionString(engine))
                .to_string_lossy()
                .to_string();
            println!("Cronet version:{version}");
        }
    }
}
