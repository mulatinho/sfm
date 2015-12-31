#!/bin/sh
ln -sf README.md README
autoreconf --force --install -I po -I doc -I src -I tests
