#! /bin/bash -ex
cd /home/ubuntu/github_repo/OpenIOLabs-Examples

OUTPUT="$(ssh-keygen -lf ~/.ssh/id_rsa.pub)"
echo "${OUTPUT}"

OUTPUT="$(whoami)"
echo "${OUTPUT}"

OUTPUT="$(git remote -v)"
echo "${OUTPUT}"

OUTPUT="$(pwd)"
echo "${OUTPUT}"

OUTPUT="$(git worktree list)"
echo "${OUTPUT}"

OUTPUT="$(git config --list)"
echo "${OUTPUT}"

cp -r /home/ubuntu/manual_builds/openio/src/scriptml/docs/c-api/* /home/ubuntu/github_repo/OpenIOLabs-Examples/documents/doxygen/c-api/.
cp -r /home/ubuntu/manual_builds/openio/src/scriptml/docs/python-api/* /home/ubuntu/github_repo/OpenIOLabs-Examples/documents/doxygen/python-api/.

env git pull
git add /home/ubuntu/github_repo/OpenIOLabs-Examples/*
git commit -am 'Doxygen update'
git push
