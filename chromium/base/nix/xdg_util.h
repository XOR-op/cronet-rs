// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_NIX_XDG_UTIL_H_
#define BASE_NIX_XDG_UTIL_H_

// XDG refers to http://en.wikipedia.org/wiki/Freedesktop.org .
// This file contains utilities found across free desktop environments.

#include "base/base_export.h"

namespace base {

class Environment;
class FilePath;

namespace nix {

enum DesktopEnvironment {
  DESKTOP_ENVIRONMENT_OTHER = 0,
  DESKTOP_ENVIRONMENT_CINNAMON = 1,
  DESKTOP_ENVIRONMENT_DEEPIN = 2,
  DESKTOP_ENVIRONMENT_GNOME = 3,
  // KDE{3,4,5,6} are sufficiently different that we count
  // them as different desktop environments here.
  DESKTOP_ENVIRONMENT_KDE3 = 4,
  DESKTOP_ENVIRONMENT_KDE4 = 5,
  DESKTOP_ENVIRONMENT_KDE5 = 6,
  DESKTOP_ENVIRONMENT_KDE6 = 12,
  DESKTOP_ENVIRONMENT_PANTHEON = 7,
  DESKTOP_ENVIRONMENT_UKUI = 8,
  DESKTOP_ENVIRONMENT_UNITY = 9,
  DESKTOP_ENVIRONMENT_XFCE = 10,
  DESKTOP_ENVIRONMENT_LXQT = 11,
};

// Values based on valid types indicated in:
// https://www.freedesktop.org/software/systemd/man/pam_systemd.html; though
// "Unset" and "Other" are provided by us to distinguish between the potentially
// valid "Unspecified" and other cases where we may not be able to find the
// value.
enum class SessionType {
  kUnset = 0,
  kOther = 1,
  kUnspecified = 2,
  kTty = 3,
  kX11 = 4,
  kWayland = 5,
  kMir = 6,
};

// The default XDG config directory name.
BASE_EXPORT extern const char kDotConfigDir[];

// The XDG config directory environment variable.
BASE_EXPORT extern const char kXdgConfigHomeEnvVar[];

// The XDG current desktop environment variable.
BASE_EXPORT extern const char kXdgCurrentDesktopEnvVar[];

// The XDG session type environment variable.
BASE_EXPORT extern const char kXdgSessionTypeEnvVar[];

// Utility function for getting XDG directories.
// |env_name| is the name of an environment variable that we want to use to get
// a directory path. |fallback_dir| is the directory relative to $HOME that we
// use if |env_name| cannot be found or is empty. |fallback_dir| may be NULL.
// Examples of |env_name| are XDG_CONFIG_HOME and XDG_DATA_HOME.
BASE_EXPORT FilePath GetXDGDirectory(Environment* env, const char* env_name,
                                     const char* fallback_dir);

// Wrapper around xdg_user_dir_lookup() from src/base/third_party/xdg-user-dirs
// This looks up "well known" user directories like the desktop and music
// folder. Examples of |dir_name| are DESKTOP and MUSIC.
BASE_EXPORT FilePath GetXDGUserDirectory(const char* dir_name,
                                         const char* fallback_dir);

// Return an entry from the DesktopEnvironment enum with a best guess
// of which desktop environment we're using.  We use this to know when
// to attempt to use preferences from the desktop environment --
// proxy settings, password manager, etc.
BASE_EXPORT DesktopEnvironment GetDesktopEnvironment(Environment* env);

// Return a string representation of the given desktop environment.
// May return NULL in the case of DESKTOP_ENVIRONMENT_OTHER.
BASE_EXPORT const char* GetDesktopEnvironmentName(DesktopEnvironment env);
// Convenience wrapper that calls GetDesktopEnvironment() first.
BASE_EXPORT const char* GetDesktopEnvironmentName(Environment* env);

// Return an entry from the SessionType enum with a best guess
// of which session type we're using.
BASE_EXPORT SessionType GetSessionType(Environment& env);

}  // namespace nix
}  // namespace base

#endif  // BASE_NIX_XDG_UTIL_H_
