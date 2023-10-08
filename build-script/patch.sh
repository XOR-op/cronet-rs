#!/bin/bash
cd `dirname $0`
cd ..

git apply build-script/build-diff.patch
git apply build-script/rust-fix.patch
git apply build-script/cronet-build.patch
