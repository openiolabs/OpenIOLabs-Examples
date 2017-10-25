#! /bin/bash -ex

cd /home/ubuntu/github_repo/OpenIOLabs-Examples

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

git pull


env -i git add /home/ubuntu/github_repo/OpenIOLabs-Examples/*

env -i git push
