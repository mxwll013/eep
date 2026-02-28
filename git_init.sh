#! /usr/bin/env bash

git init
git add .
git commit -m "hello world"
git branch -M main
git remote add origin git@github.com:mxwll013/eep.git
git push -u origin main
