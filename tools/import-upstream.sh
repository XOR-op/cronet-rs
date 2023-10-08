#!/bin/bash
set -ex
have_version=$(cut -d= -f2 chromium/chrome/VERSION | tr '\n' . | cut -d. -f1-4)
want_version=$(cat CHROMIUM_VERSION)
if [ "$have_version" = "$want_version" ]; then
  exit 0
fi
name="chromium-$want_version"
tarball="$name.tar.xz"
url="https://commondatastorage.googleapis.com/chromium-browser-official/$tarball"
git config core.autocrlf false
git config core.safecrlf false
sed "s/^\^/$name\//" ./tools/include.txt > ./tools/include.tmp
if [ ! -f "/tmp/$tarball" ]; then
  curl "$url" --continue-at - -o "/tmp/$tarball"
fi

if [ "$(uname -s)" = "Darwin" ]; then
  cat "/tmp/$tarball" | gtar xJf - --wildcards --wildcards-match-slash -T ./tools/include.tmp -X ./tools/exclude.txt
else
  cat "/tmp/$tarball" | tar xJf - --wildcards --wildcards-match-slash -T ./tools/include.tmp -X ./tools/exclude.txt
fi
mv "$name" chromium
